#pragma once
#include "Player_Controller.h"
#include <vector>

class SelectController
{
public:
	enum class CONTROLLER : int
	{
		KEYBORD = 0,
		PAD,
		MAX
	};

public:
	SelectController();
	~SelectController();
	void Update();
	void Draw();

private:
	PlayerController::PLAYCONTROLLERTYPE m_NowSelect = PlayerController::PLAYCONTROLLERTYPE::MAX;
	PlayerController* m_pPlayerController = nullptr;
};