#pragma once
#include "EffectBase.h"
#include "Calculation.h"

class EffectHitSmall : public EffectBase
{
private:
	const float m_EffectEndTime = 2.0f;

public:
	EffectHitSmall();
	~EffectHitSmall() override;
	void Update() override;
	void Draw() override;
	void PausedEffect(bool paused = true) override;
	void PlayHitEffect(CVector3 pos);

private:
	float m_TimeCount = 0.0f;
	Effekseer::Handle m_efkHnd_Hit = NULL;
};