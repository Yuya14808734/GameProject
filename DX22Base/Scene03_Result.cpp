// ====================================================================================
// インクルード
// ====================================================================================
#include "Scene03_Result.h"
#include "Scene01_Select.h"
#include "Main.h"
#include "Select01_CharacterList.h"
#include "Main.h"
#include "Player_Controller.h"

// ====================================================================================
// static
// ====================================================================================
int SceneResult::m_WinCharacterNum = 0;

void SceneResult::SetWinPlayerNum(int Num)
{
	m_WinCharacterNum = Num;
}

// ====================================================================================
// dynamic
// ====================================================================================

void SceneResult::Init()
{
	//=====<下で使うWindowSize変数を作成>=====
	CVector2 WindowSize = CVector2(
	static_cast<float>(GetAppWidth()),
	static_cast<float>(GetAppHeight()));

	//=====<背景テクスチャの設定>=====
	m_BackGround.SetTexture("Assets/BackGroundImage/SelectBackGround.png");
	m_BackGround.m_pos = WindowSize * 0.5f;
	m_BackGround.m_size = WindowSize;

	//=====<勝ったキャラクターの番号を取得>=====
	int WinCharacter = static_cast<int>(SelectCharacterList::CHARACTER::NONE);

	//=====<キャラクターの画像を設定>=====
	switch (m_WinCharacterNum)
	{
	case 1:
	//1Pが勝っていたら
	WinCharacter 
		= static_cast<int>(SceneSelect::GetFirstPlayerCharacter());
	m_WinPanelImage.SetTexture("Assets/UI/Win1Player.png");
		break;
	case 2:
	//2Pが勝っていたら
	WinCharacter 
		= static_cast<int>(SceneSelect::GetSecondPlayerCharacter());
	m_WinPanelImage.SetTexture("Assets/UI/Win2Player.png");
		break;
	default:
	//ほぼないけど他の場合
		WinCharacter = 0;
		m_WinPanelImage.SetTexture("Assets/UI/Win1Player.png");
		break;
	}

	//=====<[Win]の画像の場所設定>=====
	m_WinPanelImage.m_pos = CVector3(320.0f, 205.0f, 0.0f);
	m_WinPanelImage.m_size = CVector2(400.0f,151.0f);

	//=====<キャラクター画像の取得>=====
	switch (static_cast<SelectCharacterList::CHARACTER>(WinCharacter))
	{
	case SelectCharacterList::CHARACTER::NONE:
	case SelectCharacterList::CHARACTER::MAX:
		WinCharacter =
			static_cast<int>(SelectCharacterList::CHARACTER::UNITYCHAN);
		break;
	}

	m_pCharacterImage = 
		&((SelectCharacterList::GetCharacterStandImageList())[WinCharacter]);

	//=====<押してくださいテキストの場所設定>=====
	m_PushButtonTextImage.SetPos(CVector3(
		static_cast<float>(GetAppWidth()) * 0.27f,
		static_cast<float>(GetAppHeight()) * 0.7f
		, 0.0f));

	//=====<fadeを始める>=====
	m_StartWipeFade.SetFadeStart(true);
	m_StartWipeFade.WipeSetting(1.0f, CVector2(1.0f, 1.0f));
}

void SceneResult::Uninit()
{
}

void SceneResult::Update()
{
	//=====<fadeのアップデート>=====
	m_StartWipeFade.Update();

	//=====<押してほしいボタンのテキストを切り替える>=====
	m_PushButtonTextImage.Update();
	
	//=====<各コントローラーを取得してEnterかAが押されたら次のシーンに移動する>=====
	for (auto copyController : PlayerController::GetPlayerControllers())
	{
		if (copyController.IsTriggerReturn())
		{
			CScene::SetScene<SceneSelect>();
		}
	}
}

void SceneResult::Draw()
{
	//=====<UIの描画>=====
	EnableDepth(false);

	//背景の描画
	m_BackGround.Draw();

	//[Win]のテキスト描画
	m_WinPanelImage.Draw();

	//キャラクター画像の位置を設定
	m_pCharacterImage->m_pos = CVector2(908.0f, 368.0f);
	m_pCharacterImage->m_size = CVector2(435.0f, 640.0f) * 1.3f;
	m_pCharacterImage->Draw();

	//[押してください]の描画
	m_PushButtonTextImage.Draw();

	//フェードの描画
	m_StartWipeFade.Draw();

	EnableDepth(true);
}
