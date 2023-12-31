#include "Scene01_Select.h"
#include "CameraManager.h"
#include <array>

PlayerController* SceneSelect::m_pFirstPlayerController = nullptr;
PlayerController* SceneSelect::m_pSecondPlayerController = nullptr;

SelectCharacterList::CHARACTER SceneSelect::m_FirstPlayerCharacter =		SelectCharacterList::CHARACTER::MAX;
SelectCharacterList::CHARACTER SceneSelect::m_SecondPlayerCharacter =	SelectCharacterList::CHARACTER::MAX;

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

void SceneSelect::Init()
{
	//========<コントローラーが切れていたら情報を削除する>=================
	ControllerDisconnect();
	//=====================================================================

	//=========<2P分のキャラクターの設定を行う>=============================
	//一人目
	//1Pが選んでいるキャラクターなどを表示する位置
	m_SelectFirstCharacter.SetPos(CVector3(100.0f, 400.0f, 0.0f));
	//選んでいるキャラクターを設定(前のバトルをしていれば)
	m_SelectFirstCharacter.SetNowCharacter(m_FirstPlayerCharacter);
	//コントローラーの設定(前のバトルをしていれば)
	m_SelectFirstCharacter.SetController(m_pFirstPlayerController);
	//選べるキャラクターの画像位置などを渡す
	m_SelectFirstCharacter.SetCharacterList(&m_CharacterList.GetCharacterImageList());
	m_SelectFirstCharacter.SetCharacterIconList(&m_CharacterList.GetCharacterIconImageList());

	//二人目
	//2Pが選んでいるキャラクターなどを表示する位置
	m_SelectSecondCharacter.SetPos(CVector3(600.0f, 400.0f, 0.0f));
	//選んでいるキャラクターを設定(前のバトルをしていれば)
	m_SelectSecondCharacter.SetNowCharacter(m_SecondPlayerCharacter);
	//コントローラーの設定(前のバトルをしていれば)
	m_SelectSecondCharacter.SetController(m_pSecondPlayerController);
	//選べるキャラクターの画像位置などを渡す
	m_SelectSecondCharacter.SetCharacterList(&m_CharacterList.GetCharacterImageList());
	m_SelectSecondCharacter.SetCharacterIconList(&m_CharacterList.GetCharacterIconImageList());
	//=====================================================================
	
}

void SceneSelect::Uninit()
{
	
}

void SceneSelect::Update()
{
	//=========<コントローラーが切れていたら情報を削除する>=========
	ControllerDisconnect();

	//=========<コントローラーをつなげる>=========
	ControllerConnect();

	//=========<Bボタンを押していたらコントローラーを解除する>=========
	ControllerRelease();

	//=========<キャラクターを選択する処理>=========
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
		//決定ボタンを押せるようになる
	}
}

void SceneSelect::Draw()
{
	//=====<UIの描画>=====
	EnableDepth(false);

	//キャラクター画像を描画
	m_CharacterList.Draw();
	//1Pが選んでいる枠を表示
	m_SelectFirstCharacter.Draw();
	//2Pが選んでいる枠を表示
	m_SelectSecondCharacter.Draw();

	EnableDepth(true);
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
			if (Controller.IsReturn())
			{
				//操作するコントローラーを設定
				m_pFirstPlayerController = &Controller;
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
			if (Controller.IsReturn())
			{
				//操作するコントローラーを設定
				m_pSecondPlayerController = &Controller;
				break;
			}
		}
	}
}

void SceneSelect::ControllerDisconnect()
{
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
	//コントローラーの情報が入っていたら
	if (m_pFirstPlayerController != nullptr)
	{
		//キャラクターを選んでいる場合
		if (m_SelectFirstCharacter.GetState() == SelectCharacter::SELECTSTATE::SELECT)
		{
			//Bを押すとコントローラーの登録を外す
			if (!m_pFirstPlayerController->IsBack())
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
			if (!m_pSecondPlayerController->IsBack())
			{
				m_pSecondPlayerController = nullptr;
			}
		}
	}
}
