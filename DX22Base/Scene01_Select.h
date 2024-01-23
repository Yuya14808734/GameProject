#pragma once
#include "Scene.h"
#include "StatePattern.h"
#include "Player_Controller.h"
#include "Select00_Character.h"
#include "Select01_CharacterList.h"
#include "Select02_SlideReadyToFightText.h"
#include "Image2D.h"

class SceneSelect : public CScene
{
public:
	static PlayerController* GetFirstPlayerController();
	static PlayerController* GetSecondPlayerController();
	static SelectCharacterList::CHARACTER GetFirstPlayerCharacter();
	static SelectCharacterList::CHARACTER GetSecondPlayerCharacter();

private:
	static PlayerController* m_pFirstPlayerController;
	static PlayerController* m_pSecondPlayerController;
	static SelectCharacterList::CHARACTER m_FirstPlayerCharacter;
	static SelectCharacterList::CHARACTER m_SecondPlayerCharacter;

public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void ControllerConnect();
	void ControllerDisconnect();
	void ControllerRelease();

private:
	SelectCharacterList m_CharacterList;
	SelectCharacter m_SelectFirstCharacter;
	SelectCharacter m_SelectSecondCharacter;
	Image2D m_CharactersText;
	Image2D m_BackGroundImage;
	SlidReadyToFightText m_ReadyToFightTextImage;
};