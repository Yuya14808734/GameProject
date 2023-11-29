#include "Character_Base.h"
#include "Input.h"
#include "Attack_Base.h"
#include "XboxKeyboard.h"
#include "Input.h"

//---行ける状態---
//ジャンプ
//攻撃(一フレームのみ,横強などはWalkに任せる)
//歩く
//走る

void Character::IdleInit()
{

}

void Character::IdleUninit()
{

}

void Character::IdleUpdate()
{
	//地面に当たっていなければ
	if (!m_HitGround)
	{
		ChangeState(Character::STATE::AIRMOVE);
	}

	CVector2 LeftStick = GetPressLeftStick();

	//移動開始
	if (LeftStick.x != 0.0f || IsKeyPress(VK_RIGHT) || IsKeyPress(VK_LEFT))
	{
		if (GetLeftSmash(0.4f))
		{
			ChangeState(Character::STATE::DASH);
		}
		else
		{
			ChangeState(Character::STATE::WALK);
		}
	}

	//ジャンプ
	if (InputTriggerKey(PadButton::RIGHT_SHOULDER) || IsKeyTrigger(VK_UP))
	{
		ChangeState(Character::STATE::JUMP);
		m_Velocity.y = m_JumpPower;
	}

	//攻撃
	if (false)
	{
		ChangeState(Character::STATE::ATTACK);
	}

	m_Velocity.y += m_Gravity;
	m_Velocity.x *= m_Friction;

	//一応重力制御も書いておく
	if (m_Velocity.y < m_DefaultMaxFallSpeed)
	{
		m_Velocity.y = m_DefaultMaxFallSpeed;
	}

	m_pos += m_MoveVector;
	m_pos += m_Velocity;
}
