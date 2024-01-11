#pragma once
#include "CharacterBase_DownState.h"

class Character00_DownState : public CharacterBase_DownState
{
public:
	Character00_DownState() {};
	~Character00_DownState() override {};

	void Init() override;
	void Uninit() override;
	void Update() override;

private:
	int m_FrameCount = 0;
	float m_AnimeTime = 0.0f;
};