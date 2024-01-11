#include "CharacterBase_DownState.h"
#include "Input.h"
#include "XboxKeyboard.h"


void CharacterBase_DownState::Init()
{
	m_pCharacterParameter->MoveVector = CVector3::GetZero();
	m_pCharacterParameter->Velocity = CVector3::GetZero();
}

void CharacterBase_DownState::Uninit()
{

}

void CharacterBase_DownState::Update()
{
	//地面に当たっていなければ
	if (!m_pCharacterParameter->HitGround)
	{
		m_pCharacter->SetNextState(Character::STATE::State_AirMove);
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

	//これ以上はアニメーションが終了したら起き上がれるようにしたいので
	//継承先で実装してください
}