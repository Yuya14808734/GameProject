#include "Effect01_SingleSmoke.h"
#include "ShaderManager.h"

SingleSmoke::SingleSmoke()
{
	int RandomNum = rand() % 4;

	const char* pFilePath[4]
	{
		"Assets/Texture/Cloud00.png",
		"Assets/Texture/Cloud01.png",
		"Assets/Texture/Cloud02.png",
		"Assets/Texture/Cloud03.png",
	};

	CVector3 RandPos = CVector3(
		static_cast<float>(rand() % 200) / 100.0f - 1.0f,
		static_cast<float>(rand() % 200) / 100.0f - 1.0f,
		static_cast<float>(rand() % 200) / 100.0f - 1.0f
	);

	m_SmokeImage.SetTexture(pFilePath[RandomNum]);
	m_SmokeImage.SetSize(CVector2(256.0f, 256.0f) * 0.01f);
	m_SmokeImage.SetPos(RandPos);
	m_SmokeImage.SetPixelShader(
		ShaderManager::CreatePixelShader("DissolveSprite", CreateShaderPath("DissolveSpritePS"))
	);
	SetPos(CVector3::GetZero());
	SetTime(1.0f);
	m_isUpdate = true;
}

SingleSmoke::~SingleSmoke()
{
}

void SingleSmoke::Update()
{
	if(!m_isUpdate)
	{
		return;
	}

	m_Time = m_Time + (1.0f / 60.0f);

	if (m_Time > m_EndTime)
	{
		m_isDestroy = true;
	}

	m_SmokeImage.m_pos *= 1.01f;
}

void SingleSmoke::Draw()
{
	m_SmokeImage.Draw();
}

void SingleSmoke::PausedEffect(bool paused)
{
	m_isUpdate = !paused;
}

void SingleSmoke::SetPos(const CVector3& pos)
{
	m_SmokeImage.m_BasePos = pos;
}

void SingleSmoke::SetTime(float EndTime)
{
	m_EndTime = EndTime;
}

void SingleSmoke::PlayEffect(const CVector3& pos, float endTime)
{
	SetPos(pos);
	SetTime(endTime);
}
