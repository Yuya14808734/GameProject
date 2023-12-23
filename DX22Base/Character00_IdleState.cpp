#include "Character_00.h"

void Character_00::IdleInit()
{
	Character::IdleInit();
	m_CharacterModel.PlayAnime("Idle", true);
	m_AnimeTime = 0.0f;
}

void Character_00::IdleUninit()
{
	Character::IdleUninit();
}

void Character_00::IdleUpdate()
{
	Character::IdleUpdate();

	m_AnimeTime += 0.015f;
	if (m_AnimeTime > 1.0f)
	{
		m_AnimeTime -= 1.0f;
	}

	m_CharacterModel.SetAnimeLerp(m_AnimeTime);
}