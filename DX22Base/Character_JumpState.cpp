#include "Character_Base.h"

void Character::JumpInit()
{
	if (m_JumpCount == 0)
	{
		//最初のジャンプだった場合
		m_Velocity.y = m_JumpParameter.m_FirstJumpPower;
	}
	else
	{
		//二回目のジャンプだった場合
		m_Velocity.y = m_JumpParameter.m_SecondJumpPower;
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

	m_MoveVector.x =  m_Controller.GetMoveInput().x * m_MoveParameter.m_AirSideMoveSpeed;

	m_Velocity.x *= m_MoveParameter.m_AirDrag;	//空気抵抗を掛ける

	//もう一度ジャンプができる
	if (m_JumpCount < m_JumpParameter.m_MaxJumpCount)
	{
		if (m_Controller.GetJumpTrigger())
		{
			ChangeState(Character::STATE::JUMP);
		}
	}

	//攻撃
	if (m_Controller.GetAttack())
	{
		ChangeAttack(Character::ATTACK::ATTACK_AIRN);	//弱の設定
	}

	m_Velocity.y *= m_JumpParameter.m_JumpUpReduction;		//重力を掛ける

	//重力制御(最大の落下速度になったら)
	if (m_Velocity.y < m_JumpParameter.m_DefaultFallSpeed)
	{
		m_Velocity.y = m_JumpParameter.m_DefaultFallSpeed;
	}

	//落下し始めたら
	if (m_Velocity.y < m_JumpParameter.m_ChangeFallSpeed)
	{
		ChangeState(Character::STATE::AIRMOVE);
	}

	m_pos += m_MoveVector;
	m_pos += m_Velocity;
}