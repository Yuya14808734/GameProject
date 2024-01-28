#pragma once
#include "SceneLoad_BaseState.h"

class SceneLoad_CharacterDrawState : public SceneLoad_BaseState
{
public:
	SceneLoad_CharacterDrawState() {};
	~SceneLoad_CharacterDrawState() override {};

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
private:
	int m_FrameCount = 0;
};
