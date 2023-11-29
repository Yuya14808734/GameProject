#include "Character_Base.h"
#include "Input.h"
#include "Attack_Base.h"
#include "XboxKeyboard.h"

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

	m_MoveVector.x = GetPressLeftStick().x * m_WalkSpeed;

	if (IsKeyPress(VK_RIGHT))
	{
		m_MoveVector.x = m_WalkSpeed;
	}

	if (IsKeyPress(VK_LEFT))
	{
		m_MoveVector.x = -m_WalkSpeed;
	}

	if (m_MoveVector.x != 0.0f)
	{
		NoButton = false;
	}

	//�{�^��������������Ă��Ȃ����
	if (NoButton)
	{
		ChangeState(Character::STATE::IDLE);
	}

	//�W�����v
	if (InputTriggerKey(PadButton::RIGHT_SHOULDER) || IsKeyTrigger(VK_UP))
	{
		ChangeState(Character::STATE::JUMP);
		m_Velocity.y = m_JumpPower;
	}

	//���Ⴊ�݂������
	if (IsKeyPress(VK_DOWN))
	{

	}

	m_Velocity.y += m_Gravity;

	//�ꉞ�d�͐���������Ă���
	if (m_Velocity.y < m_DefaultMaxFallSpeed)
	{
		m_Velocity.y = m_DefaultMaxFallSpeed;
	}

	m_pos += m_MoveVector;
	m_pos += m_Velocity;
}