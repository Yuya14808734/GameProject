#pragma once
#include "CharacterBase_JumpState.h"

class Character00_JumpState : public CharacterBase_JumpState
{
public:
	Character00_JumpState() {};
	~Character00_JumpState() override {};

	void Init() override;
	void Uninit() override;
	void Update() override;

private:
	float m_AnimeTime = 0.0f;
};
