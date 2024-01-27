#include "FadeBase.h"
#include "Main.h"
#include "OffScreenRenderingClass.h"

FadeBase::FadeBase()
	:m_FadeEnd(false)
{
	//=====<ウィンドウサイズ>=====
	CVector2 WindowSize = CVector2(
		static_cast<float>(GetAppWidth()),
		static_cast<float>(GetAppHeight())
	);

	m_pos = WindowSize * 0.5f;
	m_size = WindowSize;

	//=====<描画しない設定>=====
	m_IsVisible = false;
}

FadeBase::~FadeBase()
{
}

void FadeBase::Update()
{
	if (!m_FadeStart)
	{
		m_IsVisible = false;
		return;
	}

	if (m_FadeStop)
	{
		return;
	}

	FadeUpdate();

	if (m_FadeEnd)
	{
		m_FadeStart = false;
	}
}

void FadeBase::FadeStartInit()
{
}

void FadeBase::FadeUpdate()
{
}

void FadeBase::PrevDraw()
{
}
