#pragma once
#include "CharacterBase_RespawnState.h"

class Character00_RespawnState : public CharacterBase_RespawnState
{
public:
	Character00_RespawnState() {};
	~Character00_RespawnState() override {};

	void Init() override;
	void Uninit() override;
	void Update() override;

private:
	int m_FrameCount = 0;
	float m_AnimeTime = 0.0f;
};
