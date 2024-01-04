#pragma once
#include "Main.h"
#include "Image2D.h"

class SlidReadyToFightText
{
	static constexpr float m_LerpTime = 0.06f;

public:
	SlidReadyToFightText();
	~SlidReadyToFightText();
	void Update();
	void Draw();
	void StartSlide();

private:
	Image2D m_BackGround;
	Image2D m_SlidImage01;
	Image2D m_SlidImage02;
	Image2D m_ReadyText;
	float m_LerpCount = 0.0f;
	
};