// ====================================================================================
// インクルード
// ====================================================================================

#include "Scene01_Select.h"
#include "CameraManager.h"
#include <array>
#include "Main.h"
#include "Scene.h"
#include "Scene04_Load.h"

// ====================================================================================
// static
// ====================================================================================

PlayerController* SceneSelect::m_pFirstPlayerController = nullptr;
PlayerController* SceneSelect::m_pSecondPlayerController = nullptr;

SelectCharacterList::CHARACTER SceneSelect::m_FirstPlayerCharacter =	SelectCharacterList::CHARACTER::NONE;
SelectCharacterList::CHARACTER SceneSelect::m_SecondPlayerCharacter =	SelectCharacterList::CHARACTER::NONE;

PlayerController* SceneSelect::GetFirstPlayerController()
{
	return m_pFirstPlayerController;
}

PlayerController* SceneSelect::GetSecondPlayerController()
{
	return m_pSecondPlayerController;
}

SelectCharacterList::CHARACTER SceneSelect::GetFirstPlayerCharacter()
{
	return m_FirstPlayerCharacter;
}

SelectCharacterList::CHARACTER SceneSelect::GetSecondPlayerCharacter()
{
	return m_SecondPlayerCharacter;
}

// ====================================================================================
// dynamic
// ====================================================================================

void SceneSelect::Init()
{
	const CVector2 WindowSize(static_cast<float>(GetAppWidth()), static_cast<float>(GetAppHeight()));
	const CVector2 WindowCenterPos = WindowSize * 0.5f;

	//========<コントローラーが切れていたら情報を削除する>=================
	ControllerDisconnect();
	//=====================================================================

	//=========<2P分のキャラクターの設定を行う>=============================
	//一人目
	//コントローラーの設定(前のバトルをしていれば)
	m_SelectFirstCharacter.ChangeNowController(m_pFirstPlayerController);
	//1Pが選んでいるキャラクターなどを表示する位置
	m_SelectFirstCharacter.SetBoardPos(CVector3(WindowCenterPos.x - 200.0f, WindowCenterPos.y + 200.0f, 0.0f));
	//ボードの色を変更
	m_SelectFirstCharacter.SetBoardColor(SelectCharacter::BOARDCOLOR::RED);
	//選んでいるキャラクターを設定(前のバトルをしていれば)
	m_SelectFirstCharacter.SetNowCharacter(m_FirstPlayerCharacter);	
	//選べるキャラクターの画像位置などを渡す
	m_SelectFirstCharacter.SetCharacterList(&m_CharacterList);
	//立ち絵の位置の設定
	m_SelectFirstCharacter.SetLerpStandCharacterDrawPos(CVector3(0.0f, 400.0f, 0.0f), CVector3(200.0f,400.0f,0.0f));

	//二人目
	//コントローラーの設定(前のバトルをしていれば)
	m_SelectSecondCharacter.ChangeNowController(m_pSecondPlayerController);
	//2Pが選んでいるキャラクターなどを表示する位置
	m_SelectSecondCharacter.SetBoardPos(CVector3(WindowCenterPos.x + 200.0f, WindowCenterPos.y + 200.0f, 0.0f));
	//ボードの色を変更
	m_SelectSecondCharacter.SetBoardColor(SelectCharacter::BOARDCOLOR::BLUE);
	//選んでいるキャラクターを設定(前のバトルをしていれば)
	m_SelectSecondCharacter.SetNowCharacter(m_SecondPlayerCharacter);
	//選べるキャラクターの画像位置などを渡す
	m_SelectSecondCharacter.SetCharacterList(&m_CharacterList);
	//立ち絵の位置の設定
	m_SelectSecondCharacter.SetLerpStandCharacterDrawPos(CVector3(WindowSize.x, 400.0f, 0.0f), CVector3(WindowSize.x - 200.0f, 400.0f, 0.0f));
	//=====================================================================
	
	m_CharactersText.SetTexture("Assets/UI/CharactersText.png");
	m_CharactersText.m_pos = CVector3(WindowCenterPos.x, 100.0f, 0.0f);
	m_CharactersText.m_size = CVector2(400.0f, 194.0f);

	m_BackGroundImage.SetTexture("Assets/BackGroundImage/SelectBackGround.png");
	m_BackGroundImage.m_pos = WindowCenterPos;
	m_BackGroundImage.m_size = WindowSize;

	m_ReadyToFightTextImage.StartSlide();

	m_ColorFade.m_pos = WindowCenterPos;
	m_ColorFade.m_size = WindowSize;
	m_ColorFade.m_color = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	m_isLoadNextScene = false;

	m_state = SceneSelect::SELECTSTATE::SELECT;

	m_pBGM = new BGM("Assets/Music/Select.wav", true);
	m_pBGM->Start();
}

