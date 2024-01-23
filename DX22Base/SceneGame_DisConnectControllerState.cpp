#include "SceneGame_DisConnectControllerState.h"
#include "Main.h"
#include "Player_Controller.h"
#include "Scene01_Select.h"
#include "CameraManager.h"

void SceneGame_DisConnectControllerState::Init()
{
	CVector2 WindowSize = CVector2(
		static_cast<float>(GetAppWidth()),
		static_cast<float>(GetAppHeight())
	);

	m_DissConnectControllerTextImage.SetTexture("Assets/UI/DisConnectControllerImage.png");
	m_DissConnectControllerTextImage.SetPos(WindowSize * 0.5f);
	m_DissConnectControllerTextImage.SetSize(WindowSize);

	m_ReturnCount = 0.0f;

	CameraManager::GetInstance().StopCamera();
}

void SceneGame_DisConnectControllerState::Uninit()
{
	CameraManager::GetInstance().ReStartCamera();
}

void SceneGame_DisConnectControllerState::Update()
{
	//=====<���̊֐����Ŏg���ϐ����쐬>=====
	bool ReturnSelectScene = false;
	m_ReturnCount += 1.0f / 60.0f;

	//=====<�Z���N�g�ɖ߂�>=====
	for (PlayerController& Controller : PlayerController::GetPlayerControllers())
	{
		if (Controller.IsTriggerReturn())
		{
			ReturnSelectScene = true;
			break;
		}
	}

	if (m_ReturnCount > SceneChangeWaitTime)
	{
		ReturnSelectScene = true;
	}

	//=====<�Z���N�g�V�[����ǂݍ���>=====
	if (ReturnSelectScene)
	{
		//�V�[���̐؂�ւ�
		CScene::SetScene<SceneSelect>();
	}
}

void SceneGame_DisConnectControllerState::Draw()
{
	//=====<�w�i�̕`��>=====
	m_pBackGround->Draw();

	//=====<�X�e�[�W�̕`��>=====
	m_pStage->Stage_Draw();

	//=====<�L�����N�^�[�̕`��>=====
	for (Character* copy : (*m_pCharacters))
	{
		copy->Character_Draw();
	}

	//=====<�G�t�F�N�g�̕`��>=====
	for (EffectBase* pEffect : (*m_pEffects))
	{
		pEffect->Draw();
	}

	//=====<UI�̕`��>=====
	EnableDepth(false);

	for (Character* copy : (*m_pCharacters))
	{
		copy->Character_UIDraw();
	}

	m_pStockCountUI->Draw();
	
	//�Z���N�g�ɖ߂�̕`��
	m_DissConnectControllerTextImage.Draw();

	EnableDepth(true);

}
