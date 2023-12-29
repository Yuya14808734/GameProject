#include "Character_Base.h"

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
	float NowX = m_Controller.GetMoveInput().x * m_MoveParameter.m_WalkSpeed;

	if(NowX > 0.0f)
	{
		if (m_MoveVector.x < -0.01f)
		{
			//左に行っていた場合、摩擦を掛ける
			m_MoveVector.x *= m_MoveParameter.m_Friction;
		}
		else
		{
			m_MoveVector.x = m_MoveParameter.m_DashSpeed;
		}

		//右に行っている
		SetLookRight();

		NoButton = false;
	}

	if(NowX < 0.0f)
	{
		if (m_MoveVector.x > 0.01f)
		{
			//右に行っていた場合、摩擦を掛ける
			m_MoveVector.x *= m_MoveParameter.m_Friction;
		}
		else
		{
			m_MoveVector.x = -m_MoveParameter.m_DashSpeed;
		}

		//左に行っている
		SetLookLeft();

		NoButton = false;
	}

	//ボタンが何も押されていなければ
	if (NoButton)
	{
		//止まる
		m_MoveVector.x *= m_MoveParameter.m_Friction;

		//ある程度遅くなったら
		if (m_MoveVector.x < 0.01f || m_MoveVector.x > -0.01f)
		{
			m_MoveVector.x = 0.0f;
			ChangeState(Character::STATE::IDLE);
		}
	}

	//ジャンプ
	if (m_Controller.GetJumpTrigger())
	{
		m_Velocity.x = m_MoveVector.x;
		ChangeState(Character::STATE::JUMPIN);
	}

	m_Velocity.y += m_JumpParameter.m_FallDownGravity;

	//一応重力制御も書いておく
	if (m_Velocity.y < m_JumpParameter.m_DefaultFallSpeed)
	{
		m_Velocity.y = m_JumpParameter.m_DefaultFallSpeed;
	}

	m_pos += m_MoveVector;
	m_pos += m_Velocity;
}