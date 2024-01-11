#pragma once
#include "Character_Base.h"

class Character00_AttackDS : public Character_AttackState
{
public:
	Character00_AttackDS() {};
	~Character00_AttackDS() override {};

	void Init() override;
	void Uninit() override;
	void Update() override;
	void HitCharacter(Character* pHitCharacter) override;

private:
	int m_FrameCount = 0;
	float m_AnimeTime = 0.0f;
	bool m_PushButton = false;
};

