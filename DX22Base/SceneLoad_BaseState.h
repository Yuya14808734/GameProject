#pragma once
#include "StatePattern.h"
#include "Scene04_Load.h"

class SceneLoad_BaseState : public State
{
public:
	SceneLoad_BaseState() {};
	virtual ~SceneLoad_BaseState() {};
	virtual void Init() override {};
	virtual void Uninit() override {};
	virtual void Update() override {};
	virtual void Draw() override {};

protected:
	SceneLoad* m_pScene = nullptr;
	Image2D* m_pBackGround = nullptr;
	std::vector<VersusCharacterPanelMove*>* m_pCharacterMovePanels = nullptr;
	std::vector<VersusCharacterImageMove*>* m_pCharacterImages = nullptr;
	VersusTextAnime* m_pVersusTextAnime = nullptr;

public:
	void SetScene(SceneLoad* pScene) 
	{ m_pScene = pScene; }

	void SetBackGround(Image2D* pBackGround) 
	{ m_pBackGround = pBackGround; }

	void SetCharacterMovePanels(std::vector<VersusCharacterPanelMove*>* pCharacterMovePanels) 
	{ m_pCharacterMovePanels = pCharacterMovePanels; }

	void SetCharacterImages(std::vector<VersusCharacterImageMove*>* pCharacterImages) 
	{ m_pCharacterImages = pCharacterImages; }

	void SetVersusTextAnime(VersusTextAnime* pVersusTextAnime) 
	{ m_pVersusTextAnime = pVersusTextAnime; }
};
