#include "CharacterBase_JumpState.h"

void CharacterBase_JumpState::Init()
{
	if (m_pCharacterParameter->JumpCount == 0)
	{
		//�ŏ��̃W�����v�������ꍇ
		m_pCharacterParameter->Velocity.y = m_pJumpParameter->FirstJumpPower;
	}
	else
	{
		//���ڂ̃W�����v�������ꍇ
		m_pCharacterParameter->Velocity.y = m_pJumpParameter->SecondJumpPower;
	}

	m_pCharacterParameter->MoveVector = CVector3::GetZero();
	m_pCharacterParameter->JumpCount++;
}

void CharacterBase_JumpState::Uninit()
{

}

void CharacterBase_JumpState::Update()
{
	if (m_pCharacterParameter->HitGround)
	{
		m_pCharacter->SetNextState(Character::STATE::State_Idle);		
	}


	bool OnButton = false;

	m_pCharacterParameter->MoveVector.x =  
		m_pController->GetMoveInput().x * m_pMoveParameter->AirSideMoveSpeed;

	m_pCharacterParameter->Velocity.x *= m_pMoveParameter->AirDrag;	//��C��R���|����

	//������x�W�����v���ł���
	if (m_pCharacterParameter->JumpCount < m_pJumpParameter->MaxJumpCount)
	{
		if (m_pController->GetJumpTrigger())
		{
			m_pCharacter->SetNextState(Character::STATE::State_Jump);
		}
	}

	//�U��
	if (m_pController->GetAttack())
	{
		m_pCharacter->SetNextState(Character::STATE::State_AttackAirN); //��̐ݒ�
	}

	m_pCharacterParameter->Velocity.y 
		*= m_pJumpParameter->JumpUpReduction;		//1��菬�������l���|����

	//�d�͐���(�ō��̗������x�ɂȂ�����)(�ꉞ�̏���)
	if (m_pCharacterParameter->Velocity.y < m_pJumpParameter->DefaultFallSpeed)
	{
		m_pCharacterParameter->Velocity.y = m_pJumpParameter->DefaultFallSpeed;
	}

	//�������n�߂���
	if (m_pCharacterParameter->Velocity.y < m_pJumpParameter->ChangeFallSpeed)
	{
		m_pCharacter->SetNextState(Character::STATE::State_AirMove);
	}

	m_pCharacterParameter->Pos += m_pCharacterParameter->MoveVector;
	m_pCharacterParameter->Pos += m_pCharacterParameter->Velocity;

	//�W�����v������̈ʒu���V��𒴂��Ă�����߂��Ă��
	if (m_pCharacterParameter->Pos.y > m_pStage->GetDeadLineTopY())
	{
		m_pCharacterParameter->Pos.y = m_pStage->GetDeadLineTopY();
	}
}