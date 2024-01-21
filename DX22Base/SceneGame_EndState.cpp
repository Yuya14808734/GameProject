#include "SceneGame_EndState.h"
#include "Scene.h"
#include "Scene03_Result.h"

void SceneGame_EndState::Init()
{
	//�Q�[���G���h�ƕ`�悷��
	m_pGameEndTextUI->StartAnimetion();
	m_pGameEndTextUI->SetStartSize(CVector2(640.0f, 304.0f) * 2.0f);
	m_pGameEndTextUI->SetEndSize(CVector2(640.0f, 304.0f));

	m_SceneChangeCount = 0;
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

		//�V�[���̐؂�ւ�
		CScene::SetScene<SceneResult>();
	}
}

void SceneGame_EndState::Draw()
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

	m_pGameEndTextUI->Draw();

	EnableDepth(true);
}
