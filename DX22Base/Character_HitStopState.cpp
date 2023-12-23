#include "Character_Base.h"
#include <math.h>

void Character::HitStopInit()
{

}

void Character::HitStopUninit()
{
	m_AddDrawPos = CVector3::GetZero();
	m_Shake = false;
}

void Character::HitStopUpdate()
{
	if (m_Shake)
	{
		m_AddDrawPos.x = 0.3f * (static_cast<float>(rand() % 2000) / 1000.0f - 1.0f);
		m_AddDrawPos.y = 0.02f * (static_cast<float>(rand() % 2000) / 1000.0f - 1.0f);
	}

	//ヒットストップをする時間を計測
	m_HitStopCount--;

	if (m_HitStopCount == 0)
	{
		ChangeState(m_HitStopNextState);
	}
}