#include "SceneResult_DrawWinnerNumState.h"
#include "Player_Controller.h"
#include "Scene.h"
#include "Scene01_Select.h"

void SceneResult_DrawWinnderNumState::Init()
{
	//=====<fade���n�߂�>=====
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



	//=====<�t�F�[�h�̍X�V>=====
	m_pStartWipeFade->Update();

	//=====<�����𓮂���>=====
	m_pPraiseWinnerPlayerText->Update();

	
}

void SceneResult_DrawWinnderNumState::Draw()
{
	//=====<UI�̕`��>=====
	EnableDepth(false);

	//�w�i�̕`��
	m_pBackGround->Draw();

	//[WINNER]�̃e�L�X�g�`��
	m_pPraiseWinnerPlayerText->Draw();

	//�t�F�[�h�̕`��
	m_pStartWipeFade->Draw();

	EnableDepth(true);
}
