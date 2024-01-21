#pragma once
#include "Effect_Manager.h"

class EffectBase
{
public:
	EffectBase();
	virtual ~EffectBase();
	virtual void Update();
	virtual void Draw();
	virtual void PausedEffect(bool Paused = true);

	void SetDestroy(bool destroy = true);
	bool GetisDestroy();

protected:
	bool m_isDestroy = false;
};