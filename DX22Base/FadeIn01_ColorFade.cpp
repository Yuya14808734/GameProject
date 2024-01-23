#include "FadeIn01_ColorFade.h"
#include "Main.h"

FadeInColorFade::FadeInColorFade()
{
	//=====<ウィンドウサイズ>=====
	CVector2 WindowSize = CVector2(
		static_cast<float>(GetAppWidth()),
		static_cast<float>(GetAppHeight())
	);

	m_size = WindowSize;
	m_pos = WindowSize * 0.5f;

	//=====<カウントの初期化>=====
	m_CountTime = 0.0f;

	//=====<テクスチャを読み込む>=====
	SetTexture("Assets/Texture/WhiteTexture.png");

	
	m_FadeTime = 1.0f;
}

FadeInColorFade::~FadeInColorFade()
{
}

void FadeInColorFade::FadeUpdate()
{
	m_CountTime += 1.0f / 60.0f;

	if (m_CountTime > m_FadeTime)
	{
		m_FadeEnd = true;
		m_CountTime = m_FadeTime;
	}

	m_color.w = m_CountTime / m_FadeTime;

}


void FadeInColorFade::SetFadeTime(float time)
{
	m_FadeTime = time;
}
