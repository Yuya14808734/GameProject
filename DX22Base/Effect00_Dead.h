#pragma once
#include "EffectBase.h"
#include "Calculation.h"

class EffectDead : public EffectBase
{
private:
	const float m_EffectEndTime = 2.0f;

public:
	EffectDead();
	~EffectDead() override;
	void Update() override;
	void Draw() override;
	void PausedEffect(bool paused = true) override;
	void PlayDeadEffect(CVector3 pos,CVector3 Direction);

private:
	float m_TimeCount = 0.0f;
	Effekseer::Handle m_efkHnd_Dead;
};