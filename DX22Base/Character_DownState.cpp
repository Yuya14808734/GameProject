#include "Character_Base.h"
#include "Input.h"
#include "XboxKeyboard.h"


void Character::DownInit()
{
	m_Velocity = CVector3::GetZero();
}

void Character::DownUninit()
{

}

void Character::DownUpdate()
{
	//�n�ʂɓ������Ă��Ȃ����
	if (!m_HitGround)
	{
		ChangeState(Character::STATE::AIRMOVE);
	}

	m_Velocity.y += m_JumpParameter.m_FallDownGravity;
	m_Velocity.x *= m_MoveParameter.m_Friction;

	//�ꉞ�d�͐���������Ă���
	if (m_Velocity.y < m_JumpParameter.m_DefaultFallSpeed)
	{
		m_Velocity.y = m_JumpParameter.m_DefaultFallSpeed;
	}

	//m_pos += m_MoveVector;
	m_pos += m_Velocity;

	//�A�j���[�V�������I��������N���オ���悤�ɂ������̂�
	//�p����Ŏ������Ă�������
}