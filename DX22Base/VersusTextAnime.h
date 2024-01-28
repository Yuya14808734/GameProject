#pragma once
#include "Image2D.h"

class VersusTextAnime : public Image2D
{
public:
	VersusTextAnime();
	~VersusTextAnime() override;
	void Update() override;

	void StartFadeIn();
	void StartFadeOut();
private:
	void FadeInUpdate();
	void FadeOutUpdate();

private:
	float m_Count = 0.0f;
	bool m_isFadeIn = false;
	bool m_isFadeOut = false;
	float m_LerpTime = 0.0f;
	float m_FadeOutPercent = 0.0f;
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