#pragma once
#include "StatePattern.h"
#include "Image2D.h"
#include "PushButtonText.h"
#include "FadeIn00_GameEnd.h"
#include "PraiseWinnerPlayerText.h"
#include "Scene03_Result.h"

class SceneResult_BaseState : public State
{
public:
	SceneResult_BaseState() {};
	virtual ~SceneResult_BaseState() override {};
	virtual void Init() override {};
	virtual void Uninit() override {};
	virtual void Update() override {};
	virtual void Draw() override {};


//====================================================================
// SetÅEGetä÷êî
//====================================================================
public:
	void SetSceneResult(SceneResult* pSceneResult) 
	{ m_pSceneResult = pSceneResult; }

	void SetBackGround(Image2D* pBackGround) 
	{ m_pBackGround = pBackGround; }

	void SetCharacterImage(Image2D* pCharacterImage) 
	{ m_pCharacterImage = pCharacterImage; }

	void SetWinPanelImage(Image2D* pWinPanelImage) 
	{ m_pWinPanelImage = pWinPanelImage; }

	void SetPushButtonTextImage(PushButtonText* pPushButtonTextImage) 
	{ m_pPushButtonTextImage = pPushButtonTextImage; }

	void SetFadeInWipe(FadeInWipe* pStartWipeFade) 
	{ m_pStartWipeFade = pStartWipeFade; }

	void SetPraiseWinnerPlayerText(PraiseWinnerPlayerText* pPraiseWinnerPlayerText)
	{ m_pPraiseWinnerPlayerText = pPraiseWinnerPlayerText; }

	void SetWinnerPlayerNum(Image2D* pWinnerPlayerNum) 
	{ m_pWinnerPlayerNum = pWinnerPlayerNum; }

protected:
	SceneResult* m_pSceneResult = nullptr;
	Image2D* m_pBackGround = nullptr;
	Image2D* m_pCharacterImage = nullptr;
	Image2D* m_pWinPanelImage = nullptr;
	PushButtonText* m_pPushButtonTextImage = nullptr;
	FadeInWipe* m_pStartWipeFade = nullptr;
	PraiseWinnerPlayerText* m_pPraiseWinnerPlayerText = nullptr;
	Image2D* m_pWinnerPlayerNum = nullptr;
};
