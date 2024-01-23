#include "SceneResult_DrawResult.h"
#include "Player_Controller.h"
#include "Scene.h"
#include "Scene01_Select.h"

void SceneResult_DrawResult::Init()
{

}

void SceneResult_DrawResult::Uninit()
{

}

void SceneResult_DrawResult::Update()
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

void SceneResult_DrawResult::Draw()
{
	//=====<UI�̕`��>=====
	EnableDepth(false);

	//�w�i�̕`��
	m_pBackGround->Draw();

	//[Win]�̃e�L�X�g�`��
	m_pWinPanelImage->Draw();

	//�L�����N�^�[�摜�̈ʒu��ݒ�
	m_pCharacterImage->m_pos = CVector2(908.0f, 368.0f);
	m_pCharacterImage->m_size = CVector2(435.0f, 640.0f) * 1.3f;
	m_pCharacterImage->Draw();

	//[�����Ă�������]�̕`��
	m_pPushButtonTextImage->Draw();

	EnableDepth(true);
}
