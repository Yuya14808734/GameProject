#pragma once
#include "SceneBase_State.h"

class SceneGame_EndState : public Scene_State
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