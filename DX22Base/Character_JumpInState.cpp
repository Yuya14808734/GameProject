#include "Character_Base.h"
#include "Input.h"
#include "Attack_Base.h"
#include "XboxKeyboard.h"

void Character::JumpInInit()
{
	m_JumpCharageCount = 0;
	m_MoveVector = CVector3::GetZero();
	m_Velocity.x = m_MoveVector.x;
	m_Velocity.y = 0.0f;
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
		m_Velocity.x = m_MoveVector.x;
		m_Velocity.y = m_JumpPower;
	}
	m_pos += m_MoveVector;
	m_pos += m_Velocity;
}