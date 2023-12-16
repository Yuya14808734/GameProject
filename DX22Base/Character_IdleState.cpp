#include "Character_Base.h"
#include "Input.h"
#include "Attack_Base.h"
#include "XboxKeyboard.h"
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

	CVector2 LeftStick = GetPressLeftStick();

	//�f�b�g�]�[���̐ݒ�
	if (LeftStick.x * LeftStick.x + LeftStick.y * LeftStick.y < 0.15f * 0.15f)
	{
		LeftStick.x = LeftStick.y = 0.0f;
	}


	//�ړ��J�n
	if (LeftStick.x != 0.0f || IsKeyPress(VK_RIGHT) || IsKeyPress(VK_LEFT))
	{
		if (GetLeftSmash(0.35f) || IsKeyPress('L'))
		{
			ChangeState(Character::STATE::DASH);
		}
		else
		{
			ChangeState(Character::STATE::WALK);
		}
	}

	//�W�����v
	if (InputTriggerKey(PadButton::RIGHT_SHOULDER) || IsKeyTrigger(VK_UP))
	{
		ChangeState(Character::STATE::JUMPIN);
	}

	//�U��
	if (IsKeyPress('K') || InputPressKey(PadButton::A_BUTTON))
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
