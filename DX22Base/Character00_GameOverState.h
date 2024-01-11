#pragma once
#include "CharacterBase_GameOverState.h"

class Character00_GameOverState : public CharacterBase_GameOverState
{
public:
	Character00_GameOverState() {};
	~Character00_GameOverState() override {};

	void Init() override;
	void Uninit() override;
	void Update() override;

private:
	int m_FrameCount = 0;
	float m_AnimeTime = 0.0f;
};
