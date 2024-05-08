#pragma once
#include "EffectBase.h"
#include "Calculation.h"

//==========================================================
// 
// �U���������������̃q�b�g�G�t�F�N�g
// 
//==========================================================

class EffectHitBig : public EffectBase
{
private:
	const float m_EffectEndTime = 2.0f;

public:
	EffectHitBig();
	~EffectHitBig() override;
	void Update() override;
	void Draw() override;
	void PausedEffect(bool paused = true) override;
	void PlayHitEffect(CVector3 pos);

private:
	float m_TimeCount = 0.0f;
	Effekseer::Handle m_efkHnd_Hit = NULL;
};