#include "Character_Base.h"
#include "Input.h"
#include "Attack_Base.h"
#include "XboxKeyboard.h"

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

	m_MoveVector.x = GetPressLeftStick().x * m_WalkSpeed;

	if(IsKeyPress(VK_RIGHT))
	{
		m_MoveVector.x = m_WalkSpeed;
	}

	if(IsKeyPress(VK_LEFT))
	{
		m_MoveVector.x = -m_WalkSpeed;
	}

	if (m_MoveVector.x != 0.0f)
	{
		NoButton = false;

		if (m_MoveVector.x > 0.0f)
		{
			//右に行っている
			m_rotate = CQuaternion::AngleAxis(CVector3::GetUp(), 90.0f);
			m_NowLookDir = Character::LOOKDIR::RIGHT;
		}
		else
		{
			//左に行っている
			m_rotate = CQuaternion::AngleAxis(CVector3::GetUp(), -90.0f);
			m_NowLookDir = Character::LOOKDIR::LEFT;
		}

	}

	//ボタンが何も押されていなければ
	if (NoButton)
	{
		ChangeState(Character::STATE::IDLE);
	}

	//攻撃
	if (IsKeyTrigger('K') || InputTriggerKey(PadButton::A_BUTTON))
	{
		ChangeAttack(Character::ATTACK::ATTACK_S2);	//横強の設定
	}

	//ジャンプ
	if (InputTriggerKey(PadButton::RIGHT_SHOULDER) || IsKeyTrigger(VK_UP))
	{
		ChangeState(Character::STATE::JUMPIN);
	}

	//しゃがみがあれば
	if (IsKeyPress(VK_DOWN))
	{

	}

	m_Velocity.y += m_Gravity;

	//一応重力制御も書いておく
	if (m_Velocity.y < m_DefaultFallSpeed)
	{
		m_Velocity.y = m_DefaultFallSpeed;
	}

	m_pos += m_MoveVector;
	m_pos += m_Velocity;
}