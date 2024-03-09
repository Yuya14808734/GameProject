#pragma once
#include "Scene.h"
#include "Image2D.h"
#include "Image3D.h"
#include "StatePattern.h"
#include "PushButtonText.h"
#include "PraiseWinnerPlayerText.h"
#include "FadeIn00_GameEnd.h"
#include "ResultWinnerCharacterImage.h"
#include "ResultWinnerNumPanel.h"
#include "Effect_Manager.h"
#include "Sound.h"

class SceneResult : public CScene
{
// ====================================================================================
// enum
// ====================================================================================
public:
	enum class RESULTSTATE : int
	{
		RESULTDRAWWINNERNUM = 0,
		RESULTDRAW,
		MAX,
	};

// ====================================================================================
// static
// ====================================================================================
private:
	static int m_WinPlayerNum;

public:
	static void SetWinPlayerNum(int Num);

// ====================================================================================
// dynamic
// ====================================================================================

private:
	const float m_WinDrawTime = 1.0f;
	const float m_CharacterDrawTime = 1.0f;

public:
	SceneResult() {}
	~SceneResult() override {}

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	State* SetNextState(RESULTSTATE ResultState);		//ステートの設定
	void ChangeNextState();						//ステートの取得

private:
	StateContext m_ResultStateContext;

	float m_CountTime = 0.0f;
	Image2D m_BackGround;
	ResultWinnerCharacterImage m_pResultWinnerCharacterImage;
	ResultWinnerNumPanel m_ResultWinnerNumPanel;
	PushButtonText m_PushButtonTextImage;
	FadeInWipe m_StartWipeFade;
	PraiseWinnerPlayerText m_PraiseWinnerPlayerText;
	Image2D m_WinnerPlayerNum;
	Image2D m_HideImage;
	Effekseer::Handle m_efkHnd_FlowerBlizzard = 0;
	BGM* m_pBGM = nullptr;
};
