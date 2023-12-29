#include "Character_Base.h"

void Character::DashInit()
{

}

void Character::DashUninit()
{

}

void Character::DashUpdate()
{
	//�n�ʂɓ������Ă��Ȃ����
	if (!m_HitGround)
	{
		ChangeState(Character::STATE::AIRMOVE);
	}

	bool NoButton = true;
	float NowX = m_Controller.GetMoveInput().x * m_MoveParameter.m_WalkSpeed;

	if(NowX > 0.0f)
	{
		if (m_MoveVector.x < -0.01f)
		{
			//���ɍs���Ă����ꍇ�A���C���|����
			m_MoveVector.x *= m_MoveParameter.m_Friction;
		}
		else
		{
			m_MoveVector.x = m_MoveParameter.m_DashSpeed;
		}

		//�E�ɍs���Ă���
		SetLookRight();

		NoButton = false;
	}

	if(NowX < 0.0f)
	{
		if (m_MoveVector.x > 0.01f)
		{
			//�E�ɍs���Ă����ꍇ�A���C���|����
			m_MoveVector.x *= m_MoveParameter.m_Friction;
		}
		else
		{
			m_MoveVector.x = -m_MoveParameter.m_DashSpeed;
		}

		//���ɍs���Ă���
		SetLookLeft();

		NoButton = false;
	}

	//�{�^��������������Ă��Ȃ����
	if (NoButton)
	{
		//�~�܂�
		m_MoveVector.x *= m_MoveParameter.m_Friction;

		//������x�x���Ȃ�����
		if (m_MoveVector.x < 0.01f || m_MoveVector.x > -0.01f)
		{
			m_MoveVector.x = 0.0f;
			ChangeState(Character::STATE::IDLE);
		}
	}

	//�W�����v
	if (m_Controller.GetJumpTrigger())
	{
		m_Velocity.x = m_MoveVector.x;
		ChangeState(Character::STATE::JUMPIN);
	}

	m_Velocity.y += m_JumpParameter.m_FallDownGravity;

	//�ꉞ�d�͐���������Ă���
	if (m_Velocity.y < m_JumpParameter.m_DefaultFallSpeed)
	{
		m_Velocity.y = m_JumpParameter.m_DefaultFallSpeed;
	}

	m_pos += m_MoveVector;
	m_pos += m_Velocity;
}