#pragma once
#include "SceneGame_BaseState.h"

class SceneGame_EndState : public SceneGame_BaseState
{
public:
	SceneGame_EndState() {};
	~SceneGame_EndState() override {};

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:
	int m_SceneChangeCount = 0;
};