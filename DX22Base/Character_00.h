#pragma once
#include "Character_Base.h"

class Character_00 : public Character
{
private:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void IdleInit() override;
	void IdleUpdate() override;

	void WalkInit() override;
	void WalkUpdate() override;

	void DashInit() override;
	void DashUpdate() override;

	void HitGround() override;
private:

	float m_AnimeTime = 0.0f;
};