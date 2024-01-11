#pragma once
#include "CharacterBase_FallDownState.h"

class Character00_FallDownState : public CharacterBase_FallDownState
{
public:
	Character00_FallDownState() {};
	~Character00_FallDownState() override {};

	void Init() override;
	void Uninit() override;
	void Update() override;

private:
	int m_FrameCount = 0;
	float m_AnimeTime = 0.0f;
};