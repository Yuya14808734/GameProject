#include "Scene01_Select.h"
#include "CameraManager.h"
#include <array>

PlayerController* SceneSelect::m_pFirstPlayerController = nullptr;
PlayerController* SceneSelect::m_pSecondPlayerController = nullptr;

SelectCharacterList::CHARACTER SceneSelect::m_FirstPlayerCharacter =		SelectCharacterList::CHARACTER::MAX;
SelectCharacterList::CHARACTER SceneSelect::m_SecondPlayerCharacter =	SelectCharacterList::CHARACTER::MAX;

PlayerController* SceneSelect::GetFirstPlayerController()
{
	return m_pFirstPlayerController;
}

PlayerController* SceneSelect::GetSecondPlayerController()
{
	return m_pSecondPlayerController;
}

SelectCharacterList::CHARACTER SceneSelect::GetFirstPlayerCharacter()
{
	return m_FirstPlayerCharacter;
}

SelectCharacterList::CHARACTER SceneSelect::GetSecondPlayerCharacter()
{
	return m_SecondPlayerCharacter;
}

void SceneSelect::Init()
{
	//========<�R���g���[���[���؂�Ă���������폜����>=================
	ControllerDisconnect();

	//=========<2P���̃L�����N�^�[�̐ݒ���s��>=============================

	//��l��
	//�I��ł���L�����N�^�[��ݒ�(�O�̃o�g�������Ă����)
	m_SelectFirstCharacter.SetNowCharacter(m_FirstPlayerCharacter);
	//�R���g���[���[�̐ݒ�(�O�̃o�g�������Ă����)
	m_SelectFirstCharacter.SetController(m_pFirstPlayerController);
	//�I�ׂ�L�����N�^�[�̉摜�ʒu�Ȃǂ�n��
	m_SelectFirstCharacter.SetCharacterList(&m_CharacterList.GetCharacterImageList());
	
	//��l��
	//�I��ł���L�����N�^�[��ݒ�(�O�̃o�g�������Ă����)
	m_SelectSecondCharacter.SetNowCharacter(m_SecondPlayerCharacter);
	//�R���g���[���[�̐ݒ�(�O�̃o�g�������Ă����)
	m_SelectSecondCharacter.SetController(m_pSecondPlayerController);
	//�I�ׂ�L�����N�^�[�̉摜�ʒu�Ȃǂ�n��
	m_SelectSecondCharacter.SetCharacterList(&m_CharacterList.GetCharacterImageList());
	
}

void SceneSelect::Uninit()
{
	
}

void SceneSelect::Update()
{
	//�R���g���[���[���؂�Ă���������폜����
	ControllerDisconnect();

	//�R���g���[���[���Ȃ���
	ControllerConnect();

	//B�{�^���������Ă�����R���g���[���[����������
	ControllerRelease();

	//�L�����N�^�[�̐ݒ�

	//�R���g���[���[���ύX����Ă��邩�m�F
	m_SelectFirstCharacter.ChangeNowController(m_pFirstPlayerController);
	m_SelectSecondCharacter.ChangeNowController(m_pSecondPlayerController);

	//�L�����N�^�[�Z���N�g�̃A�b�v�f�[�g
	m_SelectFirstCharacter.Update();
	m_SelectSecondCharacter.Update();

	//��l���L�����N�^�[��I��ł�����
	if (m_SelectFirstCharacter.IsDecided() && m_SelectSecondCharacter.IsDecided())
	{
		//����{�^����������悤�ɂȂ�
	}
}

void SceneSelect::Draw()
{
	//=====<UI�̕`��>=====
	EnableDepth(false);

	//�L�����N�^�[�摜��`��
	m_CharacterList.Draw();
	//1P���I��ł���g��\��
	m_SelectFirstCharacter.Draw();
	//2P���I��ł���g��\��
	m_SelectSecondCharacter.Draw();

	EnableDepth(true);
}

void SceneSelect::ControllerConnect()
{
	//1P��2P�̐U�蕪��
	//�{�^�������������ꂽ����1P,2P�Ƃ��Ă���
	if (m_pFirstPlayerController == nullptr)
	{
		std::array<PlayerController, 5>& ControllerArray = PlayerController::GetPlayerControllers();

		for (PlayerController& Controller : ControllerArray)
		{
			if (!Controller.IsConnect())
			{
				continue;
			}

			if (Controller.IsReturn())
			{
				m_pFirstPlayerController = &Controller;
				break;
			}
		}
	}
	else if (m_pSecondPlayerController == nullptr)
	{
		std::array<PlayerController, 5>& ControllerArray = PlayerController::GetPlayerControllers();

		for (PlayerController& Controller : ControllerArray)
		{
			if (!Controller.IsConnect())
			{
				continue;
			}

			if (Controller.IsReturn())
			{
				m_pSecondPlayerController = &Controller;
				break;
			}
		}
	}
}

void SceneSelect::ControllerDisconnect()
{
	//�R���g���[���[�̏�񂪓����Ă�����
	if (m_pFirstPlayerController != nullptr)
	{
		//�������Ă���R���g���[���[���q�����Ă��邩
		if(!m_pFirstPlayerController->IsConnect())
		{
			m_pFirstPlayerController = nullptr;
		}
	}

	//�R���g���[���[�̏�񂪓����Ă�����
	if (m_pSecondPlayerController != nullptr)
	{
		//�������Ă���R���g���[���[���q�����Ă��邩
		if(!m_pSecondPlayerController->IsConnect())
		{
			m_pSecondPlayerController = nullptr;
		}
	}
}

void SceneSelect::ControllerRelease()
{
	//�R���g���[���[�̏�񂪓����Ă�����
	if (m_pFirstPlayerController != nullptr)
	{
		//�L�����N�^�[��I��ł���ꍇ
		if (m_SelectFirstCharacter.GetState() == SelectCharacter::SELECTSTATE::SELECT)
		{
			//B�������ƃR���g���[���[�̓o�^���O��
			if (!m_pFirstPlayerController->IsBack())
			{
				m_pFirstPlayerController = nullptr;
			}
		}
	}

	//�R���g���[���[�̏�񂪓����Ă�����
	if (m_pSecondPlayerController != nullptr)
	{
		//�L�����N�^�[��I��ł���ꍇ
		if (m_SelectSecondCharacter.GetState() == SelectCharacter::SELECTSTATE::SELECT)
		{
			//B�������ƃR���g���[���[�̓o�^���O��
			if (!m_pSecondPlayerController->IsBack())
			{
				m_pSecondPlayerController = nullptr;
			}
		}
	}
}
