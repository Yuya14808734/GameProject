#include "Character_Base.h"
#include "Input.h"
#include "Attack_Base.h"
#include "XboxKeyboard.h"

void Character::JumpInInit()
{
	m_JumpCharageCount = 0;
}

void Character::JumpInUninit()
{

}

void Character::JumpInUpdate()
{
	m_JumpCharageCount++;

	if (m_JumpCharageCount > 3)
	{
		ChangeState(Character::STATE::JUMP);
		m_Velocity.y = m_JumpPower;
	}
}