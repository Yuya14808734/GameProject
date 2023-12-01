#include "Character_Base.h"
#include "Input.h"
#include "Attack_Base.h"
#include "XboxKeyboard.h"

void Character::AttackInit()
{
	switch (m_NowAttack)
	{
	case Character::ATTACK::ATTACK_11:
		Attack11_Init();
		break;
	case Character::ATTACK::ATTACK_12:
		Attack12_Init();
		break;
	case Character::ATTACK::ATTACK_13:
		Attack13_Init();
		break;
	case Character::ATTACK::ATTACK_S2:
		AttackS2_Init();
		break;
	case Character::ATTACK::ATTACK_S4:
		AttackS4_Init();
		break;
	case Character::ATTACK::ATTACK_AIRN:
		AttackAirN_Init();
		break;
	case Character::ATTACK::SPECIAL_N:
		SpecialN_Init();
		break;
	case Character::ATTACK::SPECIAL_AIRN:
		SpecialAirN_Init();
		break;
	case Character::ATTACK::MAX:
		break;
	default:
		break;
	}
}

void Character::AttackUninit()
{
	switch (m_NowAttack)
	{
	case Character::ATTACK::ATTACK_11:
		Attack11_Uninit();
		break;
	case Character::ATTACK::ATTACK_12:
		Attack12_Uninit();
		break;
	case Character::ATTACK::ATTACK_13:
		Attack13_Uninit();
		break;
	case Character::ATTACK::ATTACK_S2:
		AttackS2_Uninit();
		break;
	case Character::ATTACK::ATTACK_S4:
		AttackS4_Uninit();
		break;
	case Character::ATTACK::ATTACK_AIRN:
		AttackAirN_Uninit();
		break;
	case Character::ATTACK::SPECIAL_N:
		SpecialN_Uninit();
		break;
	case Character::ATTACK::SPECIAL_AIRN:
		SpecialAirN_Uninit();
		break;
	case Character::ATTACK::MAX:
		break;
	default:
		break;
	}
}

void Character::AttackUpdate()
{
	switch (m_NowAttack)
	{
	case Character::ATTACK::ATTACK_11:
		Attack11_Update();
		break;
	case Character::ATTACK::ATTACK_12:
		Attack12_Update();
		break;
	case Character::ATTACK::ATTACK_13:
		Attack13_Update();
		break;
	case Character::ATTACK::ATTACK_S2:
		AttackS2_Update();
		break;
	case Character::ATTACK::ATTACK_S4:
		AttackS4_Update();
		break;
	case Character::ATTACK::ATTACK_AIRN:
		AttackAirN_Update();
		break;
	case Character::ATTACK::SPECIAL_N:
		SpecialN_Update();
		break;
	case Character::ATTACK::SPECIAL_AIRN:
		SpecialAirN_Update();
		break;
	case Character::ATTACK::MAX:
		break;
	default:
		break;
	}
}