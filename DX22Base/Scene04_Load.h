#pragma once
#include "Scene.h"
#include "Image2D.h"
#include "Image3D.h"
#include "StatePattern.h"
#include "FadeOut00_ColorFade.h"

class SceneLoad : public CScene
{
private:
	enum class LOADSTATE : int
	{
		FADEIN = 0,
		ANIMATION,
		LOAD,
		FADEOUT,
		MAX,
	};

public:
	SceneLoad() {}
	~SceneLoad() override {}

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	State* SetNextState(LOADSTATE LoadState);	//ステートの設定
	void ChangeNextState();						//ステートの取得

private:
	StateContext m_LoadStateContext;
	Image2D m_BackGround;
	FadeInColorFade m_ColorFade;
};

