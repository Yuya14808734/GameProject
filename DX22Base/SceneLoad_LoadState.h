#pragma once
#include "SceneLoad_BaseState.h"

class SceneLoad_LoadState : public SceneLoad_BaseState
{
public:
	SceneLoad_LoadState() {}
	~SceneLoad_LoadState() override {};

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
private:
};

