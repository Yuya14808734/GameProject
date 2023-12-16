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
	//�n�ʂɓ������Ă��Ȃ����
	if (!m_HitGround)
	{
		ChangeState(Character::STATE::AIRMOVE);
	}

	bool NoButton = true;
	float NowX = GetPressLeftStick().x * m_MoveParameter.m_WalkSpeed;

	if(NowX > 0.0f || IsKeyPress(VK_RIGHT))
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
		m_rotate = CQuaternion::AngleAxis(CVector3::GetUp(), 90.0f);
		m_NowLookDir = Character::LOOKDIR::RIGHT;

		NoButton = false;
	}

	if(NowX < 0.0f || IsKeyPress(VK_LEFT))
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
		m_rotate = CQuaternion::AngleAxis(CVector3::GetUp(), -90.0f);
		m_NowLookDir = Character::LOOKDIR::LEFT;

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
	if (InputTriggerKey(PadButton::RIGHT_SHOULDER) || IsKeyPress(VK_UP))
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