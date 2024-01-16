#pragma once

#include "Character_State.h"

class Character00_StartAnimationState : public Character_State
{
	enum class AnimationState : int
	{
		Start = 0,
		Idle,
		MAX
	};

public:
	Character00_StartAnimationState() {};
	~Character00_StartAnimationState() override {};

	virtual void Init() override;
	virtual void Uninit() override;
	virtual void Update() override;

private:
	void StartAnimeUpdate();
	void IdleAnimeUpdate();
	void InitAnime(const std::string& AnimeName);
	void LookStageCenter();

private:
	AnimationState m_NowAnimeState;
	int m_FrameCount = 0;
};
