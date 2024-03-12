#include "CharacterBase_DashState.h"

void CharacterBase_DashState::Init()
{

}

void CharacterBase_DashState::Uninit()
{

}

void CharacterBase_DashState::Update()
{
	//地面に当たっていなければ
	if (!m_pCharacterParameter->HitGround)
	{
		m_pCharacter->SetNextState(Character::STATE::State_AirMove);
	}

	bool NoButton = true;
	float NowX = m_pController->GetMoveInput().x * m_pMoveParameter->WalkSpeed;

	if(NowX > 0.0f)
	{
		if (m_pCharacterParameter->Velocity.x < -0.01f)
		{
			//左に行っていた場合、摩擦を掛ける
			m_pCharacterParameter->Velocity.x *= m_pMoveParameter->Friction;
		}
		else
		{
			m_pCharacterParameter->Velocity.x = m_pMoveParameter->DashSpeed;
		}

		//右に行っている
		m_pCharacter->SetLookRight();

		NoButton = false;
	}

	if(NowX < 0.0f)
	{
		if (m_pCharacterParameter->Velocity.x > 0.01f)
		{
			//右に行っていた場合、摩擦を掛ける
			m_pCharacterParameter->Velocity.x *= m_pMoveParameter->Friction;
		}
		else
		{
			m_pCharacterParameter->Velocity.x = -m_pMoveParameter->DashSpeed;
		}

		//左に行っている
		m_pCharacter->SetLookLeft();

		NoButton = false;
	}

	//ボタンが何も押されていなければ
	if (NoButton)
	{
		//止まる
		m_pCharacterParameter->Velocity.x *= m_pMoveParameter->Friction;

		//ある程度遅くなったら
		if (m_pCharacterParameter->Velocity.x < 0.01f && m_pCharacterParameter->Velocity.x > -0.01f)
		{
			m_pCharacterParameter->Velocity.x = 0.0f;
			m_pCharacter->SetNextState(Character::STATE::State_Idle);
		}
	}

	if (m_pController->GetAttack())
	{
		m_pCharacter->SetNextState(Character::STATE::State_AttackDS);
	}

	//ジャンプ
	if (m_pController->GetJumpTrigger())
	{
		m_pCharacter->SetNextState(Character::STATE::State_JumpIn);
	}

	m_pCharacterParameter->Velocity.y += m_pJumpParameter->FallDownGravity;

	//一応重力制御も書いておく
	if (m_pCharacterParameter->Velocity.y < m_pJumpParameter->DefaultFallSpeed)
	{
		m_pCharacterParameter->Velocity.y = m_pJumpParameter->DefaultFallSpeed;
	}

	m_pCharacterParameter->Pos += m_pCharacterParameter->Velocity;
}