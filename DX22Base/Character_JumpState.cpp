#include "Character_Base.h"
#include "Input.h"
#include "Attack_Base.h"
#include "XboxKeyboard.h"

void Character::JumpInit()
{
	m_Velocity.y = m_JumpPower;
	m_JumpCount++;
}

void Character::JumpUninit()
{

}

void Character::JumpUpdate()
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

	//もう一度ジャンプができる
	if (m_JumpCount < m_MaxJumpCount)
	{
		if (IsKeyTrigger(VK_UP))
		{
			m_State = Character::STATE::JUMP;
		}
	}

	if (!OnButton)
	{
		m_Velocity.x *= m_AirResistance;	//空気抵抗を掛ける
	}

	m_Velocity.y += m_Gravity;			//重力を掛ける

	//重力制御(最大の落下速度になったら)
	if (m_Velocity.y < m_MaxFallSpeed)
	{
		m_Velocity.y = m_MaxFallSpeed;
	}

	//落下し始めたら
	if (m_Velocity.y < 0.1f)
	{
		m_State = Character::STATE::AIRMOVE;
	}

	m_pos += m_MoveVector;
	m_pos += m_Velocity;
}