#include "Character_Base.h"
#include "Input.h"
#include "Attack_Base.h"
#include "XboxKeyboard.h"

void Character::WalkInit()
{

}

void Character::WalkUninit()
{

}

void Character::WalkUpdate()
{
	//---行ける状態---
	//ジャンプ
	//攻撃
	//歩く
	//走る

	bool NoButton = true;

	m_MoveVector.x = GetPressLeftStick().x * m_FallSideMoveSpeed;

	if (m_MoveVector.x != 0.0f)
	{
		NoButton = false;
	}

	if (IsKeyPress(VK_RIGHT))
	{
		m_MoveVector.x = m_WalkSpeed;

		NoButton = false;
	}

	if (IsKeyPress(VK_LEFT))
	{
		m_MoveVector.x = -m_WalkSpeed;

		NoButton = false;
	}

	//ボタンが何も押されていなければ
	if (NoButton)
	{
		m_State = Character::STATE::IDLE;
	}

	//ジャンプ
	if (IsKeyPress(VK_UP))
	{
		m_Velocity.y = m_JumpPower;
		m_State = Character::STATE::JUMP;
	}

	//しゃがみがあれば
	if (IsKeyPress(VK_DOWN))
	{

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