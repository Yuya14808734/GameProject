#include "CharacterBase_AirMoveState.h"
#include "Input.h"
#include "XboxKeyboard.h"
#include "SoundManager.h"

void CharacterBase_AirMoveState::Init()
{

}

void CharacterBase_AirMoveState::Uninit()
{

}

void CharacterBase_AirMoveState::Update()
{
	if (m_pCharacterParameter->HitGround)
	{
		m_pCharacter->SetNextState(Character::STATE::State_Idle);
		SoundManager::PlaySE("FootSteps01_Walk");
	}

	bool OnButton = false;

	float LeftStickX = m_pController->GetMoveInput().x * m_pMoveParameter->AirSideMoveSpeed;
	m_pCharacterParameter->Velocity.x = 
		fabsf(LeftStickX) > fabsf(m_pCharacterParameter->Velocity.x) ? LeftStickX : m_pCharacterParameter->Velocity.x;

	//‚à‚¤ˆê“xƒWƒƒƒ“ƒv‚ª‚Å‚«‚é
	if (m_pCharacterParameter->JumpCount < m_pJumpParameter->MaxJumpCount)
	{
		if (m_pController->GetJumpTrigger())
		{
			m_pCharacterParameter->JumpCount++;
			m_pCharacterParameter->Velocity.y = m_pJumpParameter->FirstJumpPower;
			m_pCharacter->SetNextState(Character::STATE::State_Jump);
		}
	}

	//UŒ‚
	if (m_pController->GetAttack())
	{
		m_pCharacter->SetNextState(Character::STATE::State_AttackAirN);//Žã‚ÌÝ’è
	}

	if (!OnButton)
	{
		m_pCharacterParameter->Velocity.x *= m_pMoveParameter->AirDrag;	//‹ó‹C’ïR‚ðŠ|‚¯‚é
	}

	m_pCharacterParameter->Velocity.y += m_pJumpParameter->FallDownGravity;			//d—Í‚ðŠ|‚¯‚é

	//d—Í§Œä(Å‘å‚Ì—Ž‰º‘¬“x‚É‚È‚Á‚½‚ç)
	if (m_pCharacterParameter->Velocity.y < m_pJumpParameter->DefaultFallSpeed)
	{
		m_pCharacterParameter->Velocity.y = m_pJumpParameter->DefaultFallSpeed;
	}

	m_pCharacterParameter->Pos += m_pCharacterParameter->Velocity;
}