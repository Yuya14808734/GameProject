#include "SceneResult_DrawResult.h"
#include "Player_Controller.h"
#include "Scene.h"
#include "Scene01_Select.h"

void SceneResult_DrawResult::Init()
{
	m_pResultWinnerCharacterImage->DrawStart(1.0f);
	m_nFrameCount = 0;
	m_pPushButtonTextImage->SetScale(0.9f);
}

void SceneResult_DrawResult::Uninit()
{

}

void SceneResult_DrawResult::Update()
{
	//=====<�t���[���̍X�V>=====
	m_nFrameCount++;

	//=====<������x���Ԃ���������p�l����`��>=====
	if (m_nFrameCount == 30)
	{
		m_pResultWinnerNumPanel->DrawStart(1.0f);
	}

	//=====<�L�����N�^�[��`�悵�Ȃ���ړ�����>=====
	m_pResultWinnerCharacterImage->Update();

	//=====<�p�l����s�����ɂ��Ȃ��珬��������>=====
	m_pResultWinnerNumPanel->Update();

	//=====<�{�^����������悤�ɂ���>=====
	if (m_nFrameCount > 120)
	{
		//=====<�����Ăق����{�^���̃e�L�X�g��؂�ւ���>=====
		m_pPushButtonTextImage->Update();

		//=====<�e�R���g���[���[���擾����Enter��A�������ꂽ�玟�̃V�[���Ɉړ�����>=====
		for (auto copyController : PlayerController::GetPlayerControllers())
		{
			if (copyController.IsTriggerReturn())
			{
				CScene::SetScene<SceneSelect>();
			}
		}
	}		
}

void SceneResult_DrawResult::Draw()
{
	//=====<UI�̕`��>=====
	EnableDepth(false);

	//�w�i�̕`��
	m_pBackGround->Draw();

	//[Win]�̃e�L�X�g�`��
	m_pResultWinnerNumPanel->Draw();

	//�L�����N�^�[�摜�̈ʒu��ݒ�
	m_pResultWinnerCharacterImage->Draw();

	//[�����Ă�������]�̕`��
	if (m_nFrameCount > 90)
	{
		m_pPushButtonTextImage->Draw();
	}

	EnableDepth(true);
}
