#include "CharacterBase_DeadState.h"

void CharacterBase_DeadState::Init()
{
	m_ChangeStateCount = 0;	//ステータスを変えるまでの時間をカウントする
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
			//まだストックがある場合
			m_pCharacter->SetNextState(Character::STATE::State_Respawn);
		}
		else
		{
			//ストックがない場合
			m_pCharacter->SetNextState(Character::STATE::State_GameOver);
		}
	}
}