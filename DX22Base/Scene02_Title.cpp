#include "Scene02_Title.h"
#include "Main.h"
#include "Player_Controller.h"
#include "Scene01_Select.h"
#include "SceneTitle_TitleScreenState.h"
#include "TextureClass.h"

void SceneTitle::Init()
{
	//===<�摜�̓ǂݍ��ݏ���>===
	m_BackGround.SetTexture("Assets/UI/TitleBackGround.png");
	
	CVector2 WindowSize = 
		CVector2(static_cast<float>(GetAppWidth()), static_cast<float>(GetAppHeight()));

	//===<�w�i�̃T�C�Y�̕ύX>===
	m_BackGround.SetPos(WindowSize * 0.5f);
	m_BackGround.SetSize(WindowSize);

	SetNextState(SceneTitle::TITLESTATE::TITLEDRAW);
	ChangeNextState();
}

void SceneTitle::Uninit()
{
	
}

void SceneTitle::Update()
{
	m_TitleStateContext.StateUpdate();
	ChangeNextState();

	for (PlayerController& pController : PlayerController::GetPlayerControllers())
	{
		if (pController.IsTriggerReturn())
		{
			CScene::SetScene<SceneSelect>();
			break;
		}
	}

}

void SceneTitle::Draw()
{
	//=====<��ʕ`��>=====
	EnableDepth(false);
	
	m_BackGround.Draw();

	m_TitleStateContext.StateDraw();

	
	EnableDepth(true);
}

State* SceneTitle::SetNextState(TITLESTATE TitleState)
{
	switch (TitleState)
	{
	case SceneTitle::TITLESTATE::TITLEDRAW:
		m_TitleStateContext.SetNextState(new SceneTitle_TitleScreenState());
		break;
	case SceneTitle::TITLESTATE::TITLESELECT:
		m_TitleStateContext.SetNextState(nullptr);
		break;
	}

	return m_TitleStateContext.GetNextState();
}

void SceneTitle::ChangeNextState()
{
	if (m_TitleStateContext.GetNextState() != nullptr)
	{
		//�I������
		m_TitleStateContext.StateUninit();

		//���̃X�e�[�g�ɕύX
		m_TitleStateContext.ChangeNextState();

		//���̃X�e�[�g�̊e�ϐ���ݒ�

		//����������
		m_TitleStateContext.StateInit();
	}
}
