#include "Select02_SlideReadyToFightText.h"
#include "Main.h"

SlidReadyToFightText::SlidReadyToFightText()
{
	CVector2 WindowSize(static_cast<float>(GetAppWidth()), static_cast<float>(GetAppHeight()));

	m_SlidImage01.SetTexture("Assets/UI/ReadyToFightSlidImage01.png");
	m_SlidImage01.m_pos = CVector3(WindowSize.x * 0.5f, WindowSize.y * 0.5f,0.0f);
	m_SlidImage01.m_size = CVector2(WindowSize.x, 402.0f);

	m_SlidImage02.SetTexture("Assets/UI/ReadyToFightSlidImage02.png");
	m_SlidImage02.m_pos = m_SlidImage01.m_pos;
	m_SlidImage02.m_size = m_SlidImage01.m_size;
	m_SlidImage02.m_pos.x -= (m_SlidImage01.m_size.x + m_SlidImage02.m_size.x) * 0.5f;

	m_BackGround.SetTexture("Assets/UI/ReadyToFightBackGroundImage.png");
	m_BackGround.m_pos = CVector3(WindowSize.x * 0.5f, WindowSize.y * 0.5f, 0.0f);
	m_BackGround.m_size = WindowSize;

	m_ReadyText.SetTexture("Assets/UI/ReadyToFightImage.png");
	m_ReadyText.m_pos = CVector3(WindowSize.x * 0.5f, WindowSize.y * 0.5f, 0.0f);
	m_ReadyText.m_size = CVector2(1080.0f, 393.0f);
}

SlidReadyToFightText::~SlidReadyToFightText()
{
}

void SlidReadyToFightText::Update()
{
	//左にいるやつが0,右にいるやつが1になる
	Image2D* pSlidImages[2] = { nullptr,nullptr };

	if (m_SlidImage01.m_pos.x < m_SlidImage02.m_pos.x)
	{
		pSlidImages[0] = &m_SlidImage01;
		pSlidImages[1] = &m_SlidImage02;
	}
	else
	{
		pSlidImages[0] = &m_SlidImage02;
		pSlidImages[1] = &m_SlidImage01;
	}

	pSlidImages[0]->m_pos.x += 20.0f;
	pSlidImages[1]->m_pos.x = pSlidImages[0]->m_pos.x + ((pSlidImages[0]->m_size.x + pSlidImages[1]->m_size.x) * 0.5f);

	//画面外に完全に出たら左に持ってくる
	if (pSlidImages[1]->m_pos.x > static_cast<float>(GetAppWidth()) + (pSlidImages[1]->m_size.x * 0.5f))
	{
		pSlidImages[1]->m_pos.x = pSlidImages[0]->m_pos.x - ((m_SlidImage01.m_size.x + m_SlidImage02.m_size.x) * 0.5f);
	}

}

void SlidReadyToFightText::Draw()
{
	m_BackGround.Draw();

	//後ろの線を描画
	m_SlidImage01.Draw();
	m_SlidImage02.Draw();

	m_ReadyText.Draw();
}

void SlidReadyToFightText::StartSlide()
{
	m_LerpCount = 0.0f;
}
