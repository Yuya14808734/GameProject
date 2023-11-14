#pragma once
#include "Scene.h"

class SceneGame : public CScene
{
public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:
};