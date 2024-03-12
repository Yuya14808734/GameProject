#include "CharacterBase_FallDownState.h"
#include "SoundManager.h"

//==================================================
//
//吹っ飛ばされた後の落ちるときのアップデート
//
//==================================================

void CharacterBase_FallDownState::Init()
{

}

void CharacterBase_FallDownState::Uninit()
{

}

void CharacterBase_FallDownState::Update()
{
	if (m_pCharacterParameter->HitGround)
	{
		m_pCharacter->SetNextState(Character::STATE::State_Down);
		m_pCharacterParameter->Velocity.y += m_pJumpParameter->FallDownGravity;			//重力を掛ける
		m_pCharacterParameter->Pos += m_pCharacterParameter->Velocity;
		SoundManager::PlaySE("FootSteps01_Walk");
		return;
	}

	bool OnButton = false;

	float LeftStickX = m_pController->GetMoveInput().x * m_pMoveParameter->AirSideMoveSpeed;
	m_pCharacterParameter->Velocity.x 
		= fabsf(LeftStickX) > fabsf(m_pCharacterParameter->Velocity.x) ? LeftStickX : m_pCharacterParameter->Velocity.x;

	//もう一度ジャンプができる
	if (m_pCharacterParameter->JumpCount < m_pJumpParameter->MaxJumpCount)
	{
		if (m_pController->GetJumpTrigger())
		{
			m_pCharacterParameter->JumpCount++;
			m_pCharacterParameter->Velocity.y = m_pJumpParameter->FirstJumpPower;
			m_pCharacter->SetNextState(Character::STATE::State_Jump);
		}
	}

	//攻撃
	if (m_pController->GetAttack())
	{
		m_pCharacter->SetNextState(Character::STATE::State_AttackAirN); //空中N
	}

	if (!OnButton)
	{
		m_pCharacterParameter->Velocity.x *= m_pMoveParameter->AirDrag;	//空気抵抗を掛ける
	}

	m_pCharacterParameter->Velocity.y 
		+= m_pJumpParameter->FallDownGravity;			//重力を足す

	//重力制御(最大の落下速度になったら)
	if (m_pCharacterParameter->Velocity.y < m_pJumpParameter->DefaultFallSpeed)
	{
		m_pCharacterParameter->Velocity.y = m_pJumpParameter->DefaultFallSpeed;
	}

	m_pCharacterParameter->Pos += m_pCharacterParameter->MoveVector;
	m_pCharacterParameter->Pos += m_pCharacterParameter->Velocity;
}