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
	CVector2 WindowSize = CVector2(
	static_cast<float>(GetAppWidth()),
	static_cast<float>(GetAppHeight()));

	m_BackGround.SetTexture("Assets/BackGroundImage/SelectBackGround.png");
	m_BackGround.m_pos = WindowSize * 0.5f;
	m_BackGround.m_size = WindowSize;

	int WinCharacter = static_cast<int>(SelectCharacterList::CHARACTER::NONE);

	//=====<キャラクターの画像を設定
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

	m_WinPanelImage.m_pos = CVector3(320.0f, 205.0f, 0.0f);
	m_WinPanelImage.m_size = CVector2(400.0f,151.0f);

	m_pCharacterImage = 
		&((SelectCharacterList::GetCharacterStandImageList())[WinCharacter]);

	m_PushButtonTextImage.SetPos(CVector3(
		static_cast<float>(GetAppWidth()) * 0.27f,
		static_cast<float>(GetAppHeight()) * 0.7f
		, 0.0f));
}

void SceneResult::Uninit()
{
}

void SceneResult::Update()
{
	m_PushButtonTextImage.Update();

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
	//=====<UIの描画>=======================================================
	EnableDepth(false);
	m_BackGround.Draw();	
	m_WinPanelImage.Draw();

	m_pCharacterImage->m_pos = CVector2(908.0f, 368.0f);
	m_pCharacterImage->m_size = CVector2(435.0f, 640.0f) * 1.3f;
	m_pCharacterImage->Draw();

	m_PushButtonTextImage.Draw();

	EnableDepth(true);
	//======================================================================
}
