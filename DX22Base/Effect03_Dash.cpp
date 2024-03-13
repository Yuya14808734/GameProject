#include "Effect03_Dash.h"

EffectDash::EffectDash()
{
	m_TimeCount = 0.0f;
}

EffectDash::~EffectDash()
{
	EffectManager::GetManager()->StopEffect(m_efkHnd_Dash);
}

void EffectDash::Update()
{
	m_TimeCount += 1.0f / 60.0f;

	if (m_TimeCount > m_EffectEndTime)
	{
		m_isDestroy = true;
	}
}

void EffectDash::Draw()
{
	EffectManager::EffectDraw(m_efkHnd_Dash);
}

void EffectDash::PausedEffect(bool paused)
{
	EffectManager::GetManager()->SetPaused(m_efkHnd_Dash, paused);
}

void EffectDash::PlayDashEffect(const CVector3& pos, bool inv)
{
	m_efkHnd_Dash = EffectManager::GetManager()->
		Play(EffectManager::GetEffect("DashEffect01"),
		pos.x, pos.y, pos.z);

	EffectManager::GetManager()->SetScale(m_efkHnd_Dash, 0.3f, 0.3f, 0.3f);

	if (inv)
	{
		EffectManager::GetManager()->SetRotation(m_efkHnd_Dash, 0.0f, 
			3.141592f * 0.5f, 0.0f);
	}
	else
	{
		EffectManager::GetManager()->SetRotation(m_efkHnd_Dash, 0.0f,
			-3.141592f * 0.5f, 0.0f);
	}
}
