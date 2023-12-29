#include "Character_Base.h"

void Character::RespawnInit()
{
	m_RespawnStartPos = m_RespawnEndPos = m_pStage->AddRespawn();
	m_RespawnEndPos.y = m_pStage->GetDeadLineTopY() - 1.0f;
	m_RespawnLerpPercent = 0.0f;
	m_Invincible = true;
}

void Character::RespawnUninit()
{
	m_pStage->MinaRespawn();
	m_Invincible = false;
}

void Character::RespawnUpdate()
{
	m_RespawnLerpPercent = m_RespawnLerpPercent + 1.0f / (60.0f * 0.8f);
	m_pos = ((m_RespawnEndPos - m_RespawnStartPos) * m_RespawnLerpPercent) + m_RespawnStartPos;

	if (m_RespawnLerpPercent >= 1.0f)
	{
		ChangeState(Character::STATE::IDLE);
	}
}
