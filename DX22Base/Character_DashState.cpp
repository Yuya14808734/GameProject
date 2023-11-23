#include "Character_Base.h"
#include "Input.h"
#include "Attack_Base.h"
#include "XboxKeyboard.h"

void Character::DashInit()
{

}

void Character::DashUninit()
{

}

void Character::DashUpdate()
{
	//---�s������---
	//
	//�U��
	//����
	//����

	bool NoButton = true;

	if (IsKeyPress(VK_RIGHT))
	{
		if (m_MoveVector.x < -0.01f)
		{
			//���ɍs���Ă����ꍇ�A���C���|����
			m_MoveVector.x *= m_Friction;
		}
		else
		{
			m_MoveVector.x = m_DashSpeed;
		}

		NoButton = false;
	}

	if (IsKeyPress(VK_LEFT))
	{
		if (m_MoveVector.x > 0.01f)
		{
			//�E�ɍs���Ă����ꍇ�A���C���|����
			m_MoveVector.x *= m_Friction;
		}
		else
		{
			m_MoveVector.x = m_DashSpeed;
		}

		NoButton = false;
	}

	//�{�^��������������Ă��Ȃ����
	if (NoButton)
	{
		//�~�܂�
		m_MoveVector.x *= m_Friction;

		//������x�x���Ȃ�����
		if (m_MoveVector.x < 0.01f || m_MoveVector.x > -0.01f)
		{
			m_MoveVector.x = 0.0f;
			m_State = Character::STATE::IDLE;
		}
	}

	//�W�����v
	if (IsKeyPress(VK_UP))
	{
		m_Velocity.x = m_MoveVector.x;
		m_Velocity.y = m_JumpPower;
		m_State = Character::STATE::JUMP;
	}

	m_Velocity.y += m_Gravity;

	//�ꉞ�d�͐���������Ă���
	if (m_Velocity.y < m_MaxFallSpeed)
	{
		m_Velocity.y = m_MaxFallSpeed;
	}

	m_pos += m_MoveVector;
	m_pos += m_Velocity;
}