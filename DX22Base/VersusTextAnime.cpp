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
	if(!m_isStartLerp)
	{
		return;
	}

	m_Count += 1.0f / 60.0f;

	float Percent = m_Count / m_LerpTime;

	if (Percent > 1.0f)
	{
		Percent = 1.0f;
		m_isStartLerp = false;
	}

	//�T�C�Y�����񂾂�ς��Ă���
	m_size = (m_StartSize * (1.0f - Percent)) + (m_EndSize * Percent);

}

void VersusTextAnime::StartLerp()
{
	m_Count = 0.0f;
	m_isStartLerp = true;
}

void VersusTextAnime::PrevDraw()
{
}
