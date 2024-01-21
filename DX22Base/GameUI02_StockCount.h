#pragma once
#include "Image2D.h"
#include "Number2D.h"

class CharacterStockCountUI;
class StockCountUI;

class CharacterStockCountUI : public Number2D
{
public:
	CharacterStockCountUI() {};
	~CharacterStockCountUI() {};
	void LerpPos(const CVector3& OutPos, const CVector3& InPos, float Lerp)
	{
		m_pos = (OutPos * (1.0f - Lerp)) + (InPos * (Lerp));
	}
};

class StockCountUI
{
private:
	const float		m_LerpInTime						= 0.1f;
	const float		m_LerpStopTime						= 1.0f;
	const float		m_LerpOutTime						= 0.1f;

	const CVector3	m_FirstCharacterStockNum_OutPos		= CVector3(100.0f, 360.0f, 0.0f);
	const CVector3	m_FirstCharacterStockNum_InPos		= CVector3(300.0f, 360.0f, 0.0f);
	const CVector3	m_SecondCharacterStockNum_OutPos	= CVector3(1180.0f, 360.0f, 0.0f);
	const CVector3	m_SecondCharacterStockNum_InPos		= CVector3(980.0f, 360.0f, 0.0f);

public:
	StockCountUI();
	~StockCountUI();
	void Update();
	void Draw();
	void LerpStart(int FirstCharacterStockNum, int SecondCharacterStockNum);

private:
	Image2D			m_LineUI;										//真ん中のライン
	CharacterStockCountUI m_FirstCharacterStockCountUI;				//一人目のキャラクターのストック数
	CharacterStockCountUI m_SecondCharacterStockCountUI;			//二人目のキャラクターのストック数
	float			m_TimeCount							= 0.0f;		//時間のカウント
	bool			m_isLerp							= false;
};