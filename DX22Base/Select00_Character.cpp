#include "Select00_Character.h"

SelectCharacter::SelectCharacter()
{
	m_isDecided = false;
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

}

void SelectCharacter::SetController(PlayerController* Controller)
{
	m_pSelectController = Controller;
}

void SelectCharacter::ChangeNowController(PlayerController* Controller)
{
	//�O�̃t���[���ŃR���g���[���[���Ȃ��A���̃t���[���ŃR���g���[���[���ڑ����ꂽ�ꍇ
	if (m_pSelectController == nullptr && Controller != nullptr)
	{
		//������������
		m_SelectState = SelectCharacter::SELECTSTATE::SELECT;
		m_isDecided = false;
	}

	m_pSelectController = Controller;
}

void SelectCharacter::SetNowCharacter(CHARACTER NowCharacter)
{
	m_NowSelectCharacter = static_cast<int>(NowCharacter);
	m_NowSelectCharacter =	//�L�����N�^�[���ُ�Ȑ����̏ꍇ�A����Ȑ����ɂ���
		m_NowSelectCharacter % static_cast<int>(SelectCharacter::CHARACTER::MAX);
}

bool SelectCharacter::IsDecided()
{
	return m_isDecided;
}

SelectCharacter::SELECTSTATE SelectCharacter::GetState()
{
	return m_SelectState;
}

void SelectCharacter::SelectUpdate()
{
	//�E����������
	if (m_pSelectController->GetRightArrow())
	{
		m_NowSelectCharacter++;
		m_NowSelectCharacter =
			m_NowSelectCharacter % static_cast<int>(SelectCharacter::CHARACTER::MAX);

		m_SelectState = SelectCharacter::SELECTSTATE::ANIMATION;
	}

	//������������
	if (m_pSelectController->GetLeftArrow())
	{
		m_NowSelectCharacter--;

		m_NowSelectCharacter =
			(m_NowSelectCharacter + static_cast<int>(SelectCharacter::CHARACTER::MAX))
			% static_cast<int>(SelectCharacter::CHARACTER::MAX);

		m_SelectState = SelectCharacter::SELECTSTATE::ANIMATION;
	}

	//����{�^������������
	if (m_pSelectController->IsReturn())
	{
		m_isDecided = true;
		m_SelectState = SelectCharacter::SELECTSTATE::DECIDED;
	}
}

void SelectCharacter::AnimationUpdate()
{

}

void SelectCharacter::DecidedUpdate()
{
	//����{�^������������
	if (m_pSelectController->IsBack())
	{
		m_isDecided = false;
		m_SelectState = SelectCharacter::SELECTSTATE::SELECT;
	}
}
