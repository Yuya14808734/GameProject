#include "Select00_Character.h"

float SelectCharacter::m_AlphaCount = 0.0f;

void SelectCharacter::AlphaUpdate()
{
	m_AlphaCount += 1.0f / 60.0f;

	while(m_AlphaCount > 100.0f)
	{
		m_AlphaCount -= 100.0f;
	}
}

SelectCharacter::SelectCharacter()
{
	m_isDecided = false;

	//�t���[���̓ǂݍ���
	m_FrameImage.SetTexture("Assets/CharacterImage/SelectFrame.png");
	m_FrameImage.m_size = CVector2(276.0f, 400.0f) * 0.8f;

	//�Ȃɂ��Ȃ����Ă��Ȃ����̃t�H���g�̓ǂݍ���
	m_NoConnectText.SetTexture("Assets/UI/NoConnectText.png");
	m_NoConnectText.m_size = CVector2(400.0f, 221.0f) * 0.5f;

	//�Ȃɂ��Ȃ����Ă��Ȃ����̔w�i�̓ǂݍ���
	m_NoConnectBackGround.SetTexture("Assets/UI/NoConnectBackGround.png");
	m_NoConnectBackGround.m_size = CVector2(400.0f, 261.0f) * 0.5f;

	//�q���������ɉ��ɂȂ��������̉摜
	m_ControllerImage.m_pos = CVector2(-120.0f, -60.0f);
	m_ControllerImage.m_size = CVector2(128.0f, 128.0f);

	//�I�΂ꂽ�Ƃ��ɉf���摜
	m_SelectedImage.SetTexture("Assets/CharacterImage/SelectedImage.png");
	m_SelectedImage.m_size = CVector2(150.0f, 150.0f);
}

SelectCharacter::~SelectCharacter()
{

}

void SelectCharacter::Update()
{
	//�R���g���[���[��ݒ肵�Ă��Ȃ��ꍇ
	if (m_pSelectController == nullptr)
	{
		return;
	}

	switch (m_SelectState)
	{
	case SelectCharacter::SELECTSTATE::SELECT:
		SelectUpdate();
		break;
	case SelectCharacter::SELECTSTATE::ANIMATION:
		AnimationUpdate();
		break;
	case SelectCharacter::SELECTSTATE::DECIDED:
		DecidedUpdate();
		break;
	}
}

void SelectCharacter::Draw()
{
	//=========<�I�ׂ�L�����N�^�[�̃��X�g���ݒ肳��Ă��Ȃ��ꍇ(Scene��Init�Őݒ肵�ĉ�����)>===========
	if (m_pCharacterImageList == nullptr)
	{
		return;
	}

	if (m_pCharacterIconImageList == nullptr)
	{
		return;
	}

	//=========<�R���g���[���[���ڑ�����Ă��Ȃ��ꍇ(�R���g���[���[���ڑ������܂ő҂�)>===========
	if (m_pSelectController == nullptr)
	{
		m_NoConnectBackGround.Draw();	//�w�i�̕`��
		m_NoConnectText.m_color.w = (sinf((m_AlphaCount / 2.0f) * 3.14f) + 1.0f) / 2.0f;
		m_NoConnectText.Draw();			//�e�L�X�g�̕`��
		return;
	}

	//=========<�g�̕\��>===========
	m_FrameImage.m_pos = (*m_pCharacterImageList)[m_NowSelectCharacter].GetPos();
	m_FrameImage.m_size = (*m_pCharacterImageList)[m_NowSelectCharacter].GetSize();
	m_FrameImage.Draw();

	//=========<�ڑ������R���g���[���[�ɂ���ĉ摜��ς���>===========
	m_ControllerImage.Draw();

	//=========<�L�����N�^�[�̃A�C�R����`��>===========
	(*m_pCharacterIconImageList)[m_NowSelectCharacter].m_BasePos = m_BasePos;
	(*m_pCharacterIconImageList)[m_NowSelectCharacter].Draw();

	//=========<�I��ł�����L�����N�^�[�̃A�C�R�����B�������̕`��>===========
	if(m_isDecided)
	{
		m_SelectedImage.Draw();
	}
}

