#pragma once
#include "CharacterBase_WakeUpState.h"

class Character00_WakeUpState : public CharacterBase_WakeUpState
{
public:
	Character00_WakeUpState() {};
	~Character00_WakeUpState() override {};

	void Init() override;
	void Uninit() override;
	void Update() override;

private:
	int m_FrameCount = 0;
	float m_AnimeTime = 0.0f;
};
