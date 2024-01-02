#include "Select01_CharacterList.h"
#include "Input.h"

SelectCharacterList::SelectCharacterList()
{
	const char* CharacterImageFilePath[static_cast<int>(CHARACTER::MAX)] =
	{
		"Assets/CharacterImage/StandImage_UnityChan.png",
	};

	const char* CharacterIconImageFilePath[static_cast<int>(CHARACTER::MAX)] =
	{
		"Assets/CharacterImage/IconImage_UnityChan.png",
	};

	const CVector3 IconPos[static_cast<int>(CHARACTER::MAX)] =
	{
		CVector3(640.0f, 280.0f, 0.0f),
	};

	m_CharacterIconSize = CVector2(200.0f, 200.0f) * 0.8f;

	//�e�摜�̈ʒu�̐ݒ�
	for (int i = 0;i < static_cast<int>(CHARACTER::MAX);i++)
	{
		//�L�����N�^�[�̗����G�摜�̓ǂݍ���
		m_CharacterStandImages[i].SetTexture(CharacterImageFilePath[i]);

		//�L�����N�^�[�̃A�C�R���̉摜�̓ǂݍ���
		m_CharacterIconImages[i].SetTexture(CharacterIconImageFilePath[i]);

		m_CharacterIconPos[i] = IconPos[i];

	}
}

SelectCharacterList::~SelectCharacterList()
{

}

void SelectCharacterList::Draw()
{
	//�e�摜�̈ʒu�̐ݒ�
	for (int i = 0; i < static_cast<int>(CHARACTER::MAX); i++)
	{
		m_CharacterIconImages[i].m_BasePos = CVector3::GetZero();
		m_CharacterIconImages[i].m_pos = m_CharacterIconPos[i];
		m_CharacterIconImages[i].m_size = m_CharacterIconSize;

		m_CharacterIconImages[i].Draw();
	}
}

std::array<Image2D, static_cast<int>(SelectCharacterList::CHARACTER::MAX)>& SelectCharacterList::GetCharacterStandImageList()
{
	return m_CharacterStandImages;
}

std::array<Image2D, static_cast<int>(SelectCharacterList::CHARACTER::MAX)>& SelectCharacterList::GetCharacterIconImageList()
{
	return m_CharacterIconImages;
}

std::array<CVector3, static_cast<int>(SelectCharacterList::CHARACTER::MAX)>& SelectCharacterList::GetIconPos()
{
	return m_CharacterIconPos;
}

CVector2& SelectCharacterList::GetIconSize()
{
	return m_CharacterIconSize;
}
