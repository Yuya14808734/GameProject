#pragma once
#include "SceneGame_BaseState.h"
#include "TextureClass.h"
#include "Image2D.h"

class SceneGame_DisConnectControllerState : public SceneGame_BaseState
{
private:
	const float SceneChangeWaitTime = 3.0f;

public:
	SceneGame_DisConnectControllerState() {};
	~SceneGame_DisConnectControllerState() override {};

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

public:
	Image2D m_DissConnectControllerTextImage;
	float m_ReturnCount = 0.0f;
};
