#include "Effect01_SingleSmoke.h"

SingleSmoke::SingleSmoke()
{
	m_SmokeImage.SetTexture("Assets/Texture/Cloud00.png");
	m_SmokeImage.SetSize(CVector2(256.0f, 256.0f));
	SetPos(CVector3::GetZero());
	SetTime(1.0f);
}

SingleSmoke::~SingleSmoke()
{
}

void SingleSmoke::Update()
{
	m_Time += 1.0f / 60.0f;

	if (m_Time > m_EndTime)
	{
		m_isDestroy = true;
	}
}

void SingleSmoke::Draw()
{
	m_SmokeImage.Draw();
}

void SingleSmoke::PausedEffect(bool paused)
{
}

void SingleSmoke::SetPos(const CVector3& pos)
{
	m_SmokeImage.m_BasePos = pos;
}

void SingleSmoke::SetTime(float EndTime)
{
	m_EndTime = EndTime;
}
