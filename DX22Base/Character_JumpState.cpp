#include "Character_Base.h"
#include "Input.h"
#include "Attack_Base.h"
#include "XboxKeyboard.h"

void Character::JumpInit()
{
	m_Velocity.y = m_JumpPower;
	m_MoveVector = CVector3::GetZero();
	m_JumpCount++;
}

void Character::JumpUninit()
{

}

void Character::JumpUpdate()
{
	if (m_HitGround)
	{
		ChangeState(Character::STATE::IDLE);
	}


	bool OnButton = false;

	m_Velocity.x =  GetPressLeftStick().x * m_AirSideMoveSpeed;

	if (IsKeyPress(VK_RIGHT))
	{
		m_Velocity.x = m_AirSideMoveSpeed;
		
	}

	if (IsKeyPress(VK_LEFT))
	{
		m_Velocity.x = -m_AirSideMoveSpeed;
	}


	if (m_Velocity.x == 0.0f)
	{
		m_Velocity.x *= m_AirResistance;	//��C��R���|����
	}

	//������x�W�����v���ł���
	if (m_JumpCount < m_MaxJumpCount)
	{
		if (InputTriggerKey(PadButton::RIGHT_SHOULDER) || IsKeyTrigger(VK_UP))
		{
			ChangeState(Character::STATE::JUMP);
		}
	}

	m_Velocity.y += m_Gravity;		//�d�͂��|����

	//�d�͐���(�ő�̗������x�ɂȂ�����)
	if (m_Velocity.y < m_DefaultMaxFallSpeed)
	{
		m_Velocity.y = m_DefaultMaxFallSpeed;
	}

	//�������n�߂���
	if (m_Velocity.y < 0.1f)
	{
		ChangeState(Character::STATE::AIRMOVE);
	}

	m_pos += m_MoveVector;
	m_pos += m_Velocity;
}