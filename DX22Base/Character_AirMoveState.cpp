#include "Character_Base.h"
#include "Input.h"
#include "Attack_Base.h"
#include "XboxKeyboard.h"

void Character::AirMoveInit()
{
	m_MoveVector = CVector3::GetZero();
}

void Character::AirMoveUninit()
{

}

void Character::AirMoveUpdate()
{
	if (m_HitGround)
	{
		ChangeState(Character::STATE::IDLE);
	}

	bool OnButton = false;

	float LeftStickX = m_Controller.GetMoveInput().x * m_MoveParameter.m_AirSideMoveSpeed;
	m_Velocity.x = fabsf(LeftStickX) > fabsf(m_Velocity.x) ? LeftStickX : m_Velocity.x;

	//������x�W�����v���ł���
	if (m_JumpCount < m_JumpParameter.m_MaxJumpCount)
	{
		if (m_Controller.GetJumpTrigger())
		{
			m_JumpCount++;
			m_Velocity.y = m_JumpParameter.m_FirstJumpPower;
			ChangeState(Character::STATE::JUMP);
		}
	}

	//�U��
	if (m_Controller.GetAttack())
	{
		ChangeAttack(Character::ATTACK::ATTACK_AIRN);	//��̐ݒ�
	}

	if (!OnButton)
	{
		m_Velocity.x *= m_MoveParameter.m_AirDrag;	//��C��R���|����
	}

	m_Velocity.y += m_JumpParameter.m_FallDownGravity;			//�d�͂��|����

	//�d�͐���(�ő�̗������x�ɂȂ�����)
	if (m_Velocity.y < m_JumpParameter.m_DefaultFallSpeed)
	{
		m_Velocity.y = m_JumpParameter.m_DefaultFallSpeed;
	}

	m_pos += m_MoveVector;
	m_pos += m_Velocity;
}