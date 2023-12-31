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
	//=====================================================================

	//=========<2P���̃L�����N�^�[�̐ݒ���s��>=============================
	//��l��
	//1P���I��ł���L�����N�^�[�Ȃǂ�\������ʒu
	m_SelectFirstCharacter.SetPos(CVector3(100.0f, 400.0f, 0.0f));
	//�I��ł���L�����N�^�[��ݒ�(�O�̃o�g�������Ă����)
	m_SelectFirstCharacter.SetNowCharacter(m_FirstPlayerCharacter);
	//�R���g���[���[�̐ݒ�(�O�̃o�g�������Ă����)
	m_SelectFirstCharacter.SetController(m_pFirstPlayerController);
	//�I�ׂ�L�����N�^�[�̉摜�ʒu�Ȃǂ�n��
	m_SelectFirstCharacter.SetCharacterList(&m_CharacterList.GetCharacterImageList());
	m_SelectFirstCharacter.SetCharacterIconList(&m_CharacterList.GetCharacterIconImageList());

	//��l��
	//2P���I��ł���L�����N�^�[�Ȃǂ�\������ʒu
	m_SelectSecondCharacter.SetPos(CVector3(600.0f, 400.0f, 0.0f));
	//�I��ł���L�����N�^�[��ݒ�(�O�̃o�g�������Ă����)
	m_SelectSecondCharacter.SetNowCharacter(m_SecondPlayerCharacter);
	//�R���g���[���[�̐ݒ�(�O�̃o�g�������Ă����)
	m_SelectSecondCharacter.SetController(m_pSecondPlayerController);
	//�I�ׂ�L�����N�^�[�̉摜�ʒu�Ȃǂ�n��
	m_SelectSecondCharacter.SetCharacterList(&m_CharacterList.GetCharacterImageList());
	m_SelectSecondCharacter.SetCharacterIconList(&m_CharacterList.GetCharacterIconImageList());
	//=====================================================================
	
}

void SceneSelect::Uninit()
{
	
}

void SceneSelect::Update()
{
	//=========<�R���g���[���[���؂�Ă���������폜����>=========
	ControllerDisconnect();

	//=========<�R���g���[���[���Ȃ���>=========
	ControllerConnect();

	//=========<B�{�^���������Ă�����R���g���[���[����������>=========
	ControllerRelease();

	//=========<�L�����N�^�[��I�����鏈��>=========
	SelectCharacter::AlphaUpdate();

	//�R���g���[���[���ύX����Ă��邩�m�F
	m_SelectFirstCharacter.ChangeNowController(m_pFirstPlayerController);
	m_SelectSecondCharacter.ChangeNowController(m_pSecondPlayerController);

	//�L�����N�^�[�Z���N�g�̃A�b�v�f�[�g
	m_SelectFirstCharacter.Update();
	m_SelectSecondCharacter.Update();

	//=========<��l���L�����N�^�[��I��ł�����>=========
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

	//1P���ڑ�����Ă��Ȃ����
	if (m_pFirstPlayerController == nullptr)
	{
		//���ׂẴR���g���[���[���擾
		std::array<PlayerController, 5>& ControllerArray = PlayerController::GetPlayerControllers();

		for (PlayerController& Controller : ControllerArray)
		{
			//2P�Ɠ����R���g���[���[�ł͂Ȃ���
			if (&Controller == m_pSecondPlayerController)
			{
				continue;
			}

			//�R���g���[���[���q�����Ă��邩
			if (!Controller.IsConnect())
			{
				continue;
			}

			//Enter��A�{�^����������Ă�����
			if (Controller.IsReturn())
			{
				//���삷��R���g���[���[��ݒ�
				m_pFirstPlayerController = &Controller;
				break;
			}
		}
	}
	//2P���ڑ�����Ă��Ȃ����
	else if (m_pSecondPlayerController == nullptr)
	{
		//���ׂẴR���g���[���[���擾
		std::array<PlayerController, 5>& ControllerArray = PlayerController::GetPlayerControllers();

		for (PlayerController& Controller : ControllerArray)
		{
			//1P�Ɠ����R���g���[���[�ł͂Ȃ���
			if (&Controller == m_pFirstPlayerController)
			{
				continue;
			}

			//�R���g���[���[���q�����Ă��邩
			if (!Controller.IsConnect())
			{
				continue;
			}

			//Enter��A�{�^����������Ă�����
			if (Controller.IsReturn())
			{
				//���삷��R���g���[���[��ݒ�
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
