#pragma once
#include "Character_Attack.h"
#include "Effect_Manager.h"

class Character00_AttackS2 : public Character_AttackState
{
private:
	const int m_HitStopFrame = 30;

public:
	Character00_AttackS2() {};
	~Character00_AttackS2() override {};

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void HitCharacter(Character* pHitCharacter) override;

private:
	int m_FrameCount = 0;
	float m_AnimeTime = 0.0f;
	bool m_PushButton = false;
	int m_HitAttackStopCount = 0;

	//エフェクトの変数
	Effekseer::Handle m_efkHnd_Sword;
};

