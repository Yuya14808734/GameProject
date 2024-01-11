#pragma once
#include "CharacterBase_HitStopState.h"

class Character00_HitStopState : public CharacterBase_HitStopState
{
public:
	Character00_HitStopState() {};
	~Character00_HitStopState() override {};

	void Init() override;
	void Uninit() override;
	void Update() override;

private:
	int m_FrameCount = 0;
	float m_AnimeTime = 0.0f;
};
