#include "Character_Base.h"
#include "Input.h"

//===========================================================
//�L�����N�^�[���~�܂��Ă���Ƃ��̏���
//---�s������---
//�W�����v
//�U��(��t���[���̂�,�����Ȃǂ�Walk�ɔC����)
//����
//����
//===========================================================

void Character::IdleInit()
{

}

void Character::IdleUninit()
{

}

void Character::IdleUpdate()
{
	//�n�ʂɓ������Ă��Ȃ����
	if (!m_HitGround)
	{
		ChangeState(Character::STATE::AIRMOVE);
	}

	CVector2 LeftStick = m_Controller.GetMoveInput();

	//�ړ��J�n
	if (LeftStick.x != 0.0f)
	{
		if (m_Controller.GetLeftSmash())
		{
			ChangeState(Character::STATE::DASH);
		}
		else
		{
			ChangeState(Character::STATE::WALK);
		}
	}

	//�W�����v
	if (m_Controller.GetJumpTrigger())
	{
		ChangeState(Character::STATE::JUMPIN);
	}

	//�U��
	if (m_Controller.GetAttack())
	{
		ChangeAttack(Character::ATTACK::ATTACK_11);	//��̐ݒ�
	}

	m_Velocity.y += m_JumpParameter.m_FallDownGravity;
	m_Velocity.x *= m_MoveParameter.m_Friction;

	//�ꉞ�d�͐���������Ă���
	if (m_Velocity.y < m_JumpParameter.m_DefaultFallSpeed)
	{
		m_Velocity.y = m_JumpParameter.m_DefaultFallSpeed;
	}

	m_pos += m_MoveVector;
	m_pos += m_Velocity;
}
