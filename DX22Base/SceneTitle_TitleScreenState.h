#pragma once
#include "SceneTitle_BaseState.h"
#include "PushButtonText.h"

class SceneTitle_TitleScreenState : public SceneTitle_BaseState
{
public:
	SceneTitle_TitleScreenState();
	~SceneTitle_TitleScreenState();
	void Update() override;
	void Draw() override;

private:
	Image2D m_TitleName;
	PushButtonText m_PushButtonText;
	Image2D m_TextUnderLine;
};
