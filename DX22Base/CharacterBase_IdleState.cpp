#include "CharacterBase_IdleState.h"
#include "Input.h"

//===========================================================
//キャラクターが止まっているときの処理
//---行ける状態---
//ジャンプ
//攻撃(一フレームのみ,横強などはWalkに任せる)
//歩く
//走る
//===========================================================

void CharacterBase_IdleState::Init()
{

}

void CharacterBase_IdleState::Uninit()
{

}

void CharacterBase_IdleState::Update()
{
	//地面に当たっていなければ
	if (!m_pCharacterParameter->HitGround)
	{
		m_pCharacter->SetNextState(Character::STATE::State_AirMove);
	}

	CVector2 LeftStick = m_pController->GetMoveInput();

	//移動開始
	if (LeftStick.x != 0.0f)
	{
		if (m_pController->GetLeftSmash())
		{
			m_pCharacter->SetNextState(Character::STATE::State_Dash);
		}
		else
		{
			m_pCharacter->SetNextState(Character::STATE::State_Walk);
		}
	}

	//ジャンプ
	if (m_pController->GetJumpTrigger())
	{
		m_pCharacter->SetNextState(Character::STATE::State_JumpIn);
	}

	//攻撃
	if (m_pController->GetAttack())
	{
		m_pCharacter->SetNextState(Character::STATE::State_Attack11);	//弱の設定
	}

	m_pCharacterParameter->Velocity.y += m_pJumpParameter->FallDownGravity;
	m_pCharacterParameter->Velocity.x *= m_pMoveParameter->Friction;

	//一応重力制御も書いておく
	if (m_pCharacterParameter->Velocity.y < m_pJumpParameter->DefaultFallSpeed)
	{
		m_pCharacterParameter->Velocity.y = m_pJumpParameter->DefaultFallSpeed;
	}

	m_pCharacterParameter->Pos += m_pCharacterParameter->MoveVector;
	m_pCharacterParameter->Pos += m_pCharacterParameter->Velocity;
}
