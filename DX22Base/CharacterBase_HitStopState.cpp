#include "CharacterBase_HitStopState.h"
#include <math.h>

void CharacterBase_HitStopState::Init()
{
	m_TempPos = m_pCharacterParameter->Pos;
}

void CharacterBase_HitStopState::Uninit()
{
	m_Shake = false;
}

void CharacterBase_HitStopState::Update()
{
	CVector3 AddDrawPos;

	if (m_Shake)
	{
		AddDrawPos.x = 0.3f * (static_cast<float>(rand() % 2000) / 1000.0f - 1.0f);
		AddDrawPos.y = 0.02f * (static_cast<float>(rand() % 2000) / 1000.0f - 1.0f);
	}

	//位置をずらして揺らす
	m_pCharacterParameter->Pos = m_TempPos + AddDrawPos;

	//ヒットストップをする時間を計測
	m_HitStopCount--;

	if (m_HitStopCount == 0)
	{
		m_pCharacter->SetNextState(m_NextState);
	}
}

void CharacterBase_HitStopState::SetHitStop(int HitStopFrameTime, Character::STATE NextState, bool IsShake)
{
	m_HitStopCount = HitStopFrameTime;
	m_NextState = NextState;
	m_Shake = IsShake;
}
