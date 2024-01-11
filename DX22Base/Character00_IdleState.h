#pragma once
#include "CharacterBase_IdleState.h"

class Character00_IdleState : public CharacterBase_IdleState
{
public:
	Character00_IdleState() {};
	~Character00_IdleState() override {};

	void Init() override;
	void Uninit() override;
	void Update() override;

private:
	int m_FrameCount = 0;
	float m_AnimeTime = 0.0f;
};
