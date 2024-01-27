#pragma once
#include "StatePattern.h"
#include "Image2D.h"
#include "PushButtonText.h"
#include "FadeIn00_GameEnd.h"
#include "PraiseWinnerPlayerText.h"
#include "Scene03_Result.h"
#include "ResultWinnerCharacterImage.h"
#include "ResultWinnerNumPanel.h"
#include "Effect_Manager.h"

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

	void SetResultWinnerCharacterImage(ResultWinnerCharacterImage* pResultWinnerCharacterImage)
	{ m_pResultWinnerCharacterImage = pResultWinnerCharacterImage; }

	void SetResultWinnerNumPanel(ResultWinnerNumPanel* pResultWinnerNumPanel)
	{ m_pResultWinnerNumPanel = pResultWinnerNumPanel; }

	void SetPushButtonTextImage(PushButtonText* pPushButtonTextImage) 
	{ m_pPushButtonTextImage = pPushButtonTextImage; }

	void SetFadeInWipe(FadeInWipe* pStartWipeFade) 
	{ m_pStartWipeFade = pStartWipeFade; }

	void SetPraiseWinnerPlayerText(PraiseWinnerPlayerText* pPraiseWinnerPlayerText)
	{ m_pPraiseWinnerPlayerText = pPraiseWinnerPlayerText; }

	void SetWinnerPlayerNum(Image2D* pWinnerPlayerNum) 
	{ m_pWinnerPlayerNum = pWinnerPlayerNum; }

	void SetHideImage(Image2D* pHideImage) 
	{ m_pHideImage = pHideImage; }

	void SetEffect_FlowerBlizzard(Effekseer::Handle* pEffect) 
	{ m_pEfkHnd_FlowerBlizzard = pEffect; }

protected:
	SceneResult* m_pSceneResult = nullptr;
	Image2D* m_pBackGround = nullptr;
	ResultWinnerCharacterImage* m_pResultWinnerCharacterImage = nullptr;
	ResultWinnerNumPanel* m_pResultWinnerNumPanel = nullptr;
	PushButtonText* m_pPushButtonTextImage = nullptr;
	FadeInWipe* m_pStartWipeFade = nullptr;
	PraiseWinnerPlayerText* m_pPraiseWinnerPlayerText = nullptr;
	Image2D* m_pWinnerPlayerNum = nullptr;
	Image2D* m_pHideImage = nullptr;
	Effekseer::Handle* m_pEfkHnd_FlowerBlizzard = nullptr;
};