void SceneSelect::Uninit()
{
	m_pBGM->Stop();
	delete m_pBGM;
}

void SceneSelect::Update()
{
	switch (m_state)
	{
	case SceneSelect::SELECTSTATE::SELECT:
		SelectUpdate();
		break;
	case SceneSelect::SELECTSTATE::FADE:
		FadeUpdate();
		break;
	}	
}

void SceneSelect::SelectUpdate()
{
	//=========<コントローラーが切れていたら情報を削除する>=========
	ControllerDisconnect();

	//=========<コントローラーをつなげる>=========
	ControllerConnect();

	//=========<Bボタンを押していたらコントローラーを解除する>=========
	ControllerRelease();

	//=========<キャラクターを選択する処理>=========
	//キャラくーのアルファ変更
	SelectCharacter::AlphaUpdate();

	//コントローラーが変更されているか確認
	m_SelectFirstCharacter.ChangeNowController(m_pFirstPlayerController);
	m_SelectSecondCharacter.ChangeNowController(m_pSecondPlayerController);

	//キャラクターセレクトのアップデート
	m_SelectFirstCharacter.Update();
	m_SelectSecondCharacter.Update();

	//=========<二人がキャラクターを選んでいたら>=========
	if (m_SelectFirstCharacter.IsDecided() && m_SelectSecondCharacter.IsDecided())
	{
		m_ReadyToFightTextImage.Update();

		//ゲームスタートボタンを押せるようにする
		if (m_pFirstPlayerController->IsTriggerReturn() || m_pSecondPlayerController->IsTriggerReturn())
		{
			//キャラクターの設定
			m_FirstPlayerCharacter = m_SelectFirstCharacter.GetSelectCharacter();
			m_SecondPlayerCharacter = m_SelectSecondCharacter.GetSelectCharacter();

			m_ColorFade.SetFadeTime(0.3f);
			m_ColorFade.SetFadeStart(true);
			m_state = SELECTSTATE::FADE;			
		}
	}
}

void SceneSelect::FadeUpdate()
{
	m_ColorFade.Update();

	if (m_ColorFade.GetFadeEnd())
	{
		//シーンの切り替え
		CScene::SetScene<SceneLoad>();
	}
}

void SceneSelect::Draw()
{
	//=====<UIの描画>=======================================================
	EnableDepth(false);

	m_BackGroundImage.Draw();

	//=====<キャラクター画像を描画>=========================================
	//1Pが選んでいるキャラクターの立ち絵の描画
	m_SelectFirstCharacter.StandCharacterDraw();
	//2Pが選んでいるキャラクターの立ち絵の描画
	m_SelectSecondCharacter.StandCharacterDraw();
	//キャラクターを選ぶときに使うアイコンの描画
	m_CharacterList.Draw();

	m_CharactersText.Draw();
	//======================================================================
	
	//=====<1Pの描画>=======================================================
	//キャラクターとコントローラーを表示するボードを描画
	m_SelectFirstCharacter.BoardDraw();
	//キャラクターを選ぶフレームの描画
	m_SelectFirstCharacter.SelectFrameDraw();
	//======================================================================

	//=====<2Pの描画>=======================================================
	//キャラクターとコントローラーを表示するボードを描画
	m_SelectSecondCharacter.BoardDraw();
	//キャラクターを選ぶフレームの描画
	m_SelectSecondCharacter.SelectFrameDraw();
	//======================================================================

	//=========<二人がキャラクターを選んでいたら>=========
	if (m_SelectFirstCharacter.IsDecided() && m_SelectSecondCharacter.IsDecided())
	{
		m_ReadyToFightTextImage.Draw();
	}

	m_ColorFade.Draw();

	EnableDepth(true);
	//======================================================================
}

