#include "Character_Base.h"
#include "Input.h"
#include "Attack_Base.h"
#include "XboxKeyboard.h"

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

	m_MoveVector.x =  GetPressLeftStick().x * m_MoveParameter.m_AirSideMoveSpeed;

	if (IsKeyPress(VK_RIGHT))
	{
		m_MoveVector.x = m_MoveParameter.m_AirSideMoveSpeed;
	}

	if (IsKeyPress(VK_LEFT))
	{
		m_MoveVector.x = -m_MoveParameter.m_AirSideMoveSpeed;
	}

	m_Velocity.x *= m_MoveParameter.m_AirDrag;	//��C��R���|����

	//������x�W�����v���ł���
	if (m_JumpCount < m_JumpParameter.m_MaxJumpCount)
	{
		if (InputTriggerKey(PadButton::RIGHT_SHOULDER) || IsKeyTrigger(VK_UP))
		{
			ChangeState(Character::STATE::JUMP);
		}
	}

	//�U��
	if (IsKeyPress('K') || InputPressKey(PadButton::A_BUTTON))
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