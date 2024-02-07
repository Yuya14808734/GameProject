#pragma once
#include "EffectBase.h"
#include "Calculation.h"


class SingleSmoke : public EffectBase
{
public:
	SingleSmoke();
	~SingleSmoke() override;
	void Update() override;
	void Draw() override;
	void PausedEffect(bool paused = true) override;

private:

};