void SceneSelect::ControllerConnect()
{
	//1Pと2Pの振り分け
	//ボタンが何か押された順に1P,2Pとしていく

	//1Pが接続されていなければ
	if (m_pFirstPlayerController == nullptr)
	{
		//すべてのコントローラーを取得
		std::array<PlayerController, 5>& ControllerArray = PlayerController::GetPlayerControllers();

		for (PlayerController& Controller : ControllerArray)
		{
			//2Pと同じコントローラーではないか
			if (&Controller == m_pSecondPlayerController)
			{
				continue;
			}

			//コントローラーが繋がっているか
			if (!Controller.IsConnect())
			{
				continue;
			}

			//EnterかAボタンが押されていたら
			if (Controller.IsTriggerReturn())
			{
				//操作するコントローラーを設定
				m_pFirstPlayerController = &Controller;
				m_pFirstPlayerController->UnTriggerNowFrame();
				break;
			}
		}
	}
	//2Pが接続されていなければ
	else if (m_pSecondPlayerController == nullptr)
	{
		//すべてのコントローラーを取得
		std::array<PlayerController, 5>& ControllerArray = PlayerController::GetPlayerControllers();

		for (PlayerController& Controller : ControllerArray)
		{
			//1Pと同じコントローラーではないか
			if (&Controller == m_pFirstPlayerController)
			{
				continue;
			}

			//コントローラーが繋がっているか
			if (!Controller.IsConnect())
			{
				continue;
			}

			//EnterかAボタンが押されていたら
			if (Controller.IsTriggerReturn())
			{
				//操作するコントローラーを設定
				m_pSecondPlayerController = &Controller;
				m_pSecondPlayerController->UnTriggerNowFrame();
				break;
			}
		}
	}
}

void SceneSelect::ControllerDisconnect()
{
	//コントローラーが繋がっていない場合、コントローラーの情報をnullptrにする

	//コントローラーの情報が入っていたら
	if (m_pFirstPlayerController != nullptr)
	{
		//今持っているコントローラーが繋がっているか
		if(!m_pFirstPlayerController->IsConnect())
		{
			m_pFirstPlayerController = nullptr;
		}
	}

	//コントローラーの情報が入っていたら
	if (m_pSecondPlayerController != nullptr)
	{
		//今持っているコントローラーが繋がっているか
		if(!m_pSecondPlayerController->IsConnect())
		{
			m_pSecondPlayerController = nullptr;
		}
	}
}

void SceneSelect::ControllerRelease()
{
	//Bボタンを押したらコントローラーの登録を外してやる

	//コントローラーの情報が入っていたら
	if (m_pFirstPlayerController != nullptr)
	{
		//キャラクターを選んでいる場合
		if (m_SelectFirstCharacter.GetState() == SelectCharacter::SELECTSTATE::SELECT)
		{
			//Bを押すとコントローラーの登録を外す
			if (m_pFirstPlayerController->IsTriggerBack())
			{
				m_pFirstPlayerController = nullptr;
			}
		}
	}

	//コントローラーの情報が入っていたら
	if (m_pSecondPlayerController != nullptr)
	{
		//キャラクターを選んでいる場合
		if (m_SelectSecondCharacter.GetState() == SelectCharacter::SELECTSTATE::SELECT)
		{
			//Bを押すとコントローラーの登録を外す
			if (m_pSecondPlayerController->IsTriggerBack())
			{
				m_pSecondPlayerController = nullptr;
			}
		}
	}
}


