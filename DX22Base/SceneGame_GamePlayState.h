#pragma once
#include "SceneBase_State.h"

class SceneGame_PlayState : public Scene_State
{
public:
	SceneGame_PlayState() {};
	~SceneGame_PlayState() override {};

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:
	void Collision_Player_Player();
	void Collision_Attack_Player();
	void Collision_Player_Stage();
	void CheckGameEnd();

private:
	int m_VisibleGo_CountTime = 0;

};