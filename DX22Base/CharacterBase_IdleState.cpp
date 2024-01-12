#include "CharacterBase_IdleState.h"
#include "Input.h"

//===========================================================
//�L�����N�^�[���~�܂��Ă���Ƃ��̏���
//---�s������---
//�W�����v
//�U��(��t���[���̂�,�����Ȃǂ�Walk�ɔC����)
//����
//����
//===========================================================

void CharacterBase_IdleState::Init()
{

}

void CharacterBase_IdleState::Uninit()
{

}

void CharacterBase_IdleState::Update()
{
	//�n�ʂɓ������Ă��Ȃ����
	if (!m_pCharacterParameter->HitGround)
	{
		m_pCharacter->SetNextState(Character::STATE::State_AirMove);
	}

	CVector2 LeftStick = m_pController->GetMoveInput();

	//�ړ��J�n
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

	//�W�����v
	if (m_pController->GetJumpTrigger())
	{
		m_pCharacter->SetNextState(Character::STATE::State_JumpIn);
	}

	//�U��
	if (m_pController->GetAttack())
	{
		m_pCharacter->SetNextState(Character::STATE::State_Attack11);	//��̐ݒ�
	}

	m_pCharacterParameter->Velocity.y += m_pJumpParameter->FallDownGravity;
	m_pCharacterParameter->Velocity.x *= m_pMoveParameter->Friction;

	//�ꉞ�d�͐���������Ă���
	if (m_pCharacterParameter->Velocity.y < m_pJumpParameter->DefaultFallSpeed)
	{
		m_pCharacterParameter->Velocity.y = m_pJumpParameter->DefaultFallSpeed;
	}

	m_pCharacterParameter->Pos += m_pCharacterParameter->MoveVector;
	m_pCharacterParameter->Pos += m_pCharacterParameter->Velocity;
}
