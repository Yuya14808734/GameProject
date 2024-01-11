#pragma once
#include "CharacterBase_LeanBackState.h"

class Character00_LeanBackState : public CharacterBase_LeanBackState
{
public:
	Character00_LeanBackState() {};
	~Character00_LeanBackState() override {};

	void Init() override;
	void Uninit() override;
	void Update() override;

private:
	int m_FrameCount = 0;
	float m_AnimeTime = 0.0f;
};
