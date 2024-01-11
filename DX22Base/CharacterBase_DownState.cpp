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
	//�n�ʂɓ������Ă��Ȃ����
	if (!m_pCharacterParameter->HitGround)
	{
		m_pCharacter->SetNextState(Character::STATE::State_AirMove);
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

	//����ȏ�̓A�j���[�V�������I��������N���オ���悤�ɂ������̂�
	//�p����Ŏ������Ă�������
}