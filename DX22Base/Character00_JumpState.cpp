#include "Character_00.h"

void Character_00::JumpInit()
{
	Character::JumpInit();
}

void Character_00::JumpUninit()
{
	Character::JumpUninit();
}

void Character_00::JumpUpdate()
{
	Character::JumpUpdate();

	m_AnimeTime = (1.0f - (m_Velocity.y / m_JumpParameter.m_FirstJumpPower)) * 0.93f + 0.15f;

	m_CharacterModel.SetAnimeTime(m_AnimeTime);
}