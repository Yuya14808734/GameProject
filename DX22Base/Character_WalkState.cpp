#include "Character_Base.h"

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
	//地面に当たっていなければ
	if (!m_HitGround)
	{
		ChangeState(Character::STATE::AIRMOVE);
	}

	bool NoButton = true;

	m_MoveVector.x = m_Controller->GetMoveInput().x * m_MoveParameter.m_WalkSpeed;

	if (m_MoveVector.x != 0.0f)
	{
		NoButton = false;

		if (m_MoveVector.x > 0.0f)
		{
			//右に行っている
			SetLookRight();
		}
		else
		{
			//左に行っている
			SetLookLeft();
		}

	}

	//ボタンが何も押されていなければ
	if (NoButton)
	{
		ChangeState(Character::STATE::IDLE);
	}

	//攻撃
	if (m_Controller->GetAttack())
	{
		ChangeAttack(Character::ATTACK::ATTACK_S2);	//横強の設定
	}

	//ジャンプ
	if (m_Controller->GetJumpTrigger())
	{
		ChangeState(Character::STATE::JUMPIN);
	}

	//しゃがみがあれば
	/*if (IsKeyPress(VK_DOWN))
	{

	}*/

	m_Velocity.y += m_JumpParameter.m_FallDownGravity;

	//一応重力制御も書いておく
	if (m_Velocity.y < m_JumpParameter.m_DefaultFallSpeed)
	{
		m_Velocity.y = m_JumpParameter.m_DefaultFallSpeed;
	}

	m_pos += m_MoveVector;
	m_pos += m_Velocity;
}