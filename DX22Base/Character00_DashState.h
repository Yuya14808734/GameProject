#pragma once
#include "CharacterBase_DashState.h"

class Character00_DashState : public CharacterBase_DashState
{
public:
	Character00_DashState() {};
	~Character00_DashState() override {};

	void Init() override;
	void Uninit() override;
	void Update() override;

private:
	int m_FrameCount = 0;
	float m_AnimeTime = 0.0f;
};