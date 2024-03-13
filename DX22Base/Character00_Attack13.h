#pragma once
#include "Character_Attack.h"

class Character00_Attack13 : public Character_AttackState
{
public:
	Character00_Attack13() {};
	~Character00_Attack13() override {};

	void Init() override;
	void Uninit() override;
	void Update() override;
	void HitCharacter(Character* pHitCharacter, Character::ATTACKPARAM* pHitAttack) override;

private:
	int m_FrameCount = 0;
	float m_AnimeTime = 0.0f;
	bool m_PushButton = false;
};