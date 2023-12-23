#include "Character_00.h"

void Character_00::WalkInit()
{
	Character::WalkInit();
	m_CharacterModel.PlayAnime("Walk", true);
	m_AnimeTime = 0.0f;
}

void Character_00::WalkUninit()
{
	Character::WalkUninit();
}

void Character_00::WalkUpdate()
{
	Character::WalkUpdate();

	m_AnimeTime += 0.015f;
	if (m_AnimeTime > 1.0f)
	{
		m_AnimeTime -= 1.0f;
	}

	m_CharacterModel.SetAnimeLerp(m_AnimeTime);
}