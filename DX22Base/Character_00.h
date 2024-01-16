#pragma once
#include "Character_Base.h"
#include "Effect_Manager.h"
#include "CharacterStateWindow.h"
#include "Timer.h"

class Character_00 : public Character
{
private:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

public:
	void SetDefaultCollider() override;
	State* SetNextState(STATE NextState) override;

private:

	CharacterStateWindow m_stateWindow;		//キャラクターのデバッグウィンドウ
};