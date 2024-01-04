#include "GameUI00_StartCount.h"
#include "Main.h"

GameStartCountUI::GameStartCountUI()
{
	m_CountImage.SetNumberTexture("Assets/NumberImage/NumberImage02.png",4,3);
	m_CountShadowImage.SetNumberTexture("Assets/NumberImage/NumberImageShadow02.png",4,3);
	m_GoTextImage.m_pos = m_GoTextShadowImage.m_pos = m_CountImage.m_pos = m_CountShadowImage.m_pos = CVector3(
			static_cast<float>(GetAppWidth()) * 0.5f
			, static_cast<float>(GetAppHeight()) * 0.4f
			, 0.0f);
	m_CountImage.m_size = m_CountShadowImage.m_size = m_StartSize =
		CVector2(100.0f,100.0f);
	m_AddSize = CVector2(1.0f, 1.0f);

	m_GoTextImage.SetTexture("Assets/NumberImage/GoTextImage02.png");
	m_GoTextShadowImage.SetTexture("Assets/NumberImage/GoTextImageShadow02.png");
	m_GoTextImage.m_size = m_GoTextShadowImage.m_size = CVector2(640.0f, 386.0f);
}

GameStartCountUI::~GameStartCountUI()
{

}

void GameStartCountUI::Update()
{
	m_CountImage.m_size += m_AddSize;
	m_CountShadowImage.m_size = m_CountImage.m_size;
}

void GameStartCountUI::Draw()
{
	if (m_IsGoDraw)
	{
		m_GoTextShadowImage.Draw();
		m_GoTextImage.Draw();
	}
	else
	{
		m_CountShadowImage.m_color = DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
		m_CountShadowImage.Draw();
		//m_CountImage.Draw();
	}
}

void GameStartCountUI::SetNumDraw(int Num)
{
	m_CountImage.SetNumber(Num);
	m_CountShadowImage.SetNumber(Num);
	m_CountImage.m_size = m_StartSize;
}

void GameStartCountUI::SetGoDraw(bool draw)
{
	m_IsGoDraw = draw;
}
