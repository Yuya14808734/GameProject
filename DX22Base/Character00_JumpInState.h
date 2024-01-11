#pragma once
#include "CharacterBase_JumpInState.h"

class Character00_JumpInState : public CharacterBase_JumpInState
{
public:
	Character00_JumpInState() {};
	~Character00_JumpInState() override {};

	void Init() override;
	void Uninit() override;
	void Update() override;

private:
	int m_FrameCount = 0;
	float m_AnimeTime = 0.0f;
};
