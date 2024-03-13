#include "SceneGame_StartState.h"
#include "CameraManager.h"
#include "ShaderManager.h"
#include "SoundManager.h"

void SceneGame_StartState::Init()
{
	m_Count = 0;

	CameraManager::GetInstance().SetSceneCamera("GameStartCamera");

	for (auto copy : (*m_pCharacters))
	{
		copy->SetNextState(Character::STATE::State_StartAnime);
		copy->ChangeNextState();
	}

	
}

void SceneGame_StartState::Uninit()
{
	for (auto copy : (*m_pCharacters))
	{
		copy->SetNextState(Character::STATE::State_Idle);
		copy->ChangeNextState();
	}
}

void SceneGame_StartState::Update()
{
	//=====<�L�����N�^�[�̃A�b�v�f�[�g>=====

	//�����ōU����ړ��Ȃǂ̃A�b�v�f�[�g���s��
	for (std::vector<Character*>::iterator it = m_pCharacters->begin();
		it != m_pCharacters->end(); it++)
	{
		(*it)->Character_Update();				//�L�����N�^�[�̃A�b�v�f�[�g���s��
	}

	m_pGameStartCountUI->Update();

	m_Count++;

	if (m_Count == 60)
	{
		m_pGameStartCountUI->SetNumDraw(3);
		SoundManager::PlaySE("CountDown");
	}

	if (m_Count == 2 * 60)
	{
		m_pGameStartCountUI->SetNumDraw(2);
		SoundManager::PlaySE("CountDown");
	}

	if (m_Count == 3 * 60)
	{
		m_pGameStartCountUI->SetNumDraw(1);
		SoundManager::PlaySE("CountDown");
	}

	if (m_Count == 4 * 60)
	{
		m_pGameStartCountUI->SetGoDraw(true);
		//CameraManager::GetInstance().SetSceneCamera("GameCamera");
		m_pGameScene->SetNextState(SceneGame::GAMESTATE::GAMEPLAY);
		SoundManager::PlaySE("CountStart");
	}
}

void SceneGame_StartState::Draw()
{
	//=====<�V���h�E�}�b�v�̕`��>=====
	m_pGameScene->LightCameraDraw();
	CameraManager::GetInstance().SetSceneCamera("GameStartCamera");

	//=====<�w�i�̕`��>=====
	EnableDepth(false);
	m_pBackGround->Draw();
	EnableDepth(true);

	//=====<�e�̃V�F�[�_�[�̐ݒ�>=====
	DirectX::XMMATRIX LVP = 
		m_pLightCamera->GetViewMatrix_TypeXMMAXRIX() *
		m_pLightCamera->GetProjectionMatrix_TypeXMMAXRIX();
	DirectX::XMFLOAT4X4 matrix;
	DirectX::XMStoreFloat4x4(&matrix, 
		DirectX::XMMatrixTranspose(LVP));
	m_pLightLVPMatrixBuffer->Write(&matrix);
	m_pLightLVPMatrixBuffer->BindVS(2);
	SetTexturePS(m_pShadowMapRenderTarget->GetResource(),1);
	m_pLightCamera->SetParameter();

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

	//�ŏ��̈�b�͕`�悵�Ȃ�
	if (m_Count > 1 * 60)
	{
		m_pGameStartCountUI->Draw();
	}

	EnableDepth(true);
}
