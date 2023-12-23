#include "Character_00.h"

void Character_00::DashInit()
{
	Character::DashInit();
	m_CharacterModel.PlayAnime("Dash", true);
	m_AnimeTime = 0.0f;
}

void Character_00::DashUninit()
{
	Character::DashUninit();
}

void Character_00::DashUpdate()
{
	Character::DashUpdate();

	m_AnimeTime += 0.015f;
	if (m_AnimeTime > 1.0f)
	{
		m_AnimeTime -= 1.0f;
	}

	m_CharacterModel.SetAnimeLerp(m_AnimeTime);
}