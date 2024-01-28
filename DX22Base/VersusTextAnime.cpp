#include "VersusTextAnime.h"

VersusTextAnime::VersusTextAnime()
{
	SetTexture("Assets/UI/VersusText.png");
}

VersusTextAnime::~VersusTextAnime()
{
}

void VersusTextAnime::Update()
{	
	FadeInUpdate();
	FadeOutUpdate();
}

void VersusTextAnime::StartFadeIn()
{
	m_Count = 0.0f;
	m_isFadeIn = true;
}

void VersusTextAnime::StartFadeOut()
{
	m_Count = 0.0f;
	m_isFadeIn = false;
	m_isFadeOut = true;
}

void VersusTextAnime::FadeInUpdate()
{
	if (!m_isFadeIn)
	{
		return;
	}

	m_Count += 1.0f / 60.0f;

	float Percent = m_Count / m_LerpTime;
	float NormalPercent = Percent > 1.0f ? 1.0f : Percent;
	float EasePercent = 1.0f - powf(1.0f - NormalPercent, 3);
	m_FadeOutPercent = EasePercent = EasePercent + (Percent * 0.05f);

	//サイズをだんだん変えていく
	m_size = (m_StartSize * (1.0f - EasePercent)) + (m_EndSize * EasePercent);
	
	m_color.w = Percent;
}

void VersusTextAnime::FadeOutUpdate()
{
	if (!m_isFadeOut)
	{
		return;
	}

	m_Count += 1.0f / 60.0f;

	float Percent = m_Count / m_LerpTime;

	if (Percent > 1.0f)
	{
		Percent = 1.0f;
		m_isFadeOut = false;
	}

	float EasePercent = 1.0f - powf(1.0f - Percent, 3);
	EasePercent = m_FadeOutPercent * (1.0f - EasePercent);

	//サイズをだんだん変えていく
	m_size = (m_StartSize * (1.0f - EasePercent) + (m_EndSize * EasePercent));

	m_color.w = 1.0f - Percent;
}
