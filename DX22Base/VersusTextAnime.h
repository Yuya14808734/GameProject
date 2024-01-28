#pragma once
#include "Image2D.h"

class VersusTextAnime : public Image2D
{
public:
	VersusTextAnime();
	~VersusTextAnime() override;
	void Update() override;

	void StartLerp();
private:
	void PrevDraw() override;

private:
	float m_Count = 0.0f;
	bool m_isStartLerp = false;
	float m_LerpTime = 0.0f;
	CVector2 m_StartSize;
	CVector2 m_EndSize;

public:
	void SetLerpTime(float Time) 
	{ m_LerpTime = Time; }

	void SetLerpSize(const CVector2& startSize, const CVector2& endSize) {
		m_StartSize = startSize;
		m_EndSize = endSize;
	}

};