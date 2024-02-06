#include "CharacterBase_JumpInState.h"
#include "Input.h"
#include "XboxKeyboard.h"

void CharacterBase_JumpInState::Init()
{
	m_pCharacterParameter->JumpCharageCount = 0;
	m_pCharacterParameter->MoveVector = CVector3::GetZero();
	m_pCharacterParameter->Velocity.x = m_pCharacterParameter->MoveVector.x;
	m_pCharacterParameter->Velocity.y = 0.0f;
}

void CharacterBase_JumpInState::Uninit()
{

}

void CharacterBase_JumpInState::Update()
{
	m_pCharacterParameter->JumpCharageCount++;


	//�W�����v�{�^���̉����Ă��钷���ɂ���ăW�����v���Ă���͂�ς��Ă��
	if (m_pController->GetJumpTrigger())
	{
		if (m_pCharacterParameter->JumpCharageCount >= m_pJumpParameter->MiniJumpPushButtonCount)
		{
			//��W�����v
			m_pCharacterParameter->Velocity.y = m_pJumpParameter->FirstJumpPower;
		}
		else
		{
			//���W�����v
			m_pCharacterParameter->Velocity.y = m_pJumpParameter->FirstMiniJumpPower;
		}
	}

	if(m_pCharacterParameter->JumpCharageCount > m_pJumpParameter->JumpChargeCount)
	{
		m_pCharacter->SetNextState(Character::STATE::State_Jump);
		m_pCharacterParameter->Velocity.x = m_pCharacterParameter->MoveVector.x;
	}

	m_pCharacterParameter->Pos += m_pCharacterParameter->Velocity;
}