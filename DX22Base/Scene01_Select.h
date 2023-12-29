#pragma once
#include "Scene.h"
#include "Player_Controller.h"

class SceneSelect : public CScene
{
public:
	static PlayerController* GetFirstPlayerController();
	static PlayerController* GetSecondPlayerController();
private:
	static PlayerController* m_pFirstPlayerController;
	static PlayerController* m_pSecondPlayerController;

public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:

};