#include "Character_Base.h"
#include "Input.h"
#include "Attack_Base.h"
#include "XboxKeyboard.h"

//---行ける状態---
//ジャンプ
//攻撃(一フレームのみ,横強などはWalkに任せる)
//歩く
//走る

void Character::IdleInit()
{

}


void Character::IdleUpdate()
{
	


	if (GetPressLeftStick().x != 0.0f)
	{
		m_State = Character::STATE::WALK;
	}

	if (IsKeyPress(VK_UP))
	{
		m_State = Character::STATE::JUMP;
		m_Velocity.y = m_JumpPower;
	}

	//攻撃
	if (false)
	{
		m_State = Character::STATE::ATTACK;
	}

	m_Velocity.y += m_Gravity;
	m_Velocity.x *= m_Friction;

	//一応重力制御も書いておく
	if (m_Velocity.y < m_MaxFallSpeed)
	{
		m_Velocity.y = m_MaxFallSpeed;
	}

	m_pos += m_MoveVector;
	m_pos += m_Velocity;
}

void Character::IdleUninit()
{

}

