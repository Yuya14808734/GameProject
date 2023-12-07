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

	//もう一度ジャンプができる
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
		m_Velocity.x *= m_AirDrag;	//空気抵抗を掛ける
	}

	m_Velocity.y += m_Gravity;			//重力を掛ける

	//重力制御(最大の落下速度になったら)
	if (m_Velocity.y < m_DefaultFallSpeed)
	{
		m_Velocity.y = m_DefaultFallSpeed;
	}

	m_pos += m_MoveVector;
	m_pos += m_Velocity;
}