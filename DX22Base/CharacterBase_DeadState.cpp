#include "CharacterBase_DeadState.h"

void CharacterBase_DeadState::Init()
{
	m_ChangeStateCount = 0;	//ステータスを変えるまでの時間をカウントする
	m_pCharacter->SetStock(m_pCharacter->GetStock() - 1);
}

void CharacterBase_DeadState::Uninit()
{
	m_ChangeStateCount = 0;

	//キャラクターで初期化しないといけないものを初期化
	m_pCharacter->SetDamage(0.0f);

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
			m_pCharacter->SetCheckDead(true);
		}
		else
		{
			//ストックがない場合
			m_pCharacter->SetNextState(Character::STATE::State_GameOver);
		}
	}
}