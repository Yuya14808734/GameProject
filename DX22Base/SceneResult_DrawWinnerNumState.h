#pragma once
#include "SceneResult_BaseState.h"

class SceneResult_DrawWinnderNumState : public SceneResult_BaseState
{
public:
	SceneResult_DrawWinnderNumState() {};
	~SceneResult_DrawWinnderNumState() override {};
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
private:
	int m_nCount = 0;
};