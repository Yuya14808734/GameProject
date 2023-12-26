#include "Character_Base.h"

void Character::FallDownInit()
{

}

void Character::FallDownUninit()
{

}

void Character::FallDownUpdate()
{
	if (m_HitGround)
	{
		ChangeState(Character::STATE::DOWN);
		return;
	}

	bool OnButton = false;

	float LeftStickX = m_Controller.GetMoveInput().x * m_MoveParameter.m_AirSideMoveSpeed;
	m_Velocity.x = fabsf(LeftStickX) > fabsf(m_Velocity.x) ? LeftStickX : m_Velocity.x;

	//もう一度ジャンプができる
	if (m_JumpCount < m_JumpParameter.m_MaxJumpCount)
	{
		if (m_Controller.GetJumpTrigger())
		{
			m_JumpCount++;
			m_Velocity.y = m_JumpParameter.m_FirstJumpPower;
			ChangeState(Character::STATE::JUMP);
		}
	}

	//攻撃
	if (m_Controller.GetAttack())
	{
		ChangeAttack(Character::ATTACK::ATTACK_AIRN);	//空中N
	}

	if (!OnButton)
	{
		m_Velocity.x *= m_MoveParameter.m_AirDrag;	//空気抵抗を掛ける
	}

	m_Velocity.y += m_JumpParameter.m_FallDownGravity;			//重力を掛ける

	//重力制御(最大の落下速度になったら)
	if (m_Velocity.y < m_JumpParameter.m_DefaultFallSpeed)
	{
		m_Velocity.y = m_JumpParameter.m_DefaultFallSpeed;
	}

	m_pos += m_MoveVector;
	m_pos += m_Velocity;
}