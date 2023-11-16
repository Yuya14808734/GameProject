#include "Attack_Base.h"

void Attack::Attack_Init()
{
	Init();
}

void Attack::Attack_Uninit()
{
	Uninit();
}

void Attack::Attack_Update()
{
	Update();
}

void Attack::Attack_Draw()
{
	Draw();
}

void Attack::SetCharacter(Character * character)
{
	m_pMyCharacter = character;
}
