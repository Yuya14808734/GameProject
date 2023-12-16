#include "Character_Base.h"
#include "Input.h"
#include "Attack_Base.h"
#include "XboxKeyboard.h"
#include "Input.h"

//===========================================================
//キャラクターが止まっているときの処理
//---行ける状態---
//ジャンプ
//攻撃(一フレームのみ,横強などはWalkに任せる)
//歩く
//走る
//===========================================================

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

	//デットゾーンの設定
	if (LeftStick.x * LeftStick.x + LeftStick.y * LeftStick.y < 0.15f * 0.15f)
	{
		LeftStick.x = LeftStick.y = 0.0f;
	}


	//移動開始
	if (LeftStick.x != 0.0f || IsKeyPress(VK_RIGHT) || IsKeyPress(VK_LEFT))
	{
		if (GetLeftSmash(0.35f) || IsKeyPress('L'))
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
		ChangeState(Character::STATE::JUMPIN);
	}

	//攻撃
	if (IsKeyPress('K') || InputPressKey(PadButton::A_BUTTON))
	{
		ChangeAttack(Character::ATTACK::ATTACK_11);	//弱の設定
	}

	m_Velocity.y += m_JumpParameter.m_FallDownGravity;
	m_Velocity.x *= m_MoveParameter.m_Friction;

	//一応重力制御も書いておく
	if (m_Velocity.y < m_JumpParameter.m_DefaultFallSpeed)
	{
		m_Velocity.y = m_JumpParameter.m_DefaultFallSpeed;
	}

	m_pos += m_MoveVector;
	m_pos += m_Velocity;
}
