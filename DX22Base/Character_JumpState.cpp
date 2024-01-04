#include "Character_Base.h"

void Character::JumpInit()
{
	if (m_JumpCount == 0)
	{
		//�ŏ��̃W�����v�������ꍇ
		m_Velocity.y = m_JumpParameter.m_FirstJumpPower;
	}
	else
	{
		//���ڂ̃W�����v�������ꍇ
		m_Velocity.y = m_JumpParameter.m_SecondJumpPower;
	}

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

	m_MoveVector.x =  m_Controller->GetMoveInput().x * m_MoveParameter.m_AirSideMoveSpeed;

	m_Velocity.x *= m_MoveParameter.m_AirDrag;	//��C��R���|����

	//������x�W�����v���ł���
	if (m_JumpCount < m_JumpParameter.m_MaxJumpCount)
	{
		if (m_Controller->GetJumpTrigger())
		{
			ChangeState(Character::STATE::JUMP);
		}
	}

	//�U��
	if (m_Controller->GetAttack())
	{
		ChangeAttack(Character::ATTACK::ATTACK_AIRN);	//��̐ݒ�
	}

	m_Velocity.y *= m_JumpParameter.m_JumpUpReduction;		//�d�͂��|����

	//�d�͐���(�ő�̗������x�ɂȂ�����)
	if (m_Velocity.y < m_JumpParameter.m_DefaultFallSpeed)
	{
		m_Velocity.y = m_JumpParameter.m_DefaultFallSpeed;
	}

	//�������n�߂���
	if (m_Velocity.y < m_JumpParameter.m_ChangeFallSpeed)
	{
		ChangeState(Character::STATE::AIRMOVE);
	}

	m_pos += m_MoveVector;
	m_pos += m_Velocity;
}