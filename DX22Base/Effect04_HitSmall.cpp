#include "Effect04_HitSmall.h"

EffectHitSmall::EffectHitSmall()
{
	m_TimeCount = 0.0f;
}

EffectHitSmall::~EffectHitSmall()
{
	EffectManager::GetManager()->StopEffect(m_efkHnd_Hit);
}

void EffectHitSmall::Update()
{
	m_TimeCount += 1.0f / 60.0f;

	if (m_TimeCount > m_EffectEndTime)
	{
		m_isDestroy = true;
	}
}

void EffectHitSmall::Draw()
{
	EffectManager::EffectDraw(m_efkHnd_Hit);
}

void EffectHitSmall::PausedEffect(bool paused)
{
	EffectManager::GetManager()->SetPaused(m_efkHnd_Hit, paused);
}

void EffectHitSmall::PlayHitEffect(CVector3 pos)
{
	m_efkHnd_Hit = EffectManager::GetManager()->
		Play(EffectManager::GetEffect("DamageEffect02"),
			pos.x, pos.y, pos.z);

	EffectManager::GetManager()->SetScale(m_efkHnd_Hit, 0.5f, 0.5f, 0.5f);
}
