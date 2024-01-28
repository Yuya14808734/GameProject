#include "VersusIconAnime.h"
#include "Main.h"

VersusIconAnime::VersusIconAnime()
	:m_Count(0.0f),
	m_isFadeIn(false),
	m_LerpTime(1.0f)
{
	SetTexture("Assets/UI/VS.png");
	m_pos = CVector2(
	static_cast<float>(GetAppWidth()) * 0.5f,
	static_cast<float>(GetAppHeight()) * 0.5f
	);

	m_IsVisible = false;
}

VersusIconAnime::~VersusIconAnime()
{
}

void VersusIconAnime::Update()
{
	FadeInUpdate();
}

void VersusIconAnime::StartFadeIn()
{
	m_Count = 0.0f;
	m_isFadeIn = true;
	m_IsVisible = true;
}

void VersusIconAnime::FadeInUpdate()
{
	if (!m_isFadeIn)
	{
		return;
	}

	m_Count += 1.0f / 60.0f;

	if (m_Count > m_LerpTime)
	{
		m_isFadeIn = false;
	}

	float Percent = m_Count / m_LerpTime;
	float EasePercent =
		Percent < 0.5f ? 
		16.0f * powf(Percent, 5.0f) : 
		1.0f - powf(-2.0f * Percent + 2.0f, 5.0f) / 2.0f;

	m_size = (m_StartSize * (1.0f - EasePercent)) + (m_EndSize * EasePercent);

	m_color.w = EasePercent;
}
