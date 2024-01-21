#include "GameUI02_StockCount.h"
#include "Main.h"

StockCountUI::StockCountUI()
	:m_TimeCount(0.0f)
{
	m_FirstCharacterStockCountUI.SetNumberTexture("Assets/NumberImage/NumberImage03.png", 4, 3);
	m_SecondCharacterStockCountUI.SetNumberTexture("Assets/NumberImage/NumberImage03.png", 4, 3);
	m_FirstCharacterStockCountUI.m_size = 
	m_SecondCharacterStockCountUI.m_size =
		CVector2(640.0f / 4.0f, 480.0f / 3.0f) * 1.5f;

	m_LineUI.SetTexture("Assets/UI/LineImage.png");
	m_LineUI.m_BasePos = CVector2(
		static_cast<float>(GetAppWidth()) * 0.5f,
		static_cast<float>(GetAppHeight()) * 0.5f
	);
	m_LineUI.m_size = CVector2(150.0f, 29.0f) * 1.8f;
	
	m_LineUI.m_IsVisible =
		m_FirstCharacterStockCountUI.m_IsVisible =
		m_SecondCharacterStockCountUI.m_IsVisible =
		false;
}

StockCountUI::~StockCountUI()
{

}

void StockCountUI::Update()
{
	//ˆÚ“®‚µ‚Ä‚¢‚È‚©‚Á‚½‚ç“ü‚ç‚È‚¢,•`‰æ‚µ‚È‚¢
	if (!m_isLerp)
	{
		m_LineUI.m_IsVisible =
			m_FirstCharacterStockCountUI.m_IsVisible =
			m_SecondCharacterStockCountUI.m_IsVisible =
			false;
		return;
	}

	m_LineUI.m_IsVisible =
		m_FirstCharacterStockCountUI.m_IsVisible =
		m_SecondCharacterStockCountUI.m_IsVisible =
		true;

	m_TimeCount = m_TimeCount + (1.0f / 60.0f);

	//ƒXƒgƒbƒN•\Ž¦‚ÌˆÊ’u‚ðŒˆ‚ß‚é‚Ì‚ÉŽg‚¤
	float LerpPercent = 0.0f;

	if (m_TimeCount			< m_LerpInTime)
	{
		//“ü‚é(0`1)
		LerpPercent = m_TimeCount / m_LerpInTime;
	}
	else if(m_TimeCount		< m_LerpInTime + m_LerpStopTime)
	{
		//Ž~‚Ü‚é
		LerpPercent = 1.0f;
	}
	else if(m_TimeCount		< m_LerpInTime + m_LerpStopTime + m_LerpOutTime)
	{
		//o‚é(1`0)
		LerpPercent = 1.0f - 
			((m_TimeCount - m_LerpInTime - m_LerpStopTime) / m_LerpOutTime);
	}
	else
	{
		m_TimeCount = m_LerpInTime + m_LerpStopTime + m_LerpOutTime; 
		LerpPercent = 0.0f;
		m_isLerp = false;
	}

	m_FirstCharacterStockCountUI.LerpPos(
		m_FirstCharacterStockNum_OutPos,
		m_FirstCharacterStockNum_InPos,
		LerpPercent
	);

	m_SecondCharacterStockCountUI.LerpPos(
		m_SecondCharacterStockNum_OutPos,
		m_SecondCharacterStockNum_InPos,
		LerpPercent
	);

	m_LineUI.m_color.w =
		m_FirstCharacterStockCountUI.m_color.w =
		m_SecondCharacterStockCountUI.m_color.w = LerpPercent;

}

void StockCountUI::Draw()
{
	m_LineUI.Draw();
	m_FirstCharacterStockCountUI.Draw();
	m_SecondCharacterStockCountUI.Draw();
}

void StockCountUI::LerpStart(int FirstCharacterStockNum, int SecondCharacterStockNum)
{
	m_FirstCharacterStockCountUI.SetNumber(FirstCharacterStockNum);
	m_SecondCharacterStockCountUI.SetNumber(SecondCharacterStockNum);
	m_isLerp = true;
	m_TimeCount = 0.0f;
}