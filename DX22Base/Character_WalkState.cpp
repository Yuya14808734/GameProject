#include "Character_Base.h"
#include "Input.h"
#include "Attack_Base.h"
#include "XboxKeyboard.h"

void Character::WalkInit()
{

}

void Character::WalkUninit()
{

}

void Character::WalkUpdate()
{
	//---�s������---
	//�W�����v
	//�U��
	//����
	//����

	bool NoButton = true;

	m_MoveVector.x = GetPressLeftStick().x * m_FallSideMoveSpeed;

	if (m_MoveVector.x != 0.0f)
	{
		NoButton = false;
	}

	if (IsKeyPress(VK_RIGHT))
	{
		m_MoveVector.x = m_WalkSpeed;

		NoButton = false;
	}

	if (IsKeyPress(VK_LEFT))
	{
		m_MoveVector.x = -m_WalkSpeed;

		NoButton = false;
	}

	//�{�^��������������Ă��Ȃ����
	if (NoButton)
	{
		m_State = Character::STATE::IDLE;
	}

	//�W�����v
	if (IsKeyPress(VK_UP))
	{
		m_Velocity.y = m_JumpPower;
		m_State = Character::STATE::JUMP;
	}

	//���Ⴊ�݂������
	if (IsKeyPress(VK_DOWN))
	{

	}

	m_Velocity.y += m_Gravity;
	m_Velocity.x *= m_Friction;


	//�ꉞ�d�͐���������Ă���
	if (m_Velocity.y < m_MaxFallSpeed)
	{
		m_Velocity.y = m_MaxFallSpeed;
	}

	m_pos += m_MoveVector;
	m_pos += m_Velocity;
}