#include "Character_DamageUI.h"
#include "Input.h"

//============================================================
//概要
//キャラクターのダメージを表示する数字UI
//============================================================

Character_DamageNumUI::Character_DamageNumUI()
{
	//テクスチャのロード
	SetNumberTexture("Assets/NumberImage/NumberImage02.png", 4, 3);

	m_Number = 0;
	m_pos.x = 64.0f;
	m_pos.y = -5.0f;
	m_size.x = (640.0f / 4.0f) * 0.35f;
	m_size.y = (480.0f / 3.0f) * 0.35f;

	m_UseDistance = true;
	m_NumDistance = m_size.x * 0.55f;
}

Character_DamageNumUI::~Character_DamageNumUI()
{

}

void Character_DamageNumUI::Update()
{

}

void Character_DamageNumUI::PrevDraw()
{
	//ダメージによって色を変える処理
	if (m_Number < 50)
	{
		//50までは黄色
		const DirectX::XMFLOAT4 color_Damage0 = DirectX::XMFLOAT4(255.0f / 255.0f,255.0f / 255.0f ,255.0f/255.0f,1.0f);
		const DirectX::XMFLOAT4 color_Damage50 = DirectX::XMFLOAT4(255.0f / 255.0f,255.0f / 255.0f ,102.0f/255.0f,1.0f);
		float Ratio = static_cast<float>(m_Number) / 50.0f;
		m_color = DirectX::XMFLOAT4(
			color_Damage0.x + (color_Damage50.x - color_Damage0.x) * Ratio,
			color_Damage0.y + (color_Damage50.y - color_Damage0.y) * Ratio,
			color_Damage0.z + (color_Damage50.z - color_Damage0.z) * Ratio,
			1.0f
		);		
	}
	else if(m_Number < 100)
	{
		//100までは赤
		const DirectX::XMFLOAT4 color_Damage50 = DirectX::XMFLOAT4(255.0f / 255.0f, 255.0f / 255.0f, 102.0f / 255.0f, 1.0f);
		const DirectX::XMFLOAT4 color_Damage100 = DirectX::XMFLOAT4(255.0f / 255.0f, 69.0f / 255.0f, 0.0f / 255.0f, 1.0f);
		float Ratio = (static_cast<float>(m_Number) - 50.0f) / (100.0f - 50.0f);
		m_color = DirectX::XMFLOAT4(
			color_Damage50.x + (color_Damage100.x - color_Damage50.x) * Ratio,
			color_Damage50.y + (color_Damage100.y - color_Damage50.y) * Ratio,
			color_Damage50.z + (color_Damage100.z - color_Damage50.z) * Ratio,
			1.0f
		);
	}
	else if(m_Number < 300)
	{
		//100からは赤以外も上げる
		const DirectX::XMFLOAT4 color_Damage100 = DirectX::XMFLOAT4(255.0f / 255.0f, 69.0f / 255.0f, 0.0f / 255.0f, 1.0f);
		const DirectX::XMFLOAT4 color_Damage300 = DirectX::XMFLOAT4(97.0f / 255.0f, 11.0f / 255.0f, 11.0f / 255.0f, 1.0f);
		float Ratio = (static_cast<float>(m_Number) - 100.0f) / (300.0f - 100.0f);
		m_color = DirectX::XMFLOAT4(
			color_Damage100.x + (color_Damage300.x - color_Damage100.x) * Ratio,
			color_Damage100.y + (color_Damage300.y - color_Damage100.y) * Ratio,
			color_Damage100.z + (color_Damage300.z - color_Damage100.z) * Ratio,
			1.0f
		);
	}	
	else
	{
		const DirectX::XMFLOAT4 color_Damage300 = DirectX::XMFLOAT4(97.0f / 255.0f, 11.0f / 255.0f, 11.0f / 255.0f, 1.0f);
		m_color = color_Damage300;
	}
}

//============================================================
//概要
//上の3つをまとめるクラス
//============================================================

Character_DamageUI::Character_DamageUI()
{
	//===<テクスチャの読み込み>====================================
	m_StockIconImage.SetTexture("Assets/UI/StockIconImage.png");
	SetBoardColor(Character_DamageUI::BOARDCOLOR::RED);
	m_StockIconImage.SetTexture("Assets/UI/StockIconImage.png");

	m_BackBoard.m_size = CVector2(288.0f,123.3f);
	m_CharacterIconImage.m_pos = CVector2(-87.0f,5.0f);
	m_CharacterIconImage.m_size = CVector2(106.0f, 106.0f);
	m_StockIconImage.m_size = CVector2(22.4f, 22.4f);
	SetPos(CVector2(100.0f, 100.0f));

	m_StockIconDrawNum = 3;
	m_StockIconBasePos = CVector3(-127.0f, 74.0f, 0.0f);
	m_StockIconDistance = 27.0f;
}

Character_DamageUI::~Character_DamageUI()
{
}

void Character_DamageUI::Update()
{
	m_DamageNum.Update();

	////Image2D*
	//Number2D* 
	//	pChangeImage = &m_DamageNum;
	//CVector2 Size = CVector2(320.0f, 320.0f);

	//if (IsKeyPress(VK_RIGHT))
	//{
	//	m_StockIconBasePos.x += 1.0f;
	//}

	//if (IsKeyPress(VK_LEFT))
	//{
	//	m_StockIconBasePos.x -= 1.0f;
	//}

	//if (IsKeyPress(VK_UP))
	//{
	//	m_StockIconBasePos.y -= 1.0f;
	//}

	//if (IsKeyPress(VK_DOWN))
	//{
	//	m_StockIconBasePos.y += 1.0f;
	//}

	//if (IsKeyPress('I'))
	//{
	//	m_StockIconDistance += 0.1f;
	//}

	//if (IsKeyPress('O'))
	//{
	//	m_StockIconDistance -= 0.1f;
	//}
}

void Character_DamageUI::Draw()
{
	m_BackBoard.Draw();
	m_CharacterIconImage.Draw();
	m_DamageNum.Draw();
	m_StockIconImage.m_pos = m_StockIconBasePos;

	for (int i = 0; i < m_StockIconDrawNum; i++)
	{
		m_StockIconImage.Draw();
		m_StockIconImage.m_pos.x += m_StockIconDistance;
	}
}

Character_DamageNumUI* Character_DamageUI::GetDamageUI()
{
	return &m_DamageNum;
}

void Character_DamageUI::SetPos(const CVector2& pos)
{
	m_DamageNum.m_BasePos =
	m_BackBoard.m_BasePos =
	m_CharacterIconImage.m_BasePos =
	m_StockIconImage.m_BasePos =
	pos;	
}

void Character_DamageUI::SetBoardColor(BOARDCOLOR color)
{
	switch (color)
	{
	case Character_DamageUI::BOARDCOLOR::RED:
	{
		m_BackBoard.SetTexture("Assets/UI/DamageBoard_Red.png");
	}
		break;
	case Character_DamageUI::BOARDCOLOR::BLUE:
	{
		m_BackBoard.SetTexture("Assets/UI/DamageBoard_Blue.png");
	}
		break;
	}
}

void Character_DamageUI::SetCharacterIconImage(const char* pFilePath)
{
	m_CharacterIconImage.SetTexture(pFilePath);
}


