// ====================================================================================
// �C���N���[�h
// ====================================================================================
#include "Scene03_Result.h"
#include "Scene01_Select.h"
#include "Main.h"
#include "Select01_CharacterList.h"
#include "Main.h"
#include "Player_Controller.h"


//�X�e�[�g�̃C���N���[�h
#include "SceneResult_DrawWinnerNumState.h"
#include "SceneResult_DrawResult.h"

// ====================================================================================
// static
// ====================================================================================
int SceneResult::m_WinCharacterNum = 0;

void SceneResult::SetWinPlayerNum(int Num)
{
	m_WinCharacterNum = Num;
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

	//=====<�L�����N�^�[�̉摜��ݒ�>=====
	switch (m_WinCharacterNum)
	{
	case 1:
	//1P�������Ă�����
	WinCharacter 
		= static_cast<int>(SceneSelect::GetFirstPlayerCharacter());
	m_WinPanelImage.SetTexture("Assets/UI/Win1Player.png");
		break;
	case 2:
	//2P�������Ă�����
	WinCharacter 
		= static_cast<int>(SceneSelect::GetSecondPlayerCharacter());
	m_WinPanelImage.SetTexture("Assets/UI/Win2Player.png");
		break;
	default:
	//�قڂȂ����Ǒ��̏ꍇ
		WinCharacter = 0;
		m_WinPanelImage.SetTexture("Assets/UI/Win1Player.png");
		break;
	}

	//=====<[Win]�̉摜�̏ꏊ�ݒ�>=====
	m_WinPanelImage.m_pos = CVector3(320.0f, 205.0f, 0.0f);
	m_WinPanelImage.m_size = CVector2(400.0f,151.0f);

	//=====<�L�����N�^�[�摜�̎擾>=====
	switch (static_cast<SelectCharacterList::CHARACTER>(WinCharacter))
	{
	case SelectCharacterList::CHARACTER::NONE:
	case SelectCharacterList::CHARACTER::MAX:
		WinCharacter =
			static_cast<int>(SelectCharacterList::CHARACTER::UNITYCHAN);
		break;
	}

	m_pCharacterImage = 
		&((SelectCharacterList::GetCharacterStandImageList())[WinCharacter]);

	//=====<�����Ă��������e�L�X�g�̏ꏊ�ݒ�>=====
	m_PushButtonTextImage.SetPos(CVector3(
		static_cast<float>(GetAppWidth()) * 0.27f,
		static_cast<float>(GetAppHeight()) * 0.7f
		, 0.0f));

	SetNextState(SceneResult::RESULTSTATE::RESULTDRAWWINNERNUM);
	ChangeNextState();
}

void SceneResult::Uninit()
{
}

void SceneResult::Update()
{
	m_ResultStateContext.StateUpdate();

	ChangeNextState();
}

void SceneResult::Draw()
{
	m_ResultStateContext.StateDraw();
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
		pSceneResult_BaseState->SetCharacterImage(m_pCharacterImage);
		pSceneResult_BaseState->SetFadeInWipe(&m_StartWipeFade);
		pSceneResult_BaseState->SetPushButtonTextImage(&m_PushButtonTextImage);
		pSceneResult_BaseState->SetPraiseWinnerPlayerText(&m_PraiseWinnerPlayerText);
		pSceneResult_BaseState->SetWinnerPlayerNum(&m_WinnerPlayerNum);
		pSceneResult_BaseState->SetWinPanelImage(&m_WinPanelImage);

		//����������
		m_ResultStateContext.StateInit();
	}
}
