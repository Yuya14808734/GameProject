#include "Character_Base.h"
#include "Input.h"
#include "Attack_Base.h"
#include "XboxKeyboard.h"

//---�s������---
//�W�����v
//�U��(��t���[���̂�,�����Ȃǂ�Walk�ɔC����)
//����
//����

void Character::IdleInit()
{

}


void Character::IdleUpdate()
{
	


	if (GetPressLeftStick().x != 0.0f)
	{
		m_State = Character::STATE::WALK;
	}

	if (IsKeyPress(VK_UP))
	{
		m_State = Character::STATE::JUMP;
		m_Velocity.y = m_JumpPower;
	}

	//�U��
	if (false)
	{
		m_State = Character::STATE::ATTACK;
	}

	m_Velocity.y += m_Gravity;
	m_Velocity.x *= m_Friction;

	//�ꉞ�d�͐���������Ă���
	if (m_Velocity.y < m_MaxFallSpeed)
	{
		m_Velocity.y = m_MaxFallSpeed;
	}

	m_pos += m_MoveVector;
	m_pos += m_Velocity;
}

void Character::IdleUninit()
{

}

