#include "Scene04_Load.h"
#include "Scene01_Select.h"

//=========================================
// �e�X�e�[�g�̃C���N���[�h
//=========================================
#include "SceneLoad_BaseState.h"
#include "SceneLoad_CharacterDrawState.h"
#include "SceneLoad_PanelMoveState.h"
#include "SceneLoad_LoadState.h"

void SceneLoad::Init()
{	
	//=====<�`�悷��L�����N�^�[��ݒ�>=====
	for (int i = 0; i < 2; i++)
	{
		m_CharacterMovePanels.push_back(new VersusCharacterPanelMove());
		m_CharacterImage.push_back(new VersusCharacterImageMove());
	}

	SetNextState(SceneLoad::LOADSTATE::PANELMOVE);
	ChangeNextState();
}

void SceneLoad::Uninit()
{
	m_LoadStateContext.StateUninit();
	m_LoadStateContext.ReleaseAllState();

	for (VersusCharacterImageMove* copy : m_CharacterImage)
	{ delete copy; }

	m_CharacterImage.clear();

	for (VersusCharacterPanelMove* copy : m_CharacterMovePanels)
	{ delete copy; }

	m_CharacterMovePanels.clear();
}

void SceneLoad::Update()
{
	m_LoadStateContext.StateUpdate();
	ChangeNextState();
}

void SceneLoad::Draw()
{
	m_LoadStateContext.StateDraw();
}

State* SceneLoad::SetNextState(LOADSTATE LoadState)
{
	switch (LoadState)
	{
	case SceneLoad::LOADSTATE::PANELMOVE:
		m_LoadStateContext.SetNextState(new SceneLoad_PanelMoveState());
		break;
	case SceneLoad::LOADSTATE::CHARACTERDRAW:
		m_LoadStateContext.SetNextState(new SceneLoad_CharacterDrawState());
		break;
	case SceneLoad::LOADSTATE::LOAD:
		m_LoadStateContext.SetNextState(new SceneLoad_LoadState());
		break;
	}

	return m_LoadStateContext.GetNextState();
}

void SceneLoad::ChangeNextState()
{
	if (m_LoadStateContext.GetNextState() != nullptr)
	{
		//�I������
		m_LoadStateContext.StateUninit();

		//���̃X�e�[�g�ɕύX
		m_LoadStateContext.ChangeNextState();

		//���̃X�e�[�g�̊e�ϐ���ݒ�
		SceneLoad_BaseState* pState = static_cast<SceneLoad_BaseState*>
			(m_LoadStateContext.GetNowState());

		pState->SetScene(this);
		pState->SetBackGround(&m_BackGround);
		pState->SetCharacterMovePanels(&m_CharacterMovePanels);
		pState->SetCharacterImages(&m_CharacterImage);
		pState->SetVersusTextAnime(&m_VersusTextAnime);
		
		//����������
		m_LoadStateContext.StateInit();
	}
}
