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

	int m_FrameCount = 0;					//アタックをしているときに使うカウント
	float m_AnimeTime = 0.0f;				//アニメーションのタイム
	CharacterStateWindow m_stateWindow;		//キャラクターのデバッグウィンドウ
	//unsigned int m_FrameCount = 0;
	int m_HitAttackStopCount = 0;			//ヒットストップのカウント
	bool m_PushButton = false;

};