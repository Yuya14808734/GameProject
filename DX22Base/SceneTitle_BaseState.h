#pragma once
#include "StatePattern.h"
#include "Image2D.h"

class SceneTitle_BaseState : public State
{
public:
	SceneTitle_BaseState() {};
	virtual ~SceneTitle_BaseState() {};
	virtual void Init() override {};
	virtual void Uninit() override {};
	virtual void Update() override {};
	virtual void Draw() override {};

private:

};