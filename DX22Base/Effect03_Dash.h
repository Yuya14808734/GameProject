#pragma once
#include "EffectBase.h"
#include "Calculation.h"

class EffectDash : public EffectBase
{
private:
	const float m_EffectEndTime = 1.0f;

public:
	EffectDash();
	~EffectDash() override;
	void Update() override;
	void Draw() override;
	void PausedEffect(bool paused = true) override;
	void PlayDashEffect(const CVector3& pos,bool inv);

private:
	float m_TimeCount = 0.0f;
	Effekseer::Handle m_efkHnd_Dash = NULL;
};