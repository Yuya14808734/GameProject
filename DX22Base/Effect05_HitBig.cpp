#include "Effect05_HitBig.h"

EffectHitBig::EffectHitBig()
{
	m_TimeCount = 0.0f;
}

EffectHitBig::~EffectHitBig()
{
	EffectManager::GetManager()->StopEffect(m_efkHnd_Hit);
}

void EffectHitBig::Update()
{
	m_TimeCount += 1.0f / 60.0f;

	if (m_TimeCount > m_EffectEndTime)
	{
		m_isDestroy = true;
	}
}

void EffectHitBig::Draw()
{
	EffectManager::EffectDraw(m_efkHnd_Hit);
}

void EffectHitBig::PausedEffect(bool paused)
{
	EffectManager::GetManager()->SetPaused(m_efkHnd_Hit, paused);
}

void EffectHitBig::PlayHitEffect(CVector3 pos)
{
	m_efkHnd_Hit = EffectManager::GetManager()->
		Play(EffectManager::GetEffect("DamageEffect01"),
			pos.x, pos.y, pos.z);

	EffectManager::GetManager()->SetScale(m_efkHnd_Hit, 1.0f, 1.0f, 1.0f);
}
