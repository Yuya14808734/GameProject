#include "Character_Base.h"

void Character::WalkInit()
{
	m_MoveVector.x = 0.0f;
	m_Velocity.x = 0.0f;
}

void Character::WalkUninit()
{

}

void Character::WalkUpdate()
{
	//�n�ʂɓ������Ă��Ȃ����
	if (!m_HitGround)
	{
		ChangeState(Character::STATE::AIRMOVE);
	}

	bool NoButton = true;

	m_MoveVector.x = m_Controller->GetMoveInput().x * m_MoveParameter.m_WalkSpeed;

	if (m_MoveVector.x != 0.0f)
	{
		NoButton = false;

		if (m_MoveVector.x > 0.0f)
		{
			//�E�ɍs���Ă���
			SetLookRight();
		}
		else
		{
			//���ɍs���Ă���
			SetLookLeft();
		}

	}

	//�{�^��������������Ă��Ȃ����
	if (NoButton)
	{
		ChangeState(Character::STATE::IDLE);
	}

	//�U��
	if (m_Controller->GetAttack())
	{
		ChangeAttack(Character::ATTACK::ATTACK_S2);	//�����̐ݒ�
	}

	//�W�����v
	if (m_Controller->GetJumpTrigger())
	{
		ChangeState(Character::STATE::JUMPIN);
	}

	//���Ⴊ�݂������
	/*if (IsKeyPress(VK_DOWN))
	{

	}*/

	m_Velocity.y += m_JumpParameter.m_FallDownGravity;

	//�ꉞ�d�͐���������Ă���
	if (m_Velocity.y < m_JumpParameter.m_DefaultFallSpeed)
	{
		m_Velocity.y = m_JumpParameter.m_DefaultFallSpeed;
	}

	m_pos += m_MoveVector;
	m_pos += m_Velocity;
}