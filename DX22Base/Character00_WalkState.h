#pragma once
#include "CharacterBase_WalkState.h"
#include "SoundManager.h"

class Character00_WalkState : public CharacterBase_WalkState
{
public:
	Character00_WalkState() {};
	~Character00_WalkState() override {};

	void Init() override;
	void Uninit() override;
	void Update() override;

private:
	int m_FrameCount = 0;
	float m_AnimeTime = 0.0f;
	SE* m_pRightFootStepSE = nullptr;
	SE* m_pLeftFootStepSE = nullptr;
};
