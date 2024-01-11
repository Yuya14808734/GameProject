#include "CharacterBase_DeadState.h"

void CharacterBase_DeadState::Init()
{
	m_ChangeStateCount = 0;	//�X�e�[�^�X��ς���܂ł̎��Ԃ��J�E���g����
	m_pCharacter->SetStock(m_pCharacter->GetStock() - 1);
}

void CharacterBase_DeadState::Uninit()
{
	m_ChangeStateCount = 0;
}

void CharacterBase_DeadState::Update()
{
	m_ChangeStateCount++;

	if (m_ChangeStateCount > 30)
	{
		if (m_pCharacter->GetStock() > 0)
		{
			//�܂��X�g�b�N������ꍇ
			m_pCharacter->SetNextState(Character::STATE::State_Respawn);
		}
		else
		{
			//�X�g�b�N���Ȃ��ꍇ
			m_pCharacter->SetNextState(Character::STATE::State_GameOver);
		}
	}
}