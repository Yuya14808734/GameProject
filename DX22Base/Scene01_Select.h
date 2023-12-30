#pragma once
#include "Scene.h"
#include "Player_Controller.h"
#include "Select00_Character.h"

class SceneSelect : public CScene
{
public:
	static PlayerController* GetFirstPlayerController();
	static PlayerController* GetSecondPlayerController();
	static SelectCharacter::CHARACTER GetFirstPlayerCharacter();
	static SelectCharacter::CHARACTER GetSecondPlayerCharacter();

private:
	static PlayerController* m_pFirstPlayerController;
	static PlayerController* m_pSecondPlayerController;
	static SelectCharacter::CHARACTER m_FirstPlayerCharacter;
	static SelectCharacter::CHARACTER m_SecondPlayerCharacter;

public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void ControllerConnect();
	void ControllerDisconnect();
	void ControllerRelease();

private:
	SelectCharacter m_SelectFirstCharacter;
	SelectCharacter m_SelectSecondCharacter;
};