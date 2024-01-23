// ====================================================================================
// �C���N���[�h
// ====================================================================================
#include "Scene03_Result.h"
#include "Scene01_Select.h"
#include "Main.h"
#include "Select01_CharacterList.h"
#include "Main.h"
#include "Player_Controller.h"

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

	//=====<fade���n�߂�>=====
	m_StartWipeFade.SetFadeStart(true);
	m_StartWipeFade.WipeSetting(1.0f, CVector2(1.0f, 1.0f));
}

void SceneResult::Uninit()
{
}

void SceneResult::Update()
{
	//=====<fade�̃A�b�v�f�[�g>=====
	m_StartWipeFade.Update();

	//=====<�����Ăق����{�^���̃e�L�X�g��؂�ւ���>=====
	m_PushButtonTextImage.Update();
	
	//=====<�e�R���g���[���[���擾����Enter��A�������ꂽ�玟�̃V�[���Ɉړ�����>=====
	for (auto copyController : PlayerController::GetPlayerControllers())
	{
		if (copyController.IsTriggerReturn())
		{
			CScene::SetScene<SceneSelect>();
		}
	}
}

void SceneResult::Draw()
{
	//=====<UI�̕`��>=====
	EnableDepth(false);

	//�w�i�̕`��
	m_BackGround.Draw();

	//[Win]�̃e�L�X�g�`��
	m_WinPanelImage.Draw();

	//�L�����N�^�[�摜�̈ʒu��ݒ�
	m_pCharacterImage->m_pos = CVector2(908.0f, 368.0f);
	m_pCharacterImage->m_size = CVector2(435.0f, 640.0f) * 1.3f;
	m_pCharacterImage->Draw();

	//[�����Ă�������]�̕`��
	m_PushButtonTextImage.Draw();

	//�t�F�[�h�̕`��
	m_StartWipeFade.Draw();

	EnableDepth(true);
}
