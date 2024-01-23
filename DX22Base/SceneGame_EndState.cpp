#include "SceneGame_EndState.h"
#include "Scene.h"
#include "Scene03_Result.h"
#include "Main.h"
#include "FadeIn00_GameEnd.h"

void SceneGame_EndState::Init()
{
	//=====<�����摜�̐ݒ�>=====
	m_pGameEndTextUI->StartAnimetion();
	m_pGameEndTextUI->SetStartSize(CVector2(640.0f, 304.0f) * 2.0f);
	m_pGameEndTextUI->SetEndSize(CVector2(640.0f, 304.0f));
	m_SceneChangeCount = 0;
	
	//=====<�����_�[�^�[�Q�b�g�֕`�悷�邩�̕ϐ��̏�����>=====
	m_WipeTextureWrite = false;
}

void SceneGame_EndState::Uninit()
{

}

void SceneGame_EndState::Update()
{
	m_pGameEndTextUI->Update();

	m_SceneChangeCount++;

	if (m_SceneChangeCount > 60 * 3)
	{
		//���̃V�[���Ƀ��U���g���ʂ𑗂�
		int WinPlayerNum = 0;
		for (Character* pCharacter : (*m_pCharacters))
		{
			if (pCharacter->GetStock() > 0)
			{
				unsigned int BitPlayerNum = pCharacter->GetCharacterBit();

				WinPlayerNum =
					static_cast<int>(log2f(static_cast<float>(BitPlayerNum)));
				WinPlayerNum++;
			}
		}

		//�������v���C���[�ԍ���ݒ�
		SceneResult::SetWinPlayerNum(WinPlayerNum);

		//=====<���̕`��Ń����_�[�^�[�Q�b�g�ɏ������݂��s��>=====
		m_WipeTextureWrite = true;

		//�V�[���̐؂�ւ�
		CScene::SetScene<SceneResult>();
	}
}

void SceneGame_EndState::Draw()
{
	//=====<�����_�[�^�[�Q�b�g�֕`��>=====
	SetRenderTargetTexture();

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

	m_pGameEndTextUI->Draw();

	EnableDepth(true);
}

void SceneGame_EndState::SetRenderTargetTexture()
{
	//=====<�t�F�[�h�Ŏg�������_�[�^�[�Q�b�g��ݒ肷�邩>=====
	if (m_WipeTextureWrite)
	{
		//=====<���C�v�Ŏg���e�N�X�`������郌���_�[�^�[�Q�b�g��ݒ�>=====
		FadeInWipe::SetRenderTargets_WipeTexture();

		//=====<�[�x�o�b�t�@�L��>=====
		EnableDepth(true);

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

		m_pGameEndTextUI->Draw();

		EnableDepth(true);

		//=====<�f�t�H���g�̃����_�[�^�[�Q�b�g�ɖ߂�>=====
		SetDefaultRenderTargets();
		EnableDepth(true);

		//=====<���`�悵�������_�[�^�[�Q�b�g��n���Ă��>=====
		FadeInWipe::SetRenderTargets_WipeTexture();
	}
}
