#pragma once
#include "SceneResult_BaseState.h"

class SceneResult_DrawResult : public SceneResult_BaseState
{
public:
	SceneResult_DrawResult() {};
	~SceneResult_DrawResult() override {};


	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
private:
};
