#include "Character_Base.h"
#include "Input.h"
#include "XboxKeyboard.h"


void Character::DownInit()
{
	m_Velocity = CVector3::GetZero();
}

void Character::DownUninit()
{

}

void Character::DownUpdate()
{
	//地面に当たっていなければ
	if (!m_HitGround)
	{
		ChangeState(Character::STATE::AIRMOVE);
	}

	m_Velocity.y += m_JumpParameter.m_FallDownGravity;
	m_Velocity.x *= m_MoveParameter.m_Friction;

	//一応重力制御も書いておく
	if (m_Velocity.y < m_JumpParameter.m_DefaultFallSpeed)
	{
		m_Velocity.y = m_JumpParameter.m_DefaultFallSpeed;
	}

	//m_pos += m_MoveVector;
	m_pos += m_Velocity;

	//アニメーションが終了したら起き上がれるようにしたいので
	//継承先で実装してください
}