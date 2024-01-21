#include "EffectBase.h"

EffectBase::EffectBase()
	:m_isDestroy(false)
{
}

EffectBase::~EffectBase()
{
}

void EffectBase::Update()
{
}

void EffectBase::Draw()
{
}

void EffectBase::PausedEffect(bool Paused)
{
}

void EffectBase::SetDestroy(bool destroy)
{
	m_isDestroy = destroy;
}

bool EffectBase::GetisDestroy()
{
	return m_isDestroy;
}
