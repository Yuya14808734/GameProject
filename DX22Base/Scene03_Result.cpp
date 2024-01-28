// ====================================================================================
// インクルード
// ====================================================================================
#include "Scene03_Result.h"
#include "Scene01_Select.h"
#include "Main.h"
#include "Select01_CharacterList.h"
#include "Main.h"
#include "Player_Controller.h"
#include "CameraManager.h"
#include "Camera02_NoMove.h"


//ステートのインクルード
#include "SceneResult_DrawWinnerNumState.h"
#include "SceneResult_DrawResult.h"

// ====================================================================================
// static
// ====================================================================================
int SceneResult::m_WinPlayerNum = 0;

void SceneResult::SetWinPlayerNum(int Num)
{
	m_WinPlayerNum = Num;
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
	switch (m_WinPlayerNum)
	{
	case 1:
	//1Pが勝っていたら
	WinCharacter = static_cast<int>(SceneSelect::GetFirstPlayerCharacter());
		break;
	case 2:
	//2Pが勝っていたら
	WinCharacter = static_cast<int>(SceneSelect::GetSecondPlayerCharacter());
		break;
	}

	//=====<キャラクターの画像を設定>=====	
	m_pResultWinnerCharacterImage.SetCharacterImage(WinCharacter);

	//=====<パネルの画像を設定>=====
	m_ResultWinnerNumPanel.SetPanelImage(m_WinPlayerNum);

	//=====<勝ったプレイヤーの番号を表示するテキストの設定>=====
	m_PraiseWinnerPlayerText.SetWinPlayerNum(m_WinPlayerNum);

	//=====<画面全体を隠す画像を設定>=====
	m_HideImage.SetTexture("Assets/Texture/WhiteTexture.png");
	m_HideImage.m_pos = WindowSize * 0.5f;
	m_HideImage.m_size = WindowSize;

	//=====<押してくださいテキストの場所設定>=====
	m_PushButtonTextImage.SetPos(CVector3(
		static_cast<float>(GetAppWidth()) * 0.27f,
		static_cast<float>(GetAppHeight()) * 0.7f
		, 0.0f));

	//=====<次のステートを設定>=====
	SetNextState(SceneResult::RESULTSTATE::RESULTDRAWWINNERNUM);
	ChangeNextState();

	//カメラの作成
	CameraNoMove* pCamera = static_cast<CameraNoMove*>(
		CameraManager::GetInstance().CreateCamera<CameraNoMove>("NoMoveCamera"));
	CameraManager::GetInstance().SetSceneCamera("NoMoveCamera");
	pCamera->SetPos(CVector3(0.0f, 0.0f, -10.0f));
	pCamera->SetLookPos(CVector3(0.0f, 0.0f, 0.0f));

	m_efkHnd_FlowerBlizzard = EffectManager::GetManager()->Play(EffectManager::GetEffect("WinnerEffect"), 0, 0, 0);
	EffectManager::GetManager()->SetLocation(m_efkHnd_FlowerBlizzard,
		{ 0.0f,0.0f,0.0f });
	EffectManager::GetManager()->SetScale(m_efkHnd_FlowerBlizzard, 10.0f, 10.0f, 10.0f);
}

void SceneResult::Uninit()
{
	m_ResultStateContext.StateUninit();
	m_ResultStateContext.ReleaseAllState();
}

void SceneResult::Update()
{
	m_ResultStateContext.StateUpdate();

	ChangeNextState();
}

void SceneResult::Draw()
{
	m_ResultStateContext.StateDraw();
	EnableDepth(true);
	EffectManager::EffectDraw(m_efkHnd_FlowerBlizzard);
	EnableDepth(true);

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
		pSceneResult_BaseState->SetResultWinnerCharacterImage(&m_pResultWinnerCharacterImage);
		pSceneResult_BaseState->SetFadeInWipe(&m_StartWipeFade);
		pSceneResult_BaseState->SetPushButtonTextImage(&m_PushButtonTextImage);
		pSceneResult_BaseState->SetPraiseWinnerPlayerText(&m_PraiseWinnerPlayerText);
		pSceneResult_BaseState->SetWinnerPlayerNum(&m_WinnerPlayerNum);
		pSceneResult_BaseState->SetResultWinnerNumPanel(&m_ResultWinnerNumPanel);
		pSceneResult_BaseState->SetHideImage(&m_HideImage);
		pSceneResult_BaseState->SetEffect_FlowerBlizzard(&m_efkHnd_FlowerBlizzard);

		//初期化処理
		m_ResultStateContext.StateInit();
	}
}
