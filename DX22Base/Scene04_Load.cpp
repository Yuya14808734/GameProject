#include "Scene04_Load.h"
#include "Scene01_Select.h"
#include "Main.h"

//=========================================
// �e�X�e�[�g�̃C���N���[�h
//=========================================
#include "SceneLoad_BaseState.h"
#include "SceneLoad_CharacterDrawState.h"
#include "SceneLoad_PanelMoveState.h"
#include "SceneLoad_LoadState.h"
#include "CameraManager.h"
#include "Camera02_NoMove.h"

void SceneLoad::Init()
{	
	CVector2 WindowSize(
	static_cast<float>(GetAppWidth()),
	static_cast<float>(GetAppHeight())
		);

	//�J�����̍쐬
	CameraNoMove* pCamera = static_cast<CameraNoMove*>(
		CameraManager::GetInstance().CreateCamera<CameraNoMove>("NoMoveCamera"));
	CameraManager::GetInstance().SetSceneCamera("NoMoveCamera");
	pCamera->SetPos(CVector3(0.0f, 0.0f, -10.0f));
	pCamera->SetLookPos(CVector3(0.0f, 0.0f, 0.0f));

	//=====<�`�悷��L�����N�^�[��ݒ�>=====
	for (int i = 0; i < 2; i++)
	{
		m_CharacterMovePanels.push_back(new VersusCharacterPanelMove());
		m_CharacterImage.push_back(new VersusCharacterImageMove());
	}

	m_HideImage.SetTexture("Assets/Texture/WhiteTexture.png");
	m_HideImage.m_color = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	m_HideImage.m_size = WindowSize;
	m_HideImage.m_pos = WindowSize * 0.5f;

	m_BackGround.SetTexture("Assets/BackGroundImage/LoadBackGround.png");
	m_BackGround.m_size = WindowSize;
	m_BackGround.m_pos = WindowSize * 0.5f;

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

	//�G�t�F�N�g�̏I��
	EffectManager::GetManager()->StopAllEffects();
	CameraManager::GetInstance().DestroyAllCamera(true);
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
		pState->SetHideImage(&m_HideImage);
		pState->SetCharacterMovePanels(&m_CharacterMovePanels);
		pState->SetCharacterImages(&m_CharacterImage);
		pState->SetVersusTextAnime(&m_VersusTextAnime);
		pState->SetVersusIconImage(&m_VersusIcon);
		pState->SetFireSparks(&m_efkHnd_FireSparks);
		
		//����������
		m_LoadStateContext.StateInit();
	}
}
