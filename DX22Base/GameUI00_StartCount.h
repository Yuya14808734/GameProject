#pragma once
#include "Image2D.h"
#include "Number2D.h"

class GameStartCountUI
{
public:
	GameStartCountUI();
	~GameStartCountUI();
	void Update();
	void Draw();
	void SetNumDraw(int Num);
	void SetGoDraw(bool draw);
private:
	Number2D m_CountImage;
	Number2D m_CountShadowImage;
	Image2D m_GoTextImage;
	Image2D m_GoTextShadowImage;
	CVector2 m_StartSize;
	CVector2 m_AddSize;
	bool m_IsGoDraw = false;

};