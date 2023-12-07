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

	float LeftStickX = GetPressLeftStick().x * m_WalkSpeed;
	m_Velocity.x = fabsf(LeftStickX) > fabsf(m_Velocity.x) ? LeftStickX : m_Velocity.x;

	if (IsKeyPress(VK_RIGHT))
	{
		m_Velocity.x = m_AirSideMoveSpeed;
	}

	if (IsKeyPress(VK_LEFT))
	{
		m_Velocity.x = -m_AirSideMoveSpeed;
	}

	//������x�W�����v���ł���
	if (m_JumpCount < m_MaxJumpCount)
	{
		if (InputTriggerKey(PadButton::RIGHT_SHOULDER) || IsKeyTrigger(VK_UP))
		{
			m_JumpCount++;
			m_Velocity.y = m_FirstJumpPower;
			ChangeState(Character::STATE::JUMP);
		}
	}

	if (!OnButton)
	{
		m_Velocity.x *= m_AirDrag;	//��C��R���|����
	}

	m_Velocity.y += m_Gravity;			//�d�͂��|����

	//�d�͐���(�ő�̗������x�ɂȂ�����)
	if (m_Velocity.y < m_DefaultFallSpeed)
	{
		m_Velocity.y = m_DefaultFallSpeed;
	}

	m_pos += m_MoveVector;
	m_pos += m_Velocity;
}