#pragma once
#include "EffectBase.h"
#include "Calculation.h"
#include "Image3D.h"


class SingleSmoke : public EffectBase
{
public:
	SingleSmoke();
	~SingleSmoke() override;
	void Update() override;
	void Draw() override;
	void PausedEffect(bool paused = true) override;
	void SetPos(const CVector3& pos);
	void SetTime(float EndTime);

private:
	Image3D m_SmokeImage;
	float m_Time = 0.0f;
	float m_EndTime = 0.0f;
};