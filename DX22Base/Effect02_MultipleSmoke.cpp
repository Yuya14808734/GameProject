#include "Effect02_MultipleSmoke.h"
#include "ShaderManager.h"

MultipleSmoke::MultipleSmoke()
{
	const char* pFilePath[4]
	{
		"Assets/Texture/Cloud00.png",
		"Assets/Texture/Cloud01.png",
		"Assets/Texture/Cloud02.png",
		"Assets/Texture/Cloud03.png",
	};

	m_pDissovleShader = ShaderManager::CreatePixelShader("DissolveSprite", CreateShaderPath("DissolveSpritePS"));
	
	for (int i = 0; i < 4; i++)
	{
		m_SmokeImages[i].SetTexture(pFilePath[i]);
		m_SmokeImages[i].SetPixelShader(m_pDissovleShader);
	}

	LoadTextureFromFile("Assets/Texture/dissolve.png", &m_pDissolveTexture);

	m_Buffer_DissolveParameter.Create(sizeof(float) * 4.0f);

	m_isUpdate = true;

	m_EffectAddEnd = false;
}

MultipleSmoke::~MultipleSmoke()
{
	m_SingleSmokeParams.clear();

	m_pDissolveTexture->Release();

}

void MultipleSmoke::Update()
{
	if (!m_isUpdate)
	{
		return;
	}

	//各エフェクトの値の更新
	for (std::vector<SingleSmokeParameter>::iterator it = m_SingleSmokeParams.begin()
		;it != m_SingleSmokeParams.end();)
	{
		(*it).time = (*it).time + (1.0f / 60.0f);

		if ((*it).time > m_EndTime)
		{
			it = m_SingleSmokeParams.erase(it);
			continue;
		}

		(*it).velocity *= 0.94f;
		(*it).pos += (*it).velocity;
		(*it).size *= 1.01f;

		it++;
	}

	//もうエフェクトが足されない場合
	if (m_EffectAddEnd)
	{
		if (m_SingleSmokeParams.size() == 0)
		{
			m_isDestroy = true;
		}
	}
}

void MultipleSmoke::Draw()
{
	//描画を行う
	//テクスチャを送る
	SetTexturePS(m_pDissolveTexture, 1);

	for (const SingleSmokeParameter& copy : m_SingleSmokeParams)
	{
		//パラメータによって画像の位置を変える
		m_SmokeImages[copy.texNum].m_BasePos = copy.basePos;
		m_SmokeImages[copy.texNum].m_pos = copy.pos;
		m_SmokeImages[copy.texNum].SetSize(copy.size);
		m_DissolveParameter[0] = copy.time / m_EndTime;
		m_Buffer_DissolveParameter.Write(m_DissolveParameter);
		m_Buffer_DissolveParameter.BindPS(0);

		m_SmokeImages[copy.texNum].Draw();
	}
}

void MultipleSmoke::PausedEffect(bool paused)
{
	m_isUpdate = !paused;
}

void MultipleSmoke::AddPlayEffect(const CVector3& pos, const CVector3& velocity)
{
	SingleSmokeParameter temp;

	temp.texNum = rand() % 4;
	temp.time = 0.0f;
	temp.basePos = pos;
	temp.pos = CVector3(
		static_cast<float>(rand() % 200 + 1) / 100.0f - 1.0f,
		static_cast<float>(rand() % 200 + 1) / 100.0f - 1.0f,
		static_cast<float>(rand() % 200 + 1) / 100.0f - 1.0f
	);
	temp.size = CVector2(256.0f, 256.0f) * 0.005f;
	temp.velocity = velocity;

	m_SingleSmokeParams.push_back(temp);
}

void MultipleSmoke::SetSingleSmokeEndTime(float time)
{
	m_EndTime = time;
}

void MultipleSmoke::SetEffectAddEnd(bool end)
{
	m_EffectAddEnd = end;
}
