#pragma once
#include "SceneGame_BaseState.h"

class SceneGame_StartState : public SceneGame_BaseState
{
public:
	SceneGame_StartState() {};
	~SceneGame_StartState() override {};

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

protected:
	int m_Count = 0;
};