#include "FadeIn01_ColorFade.h"
#include "Main.h"

FadeInColorFade::FadeInColorFade()
{
	//=====<�E�B���h�E�T�C�Y>=====
	CVector2 WindowSize = CVector2(
		static_cast<float>(GetAppWidth()),
		static_cast<float>(GetAppHeight())
	);

	m_size = WindowSize;
	m_pos = WindowSize * 0.5f;

	//=====<�J�E���g�̏�����>=====
	m_CountTime = 0.0f;

	//=====<�e�N�X�`����ǂݍ���>=====
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
