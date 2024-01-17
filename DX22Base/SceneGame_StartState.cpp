#include "SceneGame_StartState.h"
#include "CameraManager.h"

void SceneGame_StartState::Init()
{
	m_Count = 0;

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

	if (m_Count == 2 * 60)
	{
		m_pGameStartCountUI->SetNumDraw(2);
	}

	if (m_Count == 3 * 60)
	{
		m_pGameStartCountUI->SetNumDraw(1);
	}

	if (m_Count == 4 * 60)
	{
		m_pGameStartCountUI->SetGoDraw(true);
		CameraManager::GetInstance().SetSceneCamera("GameCamera");
		m_pGameScene->SetNextState(SceneGame::GAMESTATE::GAMEPLAY);
	}
}

void SceneGame_StartState::Draw()
{
	//=====<�X�e�[�W�̕`��>=====
	m_pStage->Stage_Draw();

	//=====<�L�����N�^�[�̕`��>=====
	for (Character* copy : (*m_pCharacters))
	{
		copy->Character_Draw();
	}

	//=====<UI�̕`��>=====
	EnableDepth(false);

	for (Character* copy : (*m_pCharacters))
	{
		copy->Character_UIDraw();
	}

	if (m_Count > 1 * 60)
	{
		m_pGameStartCountUI->Draw();
	}

	EnableDepth(true);
}
