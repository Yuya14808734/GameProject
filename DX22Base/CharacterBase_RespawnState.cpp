#include "CharacterBase_RespawnState.h"

void CharacterBase_RespawnState::Init()
{
	m_RespawnStartPos = m_RespawnEndPos = m_pStage->AddRespawn();
	m_RespawnStartPos.y = m_pStage->GetDeadLineTopY() - 1.0f;
	m_RespawnLerpPercent = 0.0f;
	m_pCharacter->SetInvincible(true);
	m_pCharacterParameter->Pos = m_RespawnStartPos;
}

void CharacterBase_RespawnState::Uninit()
{
	m_pStage->MinaRespawn();
	m_pCharacter->SetInvincible(false);
	m_pCharacter->SetCheckDead(true);
}

void CharacterBase_RespawnState::Update()
{
	m_RespawnLerpPercent = m_RespawnLerpPercent + (1.0f / ((60.0f) * 2.0f));
	m_pCharacterParameter->Pos = ((m_RespawnEndPos - m_RespawnStartPos) * m_RespawnLerpPercent) + m_RespawnStartPos;

	if (m_RespawnLerpPercent >= 1.0f)
	{
		m_pCharacter->SetNextState(Character::STATE::State_Idle);
	}
}
