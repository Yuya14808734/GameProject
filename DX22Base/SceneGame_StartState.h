#pragma once
#include "SceneBase_State.h"

class SceneGame_StartState : public Scene_State
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