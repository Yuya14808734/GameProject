#include "SceneResult_DrawWinnerNumState.h"
#include "Player_Controller.h"
#include "Scene.h"
#include "Scene01_Select.h"

void SceneResult_DrawWinnderNumState::Init()
{
	//=====<fadeを始める>=====
	m_pStartWipeFade->SetFadeStart(true);
	m_pStartWipeFade->WipeSetting(0.5f, CVector2(1.0f, 1.0f));

	m_nCount = 0;
}

void SceneResult_DrawWinnderNumState::Uninit()
{
}

void SceneResult_DrawWinnderNumState::Update()
{
	m_nCount++;

	if (m_nCount == 60) { m_pPraiseWinnerPlayerText->StartFadeIn_LetterMove(); }
	if (m_nCount == 120) { m_pPraiseWinnerPlayerText->StartFadeIn_WinnerNum(); }
	if (m_nCount == 210) { m_pPraiseWinnerPlayerText->StartFadeOut_LetterMove(); }
	if (m_nCount == 210) { m_pPraiseWinnerPlayerText->StartFadeOut_WinnerNum(); }



	//=====<フェードの更新>=====
	m_pStartWipeFade->Update();

	//=====<文字を動かす>=====
	m_pPraiseWinnerPlayerText->Update();

	
}

void SceneResult_DrawWinnderNumState::Draw()
{
	//=====<UIの描画>=====
	EnableDepth(false);

	//背景の描画
	m_pBackGround->Draw();

	//[WINNER]のテキスト描画
	m_pPraiseWinnerPlayerText->Draw();

	//フェードの描画
	m_pStartWipeFade->Draw();

	EnableDepth(true);
}
