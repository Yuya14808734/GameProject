// ====================================================================================
// �C���N���[�h
// ====================================================================================

#include "Scene01_Select.h"
#include "CameraManager.h"
#include <array>
#include "Main.h"
#include "Scene.h"
#include "Scene04_Load.h"

// ====================================================================================
// static
// ====================================================================================

PlayerController* SceneSelect::m_pFirstPlayerController = nullptr;
PlayerController* SceneSelect::m_pSecondPlayerController = nullptr;

SelectCharacterList::CHARACTER SceneSelect::m_FirstPlayerCharacter =	SelectCharacterList::CHARACTER::NONE;
SelectCharacterList::CHARACTER SceneSelect::m_SecondPlayerCharacter =	SelectCharacterList::CHARACTER::NONE;

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

// ====================================================================================
// dynamic
// ====================================================================================

void SceneSelect::Init()
{
	const CVector2 WindowSize(static_cast<float>(GetAppWidth()), static_cast<float>(GetAppHeight()));
	const CVector2 WindowCenterPos = WindowSize * 0.5f;

	//========<�R���g���[���[���؂�Ă���������폜����>=================
	ControllerDisconnect();
	//=====================================================================

	//=========<2P���̃L�����N�^�[�̐ݒ���s��>=============================
	//��l��
	//�R���g���[���[�̐ݒ�(�O�̃o�g�������Ă����)
	m_SelectFirstCharacter.ChangeNowController(m_pFirstPlayerController);
	//1P���I��ł���L�����N�^�[�Ȃǂ�\������ʒu
	m_SelectFirstCharacter.SetBoardPos(CVector3(WindowCenterPos.x - 200.0f, WindowCenterPos.y + 200.0f, 0.0f));
	//�{�[�h�̐F��ύX
	m_SelectFirstCharacter.SetBoardColor(SelectCharacter::BOARDCOLOR::RED);
	//�I��ł���L�����N�^�[��ݒ�(�O�̃o�g�������Ă����)
	m_SelectFirstCharacter.SetNowCharacter(m_FirstPlayerCharacter);	
	//�I�ׂ�L�����N�^�[�̉摜�ʒu�Ȃǂ�n��
	m_SelectFirstCharacter.SetCharacterList(&m_CharacterList);
	//�����G�̈ʒu�̐ݒ�
	m_SelectFirstCharacter.SetLerpStandCharacterDrawPos(CVector3(0.0f, 400.0f, 0.0f), CVector3(200.0f,400.0f,0.0f));

	//��l��
	//�R���g���[���[�̐ݒ�(�O�̃o�g�������Ă����)
	m_SelectSecondCharacter.ChangeNowController(m_pSecondPlayerController);
	//2P���I��ł���L�����N�^�[�Ȃǂ�\������ʒu
	m_SelectSecondCharacter.SetBoardPos(CVector3(WindowCenterPos.x + 200.0f, WindowCenterPos.y + 200.0f, 0.0f));
	//�{�[�h�̐F��ύX
	m_SelectSecondCharacter.SetBoardColor(SelectCharacter::BOARDCOLOR::BLUE);
	//�I��ł���L�����N�^�[��ݒ�(�O�̃o�g�������Ă����)
	m_SelectSecondCharacter.SetNowCharacter(m_SecondPlayerCharacter);
	//�I�ׂ�L�����N�^�[�̉摜�ʒu�Ȃǂ�n��
	m_SelectSecondCharacter.SetCharacterList(&m_CharacterList);
	//�����G�̈ʒu�̐ݒ�
	m_SelectSecondCharacter.SetLerpStandCharacterDrawPos(CVector3(WindowSize.x, 400.0f, 0.0f), CVector3(WindowSize.x - 200.0f, 400.0f, 0.0f));
	//=====================================================================
	
	m_CharactersText.SetTexture("Assets/UI/CharactersText.png");
	m_CharactersText.m_pos = CVector3(WindowCenterPos.x, 100.0f, 0.0f);
	m_CharactersText.m_size = CVector2(400.0f, 194.0f);

	m_BackGroundImage.SetTexture("Assets/BackGroundImage/SelectBackGround.png");
	m_BackGroundImage.m_pos = WindowCenterPos;
	m_BackGroundImage.m_size = WindowSize;

	m_ReadyToFightTextImage.StartSlide();

	m_ColorFade.m_pos = WindowCenterPos;
	m_ColorFade.m_size = WindowSize;
	m_ColorFade.m_color = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	m_isLoadNextScene = false;

	m_state = SceneSelect::SELECTSTATE::SELECT;

	m_pBGM = new BGM("Assets/Music/Select.wav", true);
	m_pBGM->Start();
}

