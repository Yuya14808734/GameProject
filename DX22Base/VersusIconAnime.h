#pragma once
#include "Image2D.h"

class VersusIconAnime : public Image2D
{
private:
	const CVector2 ImageSize = CVector2(400.0f, 285.0f);

public:
	VersusIconAnime();
	~VersusIconAnime() override;
	void Update() override;

	void StartFadeIn();
private:
	void FadeInUpdate();

private:
	float m_Count = 0.0f;
	bool m_isFadeIn = false;
	float m_LerpTime = 0.0f;
	CVector2 m_StartSize;
	CVector2 m_EndSize;

public:
	void SetLerpTime(float Time)
	{
		m_LerpTime = Time;
	}

	void SetLerpSize(float StartScale,float EndScale) {
		m_StartSize = ImageSize * StartScale;
		m_EndSize = ImageSize * EndScale;
	}

};
