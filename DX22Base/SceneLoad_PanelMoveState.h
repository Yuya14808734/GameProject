#pragma once
#include "SceneLoad_BaseState.h"

class SceneLoad_PanelMoveState : public SceneLoad_BaseState
{
public:
	SceneLoad_PanelMoveState();
	~SceneLoad_PanelMoveState() override;

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
private:
};
