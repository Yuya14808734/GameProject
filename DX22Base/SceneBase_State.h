#pragma once
#include "StatePattern.h"

class Scene_State : public State
{
	Scene_State() {};
	virtual ~Scene_State() {};
	virtual void Update() override {};
	virtual void Draw() {};
};