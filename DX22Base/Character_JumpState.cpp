#include "Character_Base.h"
#include "Input.h"
#include "Attack_Base.h"
#include "XboxKeyboard.h"

void Character::JumpInit()
{
	if (m_JumpCount == 0)
	{
		//最初のジャンプだった場合
		m_Velocity.y = m_FirstJumpPower;
	}
	else
	{
		//二回目のジャンプだった場合
		m_Velocity.y = m_SecondJumpPower;
	}

	m_MoveVector = CVector3::GetZero();
	m_JumpCount++;
}

void Character::JumpUninit()
{

}

void Character::JumpUpdate()
{
	if (m_HitGround)
	{
		ChangeState(Character::STATE::IDLE);
	}


	bool OnButton = false;

	m_MoveVector.x =  GetPressLeftStick().x * m_AirSideMoveSpeed;

	if (IsKeyPress(VK_RIGHT))
	{
		m_MoveVector.x = m_AirSideMoveSpeed;
	}

	if (IsKeyPress(VK_LEFT))
	{
		m_MoveVector.x = -m_AirSideMoveSpeed;
	}

	m_Velocity.x *= m_AirDrag;	//空気抵抗を掛ける

	//もう一度ジャンプができる
	if (m_JumpCount < m_MaxJumpCount)
	{
		if (InputTriggerKey(PadButton::RIGHT_SHOULDER) || IsKeyTrigger(VK_UP))
		{
			ChangeState(Character::STATE::JUMP);
		}
	}

	m_Velocity.y += m_JumpUpGravity;		//重力を掛ける

	//重力制御(最大の落下速度になったら)
	if (m_Velocity.y < m_DefaultFallSpeed)
	{
		m_Velocity.y = m_DefaultFallSpeed;
	}

	//落下し始めたら
	if (m_Velocity.y < 0.1f)
	{
		ChangeState(Character::STATE::AIRMOVE);
	}

	m_pos += m_MoveVector;
	m_pos += m_Velocity;
}