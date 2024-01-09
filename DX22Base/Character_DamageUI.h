#pragma once
#include "Image2D.h"
#include "Number2D.h"

class Character_DamageNumUI : public Number2D
{
public:
	Character_DamageNumUI();
	~Character_DamageNumUI() override;
	void Update() override;
	void PrevDraw() override;

private:
	float m_drawDamage = 0.0f;

};

class Character_DamageUI
{
public:
	enum class BOARDCOLOR : int
	{
		RED = 0,
		BLUE,
		MAX,
	};

public:
	Character_DamageUI();
	~Character_DamageUI();
	void Update();
	void Draw();
	Character_DamageNumUI* GetDamageUI();
	void SetPos(const CVector2& pos);
	void SetBoardColor(BOARDCOLOR color);
	void SetCharacterIconImage(const char* pFilePath);
	void SetStockNum(int num);

private:
	CVector3 m_StockIconBasePos;
	float m_StockIconDistance = 0.0f;
	int m_StockIconDrawNum = 0;
	Character_DamageNumUI m_DamageNum;
	Image2D m_BackBoard;
	Image2D m_CharacterIconImage;
	Image2D m_StockIconImage;
};