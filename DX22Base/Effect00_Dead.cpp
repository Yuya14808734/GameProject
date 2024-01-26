#include "Effect00_Dead.h"

EffectDead::EffectDead()
{
	m_TimeCount = 0.0f;
}

EffectDead::~EffectDead()
{
	EffectManager::GetManager()->StopEffect(m_efkHnd_Dead);
}

void EffectDead::Update()
{
	m_TimeCount += 1.0f / 60.0f;

	if (m_TimeCount > m_EffectEndTime)
	{
		m_isDestroy = true;
	}
}

void EffectDead::Draw()
{
	EffectManager::EffectDraw(m_efkHnd_Dead);
}

void EffectDead::PausedEffect(bool paused)
{
	EffectManager::GetManager()->SetPaused(m_efkHnd_Dead, paused);
}

void EffectDead::PlayDeadEffect(CVector3 pos, CVector3 Direction)
{
	float Radian = atan2f(Direction.y, Direction.x);

	m_efkHnd_Dead = EffectManager::GetManager()->
		Play(EffectManager::GetEffect("DeadEffect"), 
			pos.x, pos.y, pos.z);

	EffectManager::GetManager()->SetScale(m_efkHnd_Dead, 5.0f, 5.0f, 5.0f);
	EffectManager::GetManager()->SetRotation(m_efkHnd_Dead, 0.0f, 0.0f, Radian);
}
