#include "Character_00.h"

void Character_00::JumpInInit()
{
	Character::JumpInInit();
	m_CharacterModel.PlayAnime("Jump", false);
	m_AnimeTime = 0.0f;
}

void Character_00::JumpInUninit()
{
	Character::JumpInUninit();
}

void Character_00::JumpInUpdate()
{
	Character::JumpInUpdate();
	m_AnimeTime = (static_cast<float>(m_JumpCharageCount) / 3.0f) * 0.05f + 0.1f;

	m_CharacterModel.SetAnimeTime(m_AnimeTime);
}


