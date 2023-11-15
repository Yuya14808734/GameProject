#include "Character_Base.h"

int Character::m_NewPlayerBit = 0x00;

void Character::InitPlayerBit()
{
	m_NewPlayerBit = 0x01;
}

int Character::GetNewPlayerBit()
{
	int ReturnBit = m_NewPlayerBit;
	m_NewPlayerBit = m_NewPlayerBit << 1;
	return ReturnBit;
}

void Character::Character_Init()
{
	Init();
}

void Character::Character_Uninit()
{
	Uninit();
}
