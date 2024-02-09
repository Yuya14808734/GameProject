#include "SceneResult_DrawWinnerNumState.h"
#include "Player_Controller.h"
#include "Scene.h"
#include "Scene01_Select.h"

void SceneResult_DrawWinnderNumState::Init()
{
	//=====<fade���n�߂�>=====
	m_pStartWipeFade->SetFadeStart(true);
	m_pStartWipeFade->WipeSetting(0.5f, CVector2(1.0f, 1.0f));

	m_pHideImage->m_color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 0.75f);

	m_nCount = 0;
}

void SceneResult_DrawWinnderNumState::Uninit()
{
	//=====<���C�v�Ŏg���e�N�X�`������郌���_�[�^�[�Q�b�g���폜>=====
	FadeInWipe::ReleaseRenderTargets_WipeTexture();
}

void SceneResult_DrawWinnderNumState::Update()
{
	m_nCount++;

	//=====<�e�摜�̃t�F�[�h�C���E�A�E�g�̃^�C�~���O�ݒ�>=====
	if (m_nCount == 60)  { m_pPraiseWinnerPlayerText->StartFadeIn_LetterMove(0.8f); }
	if (m_nCount == 120) { m_pPraiseWinnerPlayerText->StartFadeIn_WinnerNum(0.5f);	}
	if (m_nCount == 250) { m_pPraiseWinnerPlayerText->StartFadeOut_LetterMove(0.5f);}
	if (m_nCount == 250) { m_pPraiseWinnerPlayerText->StartFadeOut_WinnerNum(0.5f); }

	//=====<�t�F�[�h�̍X�V>=====
	m_pStartWipeFade->Update();

	//=====<�����𓮂���>=====
	m_pPraiseWinnerPlayerText->Update();

	//=====<�����B���Ă���摜�̃A���t�@��0�ɂ��Ă���>=====
	const int AlphaChangeFrame = 300;
	if (m_nCount > AlphaChangeFrame)
	{
		float Percent = static_cast<float>(m_nCount - AlphaChangeFrame) / 20.0f;
		Percent = 1.0f - Percent;
		m_pHideImage->m_color.w = 0.75f * Percent;
	}

	//=====<���̃X�e�[�g�̓ǂݍ���>=====
	if (m_nCount > 340)
	{
		m_pSceneResult->SetNextState(SceneResult::RESULTSTATE::RESULTDRAW);
	}	
}

void SceneResult_DrawWinnderNumState::Draw()
{
	//=====<UI�̕`��>=====
	EnableDepth(false);

	//�w�i�̕`��
	m_pBackGround->Draw();

	//�����B���Ă�锒���摜�̕`��
	m_pHideImage->Draw();

	//[WINNER]�Ə������v���C���[�̔ԍ��̃e�L�X�g�`��
	m_pPraiseWinnerPlayerText->Draw();

	//�t�F�[�h�̕`��
	m_pStartWipeFade->Draw();

	EnableDepth(true);
}
