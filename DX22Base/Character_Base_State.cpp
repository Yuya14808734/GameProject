#include "Character_Base.h"
#include "Input.h"
#include "Attack_Base.h"

void Character::IdleUpdate()
{
	//---行ける状態---
	//ジャンプ
	//攻撃
	//歩く
	//走る
	

	if (IsKeyPress(VK_RIGHT) || IsKeyPress(VK_LEFT))
	{
		m_State = Character::STATE::WALK;
	}

	if (IsKeyPress(VK_UP))
	{
		m_State = Character::STATE::JUMP;
	}

	//攻撃
	if (false)
	{
		m_State = Character::STATE::ATTACK;
	}
}

void Character::WalkUpdate()
{
	//---行ける状態---
	//ジャンプ
	//攻撃
	//歩く
	//走る

	bool NoButton = true;

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


	m_Velocity.y += m_Gravity;

	//一応重力制御も書いておく
	if (m_Velocity.y < m_MaxFallSpeed)
	{
		m_Velocity.y = m_MaxFallSpeed;
	}

	m_pos += m_MoveVector;
	m_pos += m_Velocity;
}

void Character::DashUpdate()
{
	//---行ける状態---
	//
	//攻撃
	//歩く
	//走る

	bool NoButton = true;

	if (IsKeyPress(VK_RIGHT))
	{
		if (m_MoveVector.x < -0.01f)
		{
			//左に行っていた場合、摩擦を掛ける
			m_MoveVector.x *= m_Friction;
		}
		else
		{
			m_MoveVector.x = m_DashSpeed;
		}

		NoButton = false;
	}

	if (IsKeyPress(VK_LEFT))
	{
		if (m_MoveVector.x > 0.01f)
		{
			//右に行っていた場合、摩擦を掛ける
			m_MoveVector.x *= m_Friction;
		}
		else
		{
			m_MoveVector.x = m_DashSpeed;
		}

		NoButton = false;
	}

	//ボタンが何も押されていなければ
	if (NoButton)
	{
		//止まる
		m_MoveVector.x *= m_Friction;

		//ある程度遅くなったら
		if (m_MoveVector.x < 0.01f || m_MoveVector.x > -0.01f)
		{
			m_MoveVector.x = 0.0f;
			m_State = Character::STATE::IDLE;
		}
	}

	//ジャンプ
	if (IsKeyPress(VK_UP))
	{
		m_Velocity.x = m_MoveVector.x;
		m_Velocity.y = m_JumpPower;
		m_State = Character::STATE::JUMP;
	}

	m_Velocity.y += m_Gravity;

	//一応重力制御も書いておく
	if (m_Velocity.y < m_MaxFallSpeed)
	{
		m_Velocity.y = m_MaxFallSpeed;
	}

	m_pos += m_MoveVector;
	m_pos += m_Velocity;
}

void Character::AttackUpdate()
{
	//---行ける状態---
	//アタックによって変わる
	//地面での攻撃ならIdle
	//空中ならFull

	//アタックの更新は任せる
	if(m_pNowAttack != nullptr)
	m_pNowAttack->Attack_Update();
}

//==============================================
//吹っ飛んでいるときのアップデート
void Character::BlowOffUpdate()
{
	if (IsKeyPress(VK_RIGHT))
	{
		m_MoveVector.x = m_FallSideMoveSpeed;
	}

	if (IsKeyPress(VK_LEFT))
	{
		m_MoveVector.x = -m_FallSideMoveSpeed;
	}

	//縦に飛ばすベクトルを小さくする
	if (m_Velocity.y < m_MaxFallSpeed || m_Velocity.y > 0.01f)
	{
		m_Velocity.y *= m_AirResistance;
	}

	//横に飛ばすベクトルを小さくする
	m_Velocity.x *= m_AirResistance;

	//ある程度動かなくなったら落下状態に変える
	if (fabsf(m_Velocity.x) < 0.3f && fabsf(m_Velocity.y) < 0.3f)
	{
		m_State = Character::STATE::FALL;
	}

	//一応重力制御も書いておく
	if (m_Velocity.y < m_MaxFallSpeed)
	{
		m_Velocity.y = m_MaxFallSpeed;
	}

	m_pos += m_MoveVector;
	m_pos += m_Velocity;

}

void Character::JumpUpdate()
{
	if (IsKeyPress(VK_RIGHT))
	{
		m_MoveVector.x = m_FallSideMoveSpeed;
	}

	if (IsKeyPress(VK_LEFT))
	{
		m_MoveVector.x = -m_FallSideMoveSpeed;
	}

	m_Velocity.x *= m_AirResistance;	//空気抵抗を掛ける
	m_Velocity.y += m_Gravity;			//重力を掛ける

	//重力制御
	if (m_Velocity.y < m_MaxFallSpeed)
	{
		m_Velocity.y = m_MaxFallSpeed;
	}

	//落下し始めたら
	if (m_Velocity.y < 0.1f)
	{
		m_State = Character::STATE::FALL;
	}

	m_pos += m_MoveVector;
	m_pos += m_Velocity;
}

void Character::FallUpdate()
{
	if (IsKeyPress(VK_RIGHT))
	{
		m_MoveVector.x = m_FallSideMoveSpeed;
	}

	if (IsKeyPress(VK_LEFT))
	{
		m_MoveVector.x = -m_FallSideMoveSpeed;
	}
}

void Character::DownUpdate()
{
	
}

void Character::HitGround()
{
}

void Character::SetAttack(Attack* pAttack)
{
	if (m_pNowAttack != nullptr)
	{
		m_pNowAttack->Attack_Uninit();
		delete m_pNowAttack;
	}

	m_pNowAttack = pAttack;
	if (m_pNowAttack != nullptr)
	{
		m_pNowAttack->Attack_Init();
		m_State = Character::STATE::ATTACK;
	}
}
