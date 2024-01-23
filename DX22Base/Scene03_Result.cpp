// ====================================================================================
// インクルード
// ====================================================================================
#include "Scene03_Result.h"
#include "Scene01_Select.h"
#include "Main.h"
#include "Select01_CharacterList.h"
#include "Main.h"
#include "Player_Controller.h"


//ステートのインクルード
#include "SceneResult_DrawWinnerNumState.h"
#include "SceneResult_DrawResult.h"

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

	SetNextState(SceneResult::RESULTSTATE::RESULTDRAWWINNERNUM);
	ChangeNextState();
}

void SceneResult::Uninit()
{
}

void SceneResult::Update()
{
	m_ResultStateContext.StateUpdate();

	ChangeNextState();
}

void SceneResult::Draw()
{
	m_ResultStateContext.StateDraw();
}

State* SceneResult::SetNextState(RESULTSTATE ResultState)
{
	switch (ResultState)
	{
	case SceneResult::RESULTSTATE::RESULTDRAWWINNERNUM:
		m_ResultStateContext.SetNextState(new SceneResult_DrawWinnderNumState());
		break;
	case SceneResult::RESULTSTATE::RESULTDRAW:
		m_ResultStateContext.SetNextState(new SceneResult_DrawResult());
		break;
	}

	return m_ResultStateContext.GetNextState();
}

void SceneResult::ChangeNextState()
{
	if (m_ResultStateContext.GetNextState() != nullptr)
	{
		//終了処理
		m_ResultStateContext.StateUninit();

		//次のステートに変更
		m_ResultStateContext.ChangeNextState();

		//今のステートの各変数を設定
		SceneResult_BaseState* pSceneResult_BaseState =
			static_cast<SceneResult_BaseState*>(m_ResultStateContext.GetNowState());
		pSceneResult_BaseState->SetSceneResult(this);
		pSceneResult_BaseState->SetBackGround(&m_BackGround);
		pSceneResult_BaseState->SetCharacterImage(m_pCharacterImage);
		pSceneResult_BaseState->SetFadeInWipe(&m_StartWipeFade);
		pSceneResult_BaseState->SetPushButtonTextImage(&m_PushButtonTextImage);
		pSceneResult_BaseState->SetPraiseWinnerPlayerText(&m_PraiseWinnerPlayerText);
		pSceneResult_BaseState->SetWinnerPlayerNum(&m_WinnerPlayerNum);
		pSceneResult_BaseState->SetWinPanelImage(&m_WinPanelImage);

		//初期化処理
		m_ResultStateContext.StateInit();
	}
}
