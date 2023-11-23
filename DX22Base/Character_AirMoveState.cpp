#include "Character_Base.h"
#include "Input.h"
#include "Attack_Base.h"
#include "XboxKeyboard.h"

void Character::AirMoveInit()
{

}

void Character::AirMoveUninit()
{

}

void Character::AirMoveUpdate()
{
	bool OnButton = false;

	m_MoveVector = CVector3::GetZero();

	if (IsKeyPress(VK_RIGHT))
	{
		m_Velocity.x = m_FallSideMoveSpeed;
		OnButton = true;
	}

	if (IsKeyPress(VK_LEFT))
	{
		m_Velocity.x = -m_FallSideMoveSpeed;
		OnButton = true;
	}

	//������x�W�����v���ł���
	if (m_JumpCount < m_MaxJumpCount)
	{
		if (IsKeyTrigger(VK_UP))
		{
			m_JumpCount++;
			m_Velocity.y = m_JumpPower;
			m_State = Character::STATE::JUMP;
		}
	}

	if (!OnButton)
	{
		m_Velocity.x *= m_AirResistance;	//��C��R���|����
	}

	m_Velocity.y += m_Gravity;			//�d�͂��|����

	//�d�͐���(�ő�̗������x�ɂȂ�����)
	if (m_Velocity.y < m_MaxFallSpeed)
	{
		m_Velocity.y = m_MaxFallSpeed;
	}

	m_pos += m_MoveVector;
	m_pos += m_Velocity;
}