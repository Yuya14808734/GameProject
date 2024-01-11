#pragma once
#include "CharacterBase_AirMoveState.h"

class Character00_AirMoveState : public CharacterBase_AirMoveState
{
public:
	Character00_AirMoveState() {};
	~Character00_AirMoveState() override {};

	void Init() override;
	void Uninit() override;
	void Update() override;

private:
	int m_FrameCount = 0;
	float m_AnimeTime = 0.0f;
};