#include "Scene04_Load.h"

void SceneLoad::Init()
{
	m_ColorFade.m_color = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
}

void SceneLoad::Uninit()
{

}

void SceneLoad::Update()
{
	m_LoadStateContext.StateUpdate();
	ChangeNextState();
}

void SceneLoad::Draw()
{
}

State* SceneLoad::SetNextState(LOADSTATE LoadState)
{
	switch (LoadState)
	{
	case SceneLoad::LOADSTATE::FADEIN:
		break;
	case SceneLoad::LOADSTATE::ANIMATION:
		break;
	case SceneLoad::LOADSTATE::LOAD:
		break;
	case SceneLoad::LOADSTATE::FADEOUT:
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
		 
		
		//����������
		m_LoadStateContext.StateInit();
	}
}
