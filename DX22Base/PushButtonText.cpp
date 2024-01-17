#include "PushButtonText.h"
#include "Main.h"

PushAButtonText::PushAButtonText()
{
	SetTexture("Assets/UI/PRESSABUTTON_Text.png");

	CVector2 WindowSize =
		CVector2(static_cast<float>(GetAppWidth()), static_cast<float>(GetAppHeight()));

	float SizeChangeScalePercent = 50.0f / 71.0f;
	SetPos(CVector2(WindowSize.x * 0.5f, WindowSize.y * 0.75f));
	SetSize(CVector2(640.0f, 71.0f) * SizeChangeScalePercent);
}

PushAButtonText::~PushAButtonText()
{

}

PushEnterButtonText::PushEnterButtonText()
{
	SetTexture("Assets/UI/PRESSENTERBUTTON_Text.png");

	CVector2 WindowSize =
		CVector2(static_cast<float>(GetAppWidth()), static_cast<float>(GetAppHeight()));

	float SizeChangeScalePercent = 50.0f / 53.0f;
	SetPos(CVector2(WindowSize.x * 0.5f, WindowSize.y * 0.75f));
	SetSize(CVector2(640.0f, 53.0f) * SizeChangeScalePercent);
}

PushEnterButtonText::~PushEnterButtonText()
{

}

PushButtonText::PushButtonText()
{
	m_Time = 0.0f;
}

PushButtonText::~PushButtonText()
{

}

void PushButtonText::Update()
{
	m_Time = m_Time + (1.0f / 60.0f);

	//タイムが大きくなり過ぎないようにする
	while(m_Time > m_FadeInOutTime * 2.0f)
	{
		m_Time = 
			m_Time - (m_FadeInOutTime * 2.0f);
	}

	//=====<sinウェーブ>=====
	float sinValue = sinf((m_Time / m_FadeInOutTime) * DirectX::XM_PI);

	//=====<アルファ値をいじる>=====
	m_PushAButtonText.m_color.w = sinValue > 0.0f ? 
		sinValue: 0.0f;

	m_PushEnterButtonText.m_color.w = sinValue < 0.0f ?
		-sinValue : 0.0f;
}

void PushButtonText::Draw()
{
	m_PushAButtonText.Draw();
	m_PushEnterButtonText.Draw();
}
