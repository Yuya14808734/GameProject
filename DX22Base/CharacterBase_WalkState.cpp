#include "CharacterBase_WalkState.h"

void CharacterBase_WalkState::Init()
{
	m_pCharacterParameter->MoveVector.x = 0.0f;
	m_pCharacterParameter->Velocity.x = 0.0f;
}

void CharacterBase_WalkState::Uninit()
{

}

void CharacterBase_WalkState::Update()
{
	//�n�ʂɓ������Ă��Ȃ����
	if (!m_pCharacterParameter->HitGround)
	{
		m_pCharacter->SetNextState(Character::STATE::State_AirMove);
	}

	bool NoButton = true;

	m_pCharacterParameter->MoveVector.x 
		= m_pController->GetMoveInput().x * m_pMoveParameter->WalkSpeed;

	if (m_pCharacterParameter->MoveVector.x != 0.0f)
	{
		NoButton = false;

		if (m_pCharacterParameter->MoveVector.x > 0.0f)
		{
			//�E�ɍs���Ă���
			m_pCharacter->SetLookRight();
		}
		else
		{
			//���ɍs���Ă���
			m_pCharacter->SetLookLeft();
		}

	}

	//�{�^��������������Ă��Ȃ����
	if (NoButton)
	{
		m_pCharacter->SetNextState(Character::STATE::State_Idle);
		//ChangeState(Character::STATE::IDLE);
	}

	//�U��
	if (m_pController->GetAttack())
	{
		m_pCharacter->SetNextState(Character::STATE::State_AttackS2);
	}

	//�W�����v
	if (m_pController->GetJumpTrigger())
	{
		m_pCharacter->SetNextState(Character::STATE::State_JumpIn);
	}

	//���Ⴊ�݂������
	/*if (IsKeyPress(VK_DOWN))
	{

	}*/

	m_pCharacterParameter->Velocity.y += m_pJumpParameter->FallDownGravity;

	//�ꉞ�d�͐���������Ă���
	if (m_pCharacterParameter->Velocity.y < m_pJumpParameter->DefaultFallSpeed)
	{
		m_pCharacterParameter->Velocity.y = m_pJumpParameter->DefaultFallSpeed;
	}

	m_pCharacterParameter->Pos += m_pCharacterParameter->MoveVector;
	m_pCharacterParameter->Pos += m_pCharacterParameter->Velocity;
}