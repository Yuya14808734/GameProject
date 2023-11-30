#include "Character_Base.h"
#include "Input.h"
#include "Attack_Base.h"
#include "XboxKeyboard.h"

void Character::DashInit()
{

}

void Character::DashUninit()
{

}

void Character::DashUpdate()
{
	//地面に当たっていなければ
	if (!m_HitGround)
	{
		ChangeState(Character::STATE::AIRMOVE);
	}

	bool NoButton = true;
	float NowX = GetPressLeftStick().x * m_WalkSpeed;

	if(NowX > 0.0f || IsKeyPress(VK_RIGHT))
	{
		if (m_MoveVector.x < -0.01f)
		{
			//左に行っていた場合、摩擦を掛ける
			m_MoveVector.x *= m_Friction;
		}
		else
		{
			m_MoveVector.x = m_DashSpeed;
		}

		NoButton = false;
	}

	if(NowX < 0.0f || IsKeyPress(VK_LEFT))
	{
		if (m_MoveVector.x > 0.01f)
		{
			//右に行っていた場合、摩擦を掛ける
			m_MoveVector.x *= m_Friction;
		}
		else
		{
			m_MoveVector.x = -m_DashSpeed;
		}

		NoButton = false;
	}

	//ボタンが何も押されていなければ
	if (NoButton)
	{
		//止まる
		m_MoveVector.x *= m_Friction;

		//ある程度遅くなったら
		if (m_MoveVector.x < 0.01f || m_MoveVector.x > -0.01f)
		{
			m_MoveVector.x = 0.0f;
			ChangeState(Character::STATE::IDLE);
		}
	}

	//ジャンプ
	if (IsKeyPress(VK_UP))
	{
		m_Velocity.x = m_MoveVector.x;
		m_Velocity.y = m_JumpPower;
		ChangeState(Character::STATE::JUMP);
	}

	m_Velocity.y += m_Gravity;

	//一応重力制御も書いておく
	if (m_Velocity.y < m_DefaultMaxFallSpeed)
	{
		m_Velocity.y = m_DefaultMaxFallSpeed;
	}

	m_pos += m_MoveVector;
	m_pos += m_Velocity;
}