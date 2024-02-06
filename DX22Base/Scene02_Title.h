#pragma once
#include "Scene.h"
#include "Image2D.h"
#include "Image3D.h"
#include "StatePattern.h"

class SceneTitle : public CScene
{
private:
	enum class TITLESTATE : int
	{
		TITLEDRAW = 0,
		TITLESELECT,
		MAX,
	};

public:
	SceneTitle() {}
	~SceneTitle() override {}


	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	State* SetNextState(TITLESTATE TitleState);		//ステートの設定
	void ChangeNextState();						//ステートの取得

private:
	StateContext m_TitleStateContext;
	Image2D m_BackGround00;
	Image2D m_BackGround01;
};
