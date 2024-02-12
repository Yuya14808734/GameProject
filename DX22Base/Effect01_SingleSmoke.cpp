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

	CVector3 randPos = CVector3(
		static_cast<float>(rand() % 200 + 1) / 100.0f - 1.0f,
		static_cast<float>(rand() % 200 + 1) / 100.0f - 1.0f,
		static_cast<float>(rand() % 200 + 1) / 100.0f - 1.0f
	);

	m_SmokeImage.SetTexture(pFilePath[RandomNum]);
	m_SmokeImage.SetPos(randPos);
	m_SmokeImage.SetSize(CVector2(256.0f, 256.0f) * 0.005f);
	m_SmokeImage.SetPixelShader(
		ShaderManager::CreatePixelShader("DissolveSprite", CreateShaderPath("DissolveSpritePS"))
	);
	SetPos(CVector3::GetZero());
	SetTime(1.0f);
	m_isUpdate = true;

	LoadTextureFromFile("Assets/Texture/dissolve.png", &m_pDissolveTexture);

	m_Buffer_DissolveParameter.Create(sizeof(float) * 4.0f);
}

SingleSmoke::~SingleSmoke()
{
	m_pDissolveTexture->Release();
	m_pDissolveTexture = nullptr;
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

	m_Velocity *= 0.9f;

	m_SmokeImage.m_pos += m_Velocity;
	m_SmokeImage.m_size *= 1.01f;
}

void SingleSmoke::Draw()
{
	//テクスチャを送る
	SetTexturePS(m_pDissolveTexture,1);

	m_DissolveParameter[0] = m_Time / m_EndTime;
	m_Buffer_DissolveParameter.Write(m_DissolveParameter);
	m_Buffer_DissolveParameter.BindPS(0);

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

void SingleSmoke::SetVelocity(const CVector3& velocity)
{
	m_Velocity = velocity;
}

void SingleSmoke::PlayEffect(const CVector3& pos, float endTime, const CVector3& velocity)
{
	SetPos(pos);
	SetTime(endTime);
	SetVelocity(velocity);
}
