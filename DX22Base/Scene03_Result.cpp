// ====================================================================================
// �C���N���[�h
// ====================================================================================
#include "Scene03_Result.h"
#include "Scene01_Select.h"
#include "Main.h"
#include "Select01_CharacterList.h"
#include "Main.h"
#include "Player_Controller.h"
#include "CameraManager.h"
#include "Camera02_NoMove.h"


//�X�e�[�g�̃C���N���[�h
#include "SceneResult_DrawWinnerNumState.h"
#include "SceneResult_DrawResult.h"

// ====================================================================================
// static
// ====================================================================================
int SceneResult::m_WinPlayerNum = 0;

void SceneResult::SetWinPlayerNum(int Num)
{
	m_WinPlayerNum = Num;
}

// ====================================================================================
// dynamic
// ====================================================================================

void SceneResult::Init()
{
	//=====<���Ŏg��WindowSize�ϐ����쐬>=====
	CVector2 WindowSize = CVector2(
	static_cast<float>(GetAppWidth()),
	static_cast<float>(GetAppHeight()));

	//=====<�w�i�e�N�X�`���̐ݒ�>=====
	m_BackGround.SetTexture("Assets/BackGroundImage/SelectBackGround.png");
	m_BackGround.m_pos = WindowSize * 0.5f;
	m_BackGround.m_size = WindowSize;

	//=====<�������L�����N�^�[�̔ԍ����擾>=====
	int WinCharacter = static_cast<int>(SelectCharacterList::CHARACTER::NONE);
	switch (m_WinPlayerNum)
	{
	case 1:
	//1P�������Ă�����
	WinCharacter = static_cast<int>(SceneSelect::GetFirstPlayerCharacter());
		break;
	case 2:
	//2P�������Ă�����
	WinCharacter = static_cast<int>(SceneSelect::GetSecondPlayerCharacter());
		break;
	}

	//=====<�L�����N�^�[�̉摜��ݒ�>=====	
	m_pResultWinnerCharacterImage.SetCharacterImage(WinCharacter);

	//=====<�p�l���̉摜��ݒ�>=====
	m_ResultWinnerNumPanel.SetPanelImage(m_WinPlayerNum);

	//=====<�������v���C���[�̔ԍ���\������e�L�X�g�̐ݒ�>=====
	m_PraiseWinnerPlayerText.SetWinPlayerNum(m_WinPlayerNum);

	//=====<��ʑS�̂��B���摜��ݒ�>=====
	m_HideImage.SetTexture("Assets/Texture/WhiteTexture.png");
	m_HideImage.m_pos = WindowSize * 0.5f;
	m_HideImage.m_size = WindowSize;

	//=====<�����Ă��������e�L�X�g�̏ꏊ�ݒ�>=====
	m_PushButtonTextImage.SetPos(CVector3(
		static_cast<float>(GetAppWidth()) * 0.27f,
		static_cast<float>(GetAppHeight()) * 0.7f
		, 0.0f));

	//=====<���̃X�e�[�g��ݒ�>=====
	SetNextState(SceneResult::RESULTSTATE::RESULTDRAWWINNERNUM);
	ChangeNextState();

	//�J�����̍쐬
	CameraNoMove* pCamera = static_cast<CameraNoMove*>(
		CameraManager::GetInstance().CreateCamera<CameraNoMove>("NoMoveCamera"));
	CameraManager::GetInstance().SetSceneCamera("NoMoveCamera");
	pCamera->SetPos(CVector3(0.0f, 0.0f, -10.0f));
	pCamera->SetLookPos(CVector3(0.0f, 0.0f, 0.0f));

	m_efkHnd_FlowerBlizzard = EffectManager::GetManager()->Play(EffectManager::GetEffect("WinnerEffect"), 0, 0, 0);
	EffectManager::GetManager()->SetLocation(m_efkHnd_FlowerBlizzard,
		{ 0.0f,0.0f,0.0f });
	EffectManager::GetManager()->SetScale(m_efkHnd_FlowerBlizzard, 10.0f, 10.0f, 10.0f);
}

void SceneResult::Uninit()
{
	m_ResultStateContext.StateUninit();
	m_ResultStateContext.ReleaseAllState();
}

void SceneResult::Update()
{
	m_ResultStateContext.StateUpdate();

	ChangeNextState();
}

void SceneResult::Draw()
{
	m_ResultStateContext.StateDraw();
	EnableDepth(true);
	EffectManager::EffectDraw(m_efkHnd_FlowerBlizzard);
	EnableDepth(true);

}

State* SceneResult::SetNextState(RESULTSTATE ResultState)
{
	switch (ResultState)
	{
	case SceneResult::RESULTSTATE::RESULTDRAWWINNERNUM:
		m_ResultStateContext.SetNextState(new SceneResult_DrawWinnderNumState());
		break;
	case SceneResult::RESULTSTATE::RESULTDRAW:
		m_ResultStateContext.SetNextState(new SceneResult_DrawResult());
		break;
	}

	return m_ResultStateContext.GetNextState();
}

void SceneResult::ChangeNextState()
{
	if (m_ResultStateContext.GetNextState() != nullptr)
	{
		//�I������
		m_ResultStateContext.StateUninit();

		//���̃X�e�[�g�ɕύX
		m_ResultStateContext.ChangeNextState();

		//���̃X�e�[�g�̊e�ϐ���ݒ�
		SceneResult_BaseState* pSceneResult_BaseState =
			static_cast<SceneResult_BaseState*>(m_ResultStateContext.GetNowState());
		pSceneResult_BaseState->SetSceneResult(this);
		pSceneResult_BaseState->SetBackGround(&m_BackGround);
		pSceneResult_BaseState->SetResultWinnerCharacterImage(&m_pResultWinnerCharacterImage);
		pSceneResult_BaseState->SetFadeInWipe(&m_StartWipeFade);
		pSceneResult_BaseState->SetPushButtonTextImage(&m_PushButtonTextImage);
		pSceneResult_BaseState->SetPraiseWinnerPlayerText(&m_PraiseWinnerPlayerText);
		pSceneResult_BaseState->SetWinnerPlayerNum(&m_WinnerPlayerNum);
		pSceneResult_BaseState->SetResultWinnerNumPanel(&m_ResultWinnerNumPanel);
		pSceneResult_BaseState->SetHideImage(&m_HideImage);
		pSceneResult_BaseState->SetEffect_FlowerBlizzard(&m_efkHnd_FlowerBlizzard);

		//����������
		m_ResultStateContext.StateInit();
	}
}