void SelectCharacter::SetController(PlayerController* Controller)
{
	m_pSelectController = Controller;
}

void SelectCharacter::ChangeNowController(PlayerController* Controller)
{
	//���̃t���[���ŃR���g���[���[���ύX���ꂽ�ꍇ
	if (m_pSelectController != Controller)
	{
		//�R���g���[���[�̏㏑��
		m_pSelectController = Controller;

		//=========<�R���g���[���[���ڑ�����Ă��Ȃ����>===========
		if (Controller == nullptr)
		{
			m_ControllerImage.ReleaseTexture();
			return;
		}

		//=========<�R���g���[���[���ڑ�����Ă���>===========
		
		//������������
		m_SelectState = SelectCharacter::SELECTSTATE::SELECT;
		m_isDecided = false;

		//���̃R���g���[���[�̃^�C�v
		switch (Controller->GetControllerType())
		{
		case PlayerController::PLAYCONTROLLERTYPE::GAMEPAD:
			m_ControllerImage.SetTexture("Assets/UI/ControllerImage.png");
			break;
		case PlayerController::PLAYCONTROLLERTYPE::KEYBOARD:
			m_ControllerImage.SetTexture("Assets/UI/KeyboardImage.png");
			break;
		}
	}
}

void SelectCharacter::SetNowCharacter(SelectCharacterList::CHARACTER NowCharacter)
{
	m_NowSelectCharacter = static_cast<int>(NowCharacter);
	m_NowSelectCharacter =	//�L�����N�^�[���ُ�Ȑ����̏ꍇ�A����Ȑ����ɂ���
		m_NowSelectCharacter % static_cast<int>(SelectCharacterList::CHARACTER::MAX);
}

bool SelectCharacter::IsDecided()
{
	return m_isDecided;
}

SelectCharacter::SELECTSTATE SelectCharacter::GetState()
{
	return m_SelectState;
}

void SelectCharacter::SetPos(const CVector3& pos)
{
	//�e�C���[�W�̃x�[�X�ʒu��ύX
	m_NoConnectBackGround.m_BasePos =
	m_NoConnectText.m_BasePos =
	m_ControllerImage.m_BasePos =
	m_SelectedImage.m_BasePos =
	m_BasePos = pos;
}

const CVector3& SelectCharacter::GetPos() const
{
	return m_BasePos;
}

void SelectCharacter::SetCharacterList(std::array<Image2D, static_cast<int>(SelectCharacterList::CHARACTER::MAX)>* pCharacterImageList)
{
	m_pCharacterImageList = pCharacterImageList;
}

void SelectCharacter::SetCharacterIconList(std::array<Image2D, static_cast<int>(SelectCharacterList::CHARACTER::MAX)>* pCharacterIconImageList)
{
	m_pCharacterIconImageList = pCharacterIconImageList;
}

void SelectCharacter::SelectUpdate()
{
	//�E����������
	if (m_pSelectController->GetTriggerRightArrow())
	{
		m_NowSelectCharacter++;
		m_NowSelectCharacter =
			m_NowSelectCharacter % static_cast<int>(SelectCharacterList::CHARACTER::MAX);

		m_SelectState = SelectCharacter::SELECTSTATE::ANIMATION;
	}

	//������������
	if (m_pSelectController->GetTriggerLeftArrow())
	{
		m_NowSelectCharacter--;

		m_NowSelectCharacter =
			(m_NowSelectCharacter + static_cast<int>(SelectCharacterList::CHARACTER::MAX))
			% static_cast<int>(SelectCharacterList::CHARACTER::MAX);

		m_SelectState = SelectCharacter::SELECTSTATE::ANIMATION;
	}

	//����{�^������������
	if (m_pSelectController->IsTriggerReturn())
	{
		m_isDecided = true;
		m_SelectState = SelectCharacter::SELECTSTATE::DECIDED;
	}
}

void SelectCharacter::AnimationUpdate()
{
	m_SelectState = SelectCharacter::SELECTSTATE::SELECT;
}

void SelectCharacter::DecidedUpdate()
{
	//����{�^������������
	if (m_pSelectController->IsPressBack())
	{
		m_isDecided = false;
		m_SelectState = SelectCharacter::SELECTSTATE::SELECT;
	}
}