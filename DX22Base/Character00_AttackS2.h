#pragma once
#include "Character_Base.h"
#include "Effect_Manager.h"

class Character00_AttackS2 : public Character_AttackState
{
public:
	Character00_AttackS2() {};
	~Character00_AttackS2() override {};

	void Init() override;
	void Uninit() override;
	void Update() override;
	void HitCharacter(Character* pHitCharacter) override;

private:
	int m_FrameCount = 0;
	float m_AnimeTime = 0.0f;
	bool m_PushButton = false;
	int m_HitAttackStopCount = 0;

	//エフェクトの変数
	Effekseer::Handle m_SwordHandle;
};

