#include "FadeOut00_ColorFade.h"
#include "Main.h"

FadeOutColorFade::FadeOutColorFade()
{
	//=====<�J�E���g�̏�����>=====
	m_CountTime = 0.0f;

	//=====<�e�N�X�`����ǂݍ���>=====
	SetTexture("Assets/Texture/WhiteTexture.png");

	m_color.w = 0.0f;
	m_FadeTime = 1.0f;
}

FadeOutColorFade::~FadeOutColorFade()
{
}

void FadeOutColorFade::FadeUpdate()
{
	m_CountTime += 1.0f / 60.0f;

	if (m_CountTime > m_FadeTime)
	{
		m_FadeEnd = true;
		m_CountTime = m_FadeTime;
	}

	m_color.w = m_CountTime / m_FadeTime;

}


void FadeOutColorFade::SetFadeTime(float time)
{
	m_FadeTime = time;
}