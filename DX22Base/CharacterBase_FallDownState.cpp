#include "CharacterBase_FallDownState.h"
#include "SoundManager.h"

//==================================================
//
//������΂��ꂽ��̗�����Ƃ��̃A�b�v�f�[�g
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
		m_pCharacterParameter->Velocity.y += m_pJumpParameter->FallDownGravity;			//�d�͂��|����
		m_pCharacterParameter->Pos += m_pCharacterParameter->Velocity;
		SoundManager::PlaySE("FootSteps01_Walk");
		return;
	}

	bool OnButton = false;

	float LeftStickX = m_pController->GetMoveInput().x * m_pMoveParameter->AirSideMoveSpeed;
	m_pCharacterParameter->Velocity.x 
		= fabsf(LeftStickX) > fabsf(m_pCharacterParameter->Velocity.x) ? LeftStickX : m_pCharacterParameter->Velocity.x;

	//������x�W�����v���ł���
	if (m_pCharacterParameter->JumpCount < m_pJumpParameter->MaxJumpCount)
	{
		if (m_pController->GetJumpTrigger())
		{
			m_pCharacterParameter->JumpCount++;
			m_pCharacterParameter->Velocity.y = m_pJumpParameter->FirstJumpPower;
			m_pCharacter->SetNextState(Character::STATE::State_Jump);
		}
	}

	//�U��
	if (m_pController->GetAttack())
	{
		m_pCharacter->SetNextState(Character::STATE::State_AttackAirN); //��N
	}

	if (!OnButton)
	{
		m_pCharacterParameter->Velocity.x *= m_pMoveParameter->AirDrag;	//��C��R���|����
	}

	m_pCharacterParameter->Velocity.y 
		+= m_pJumpParameter->FallDownGravity;			//�d�͂𑫂�

	//�d�͐���(�ő�̗������x�ɂȂ�����)
	if (m_pCharacterParameter->Velocity.y < m_pJumpParameter->DefaultFallSpeed)
	{
		m_pCharacterParameter->Velocity.y = m_pJumpParameter->DefaultFallSpeed;
	}

	m_pCharacterParameter->Pos += m_pCharacterParameter->MoveVector;
	m_pCharacterParameter->Pos += m_pCharacterParameter->Velocity;
}