#include "Select00_Character.h"

SelectCharacter::SelectCharacter()
{
	m_isDecided = false;

	//�t���[���̓ǂݍ���
	m_FrameImage.SetTexture("Assets/CharacterImage/SelectFrame.png");
	m_FrameImage.m_size = CVector2(276.0f, 400.0f) * 0.8f;
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
	if (m_pCharacterImageList == nullptr)
	{
		return;
	}

	if (m_pSelectController == nullptr)
	{
		return;
	}

	//�g�̕\��
	m_FrameImage.m_pos = (*m_pCharacterImageList)[m_NowSelectCharacter].GetPos();
	m_FrameImage.m_size = (*m_pCharacterImageList)[m_NowSelectCharacter].GetSize();
	m_FrameImage.Draw();
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

void SelectCharacter::SetCharacterList(std::array<Image2D, static_cast<int>(SelectCharacterList::CHARACTER::MAX)>* pCharacterImageList)
{
	m_pCharacterImageList = pCharacterImageList;
}

void SelectCharacter::SelectUpdate()
{
	//�E����������
	if (m_pSelectController->GetRightArrow())
	{
		m_NowSelectCharacter++;
		m_NowSelectCharacter =
			m_NowSelectCharacter % static_cast<int>(SelectCharacterList::CHARACTER::MAX);

		m_SelectState = SelectCharacter::SELECTSTATE::ANIMATION;
	}

	//������������
	if (m_pSelectController->GetLeftArrow())
	{
		m_NowSelectCharacter--;

		m_NowSelectCharacter =
			(m_NowSelectCharacter + static_cast<int>(SelectCharacterList::CHARACTER::MAX))
			% static_cast<int>(SelectCharacterList::CHARACTER::MAX);

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
	m_SelectState = SelectCharacter::SELECTSTATE::SELECT;
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