void SceneSelect::Uninit()
{
	m_pBGM->Stop();
	delete m_pBGM;
}

void SceneSelect::Update()
{
	switch (m_state)
	{
	case SceneSelect::SELECTSTATE::SELECT:
		SelectUpdate();
		break;
	case SceneSelect::SELECTSTATE::FADE:
		FadeUpdate();
		break;
	}	
}

void SceneSelect::SelectUpdate()
{
	//=========<�R���g���[���[���؂�Ă���������폜����>=========
	ControllerDisconnect();

	//=========<�R���g���[���[���Ȃ���>=========
	ControllerConnect();

	//=========<B�{�^���������Ă�����R���g���[���[����������>=========
	ControllerRelease();

	//=========<�L�����N�^�[��I�����鏈��>=========
	//�L�������[�̃A���t�@�ύX
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
		m_ReadyToFightTextImage.Update();

		//�Q�[���X�^�[�g�{�^����������悤�ɂ���
		if (m_pFirstPlayerController->IsTriggerReturn() || m_pSecondPlayerController->IsTriggerReturn())
		{
			//�L�����N�^�[�̐ݒ�
			m_FirstPlayerCharacter = m_SelectFirstCharacter.GetSelectCharacter();
			m_SecondPlayerCharacter = m_SelectSecondCharacter.GetSelectCharacter();

			m_ColorFade.SetFadeTime(0.3f);
			m_ColorFade.SetFadeStart(true);
			m_state = SELECTSTATE::FADE;			
		}
	}
}

void SceneSelect::FadeUpdate()
{
	m_ColorFade.Update();

	if (m_ColorFade.GetFadeEnd())
	{
		//�V�[���̐؂�ւ�
		CScene::SetScene<SceneLoad>();
	}
}

void SceneSelect::Draw()
{
	//=====<UI�̕`��>=======================================================
	EnableDepth(false);

	m_BackGroundImage.Draw();

	//=====<�L�����N�^�[�摜��`��>=========================================
	//1P���I��ł���L�����N�^�[�̗����G�̕`��
	m_SelectFirstCharacter.StandCharacterDraw();
	//2P���I��ł���L�����N�^�[�̗����G�̕`��
	m_SelectSecondCharacter.StandCharacterDraw();
	//�L�����N�^�[��I�ԂƂ��Ɏg���A�C�R���̕`��
	m_CharacterList.Draw();

	m_CharactersText.Draw();
	//======================================================================
	
	//=====<1P�̕`��>=======================================================
	//�L�����N�^�[�ƃR���g���[���[��\������{�[�h��`��
	m_SelectFirstCharacter.BoardDraw();
	//�L�����N�^�[��I�ԃt���[���̕`��
	m_SelectFirstCharacter.SelectFrameDraw();
	//======================================================================

	//=====<2P�̕`��>=======================================================
	//�L�����N�^�[�ƃR���g���[���[��\������{�[�h��`��
	m_SelectSecondCharacter.BoardDraw();
	//�L�����N�^�[��I�ԃt���[���̕`��
	m_SelectSecondCharacter.SelectFrameDraw();
	//======================================================================

	//=========<��l���L�����N�^�[��I��ł�����>=========
	if (m_SelectFirstCharacter.IsDecided() && m_SelectSecondCharacter.IsDecided())
	{
		m_ReadyToFightTextImage.Draw();
	}

	m_ColorFade.Draw();

	EnableDepth(true);
	//======================================================================
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
			if (Controller.IsTriggerReturn())
			{
				//���삷��R���g���[���[��ݒ�
				m_pFirstPlayerController = &Controller;
				m_pFirstPlayerController->UnTriggerNowFrame();
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
			if (Controller.IsTriggerReturn())
			{
				//���삷��R���g���[���[��ݒ�
				m_pSecondPlayerController = &Controller;
				m_pSecondPlayerController->UnTriggerNowFrame();
				break;
			}
		}
	}
}

void SceneSelect::ControllerDisconnect()
{
	//�R���g���[���[���q�����Ă��Ȃ��ꍇ�A�R���g���[���[�̏���nullptr�ɂ���

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
	//B�{�^������������R���g���[���[�̓o�^���O���Ă��

	//�R���g���[���[�̏�񂪓����Ă�����
	if (m_pFirstPlayerController != nullptr)
	{
		//�L�����N�^�[��I��ł���ꍇ
		if (m_SelectFirstCharacter.GetState() == SelectCharacter::SELECTSTATE::SELECT)
		{
			//B�������ƃR���g���[���[�̓o�^���O��
			if (m_pFirstPlayerController->IsTriggerBack())
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
			if (m_pSecondPlayerController->IsTriggerBack())
			{
				m_pSecondPlayerController = nullptr;
			}
		}
	}
}


