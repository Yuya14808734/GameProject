#include "CharacterBase_DashState.h"

void CharacterBase_DashState::Init()
{

}

void CharacterBase_DashState::Uninit()
{

}

void CharacterBase_DashState::Update()
{
	//�n�ʂɓ������Ă��Ȃ����
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
			//���ɍs���Ă����ꍇ�A���C���|����
			m_pCharacterParameter->Velocity.x *= m_pMoveParameter->Friction;
		}
		else
		{
			m_pCharacterParameter->Velocity.x = m_pMoveParameter->DashSpeed;
		}

		//�E�ɍs���Ă���
		m_pCharacter->SetLookRight();

		NoButton = false;
	}

	if(NowX < 0.0f)
	{
		if (m_pCharacterParameter->Velocity.x > 0.01f)
		{
			//�E�ɍs���Ă����ꍇ�A���C���|����
			m_pCharacterParameter->Velocity.x *= m_pMoveParameter->Friction;
		}
		else
		{
			m_pCharacterParameter->Velocity.x = -m_pMoveParameter->DashSpeed;
		}

		//���ɍs���Ă���
		m_pCharacter->SetLookLeft();

		NoButton = false;
	}

	//�{�^��������������Ă��Ȃ����
	if (NoButton)
	{
		//�~�܂�
		m_pCharacterParameter->Velocity.x *= m_pMoveParameter->Friction;

		//������x�x���Ȃ�����
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

	//�W�����v
	if (m_pController->GetJumpTrigger())
	{
		m_pCharacter->SetNextState(Character::STATE::State_JumpIn);
	}

	m_pCharacterParameter->Velocity.y += m_pJumpParameter->FallDownGravity;

	//�ꉞ�d�͐���������Ă���
	if (m_pCharacterParameter->Velocity.y < m_pJumpParameter->DefaultFallSpeed)
	{
		m_pCharacterParameter->Velocity.y = m_pJumpParameter->DefaultFallSpeed;
	}

	m_pCharacterParameter->Pos += m_pCharacterParameter->Velocity;
}