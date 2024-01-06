#include "Character_DamageUI.h"

//============================================================
//概要
//キャラクターのダメージを表示するUI
//============================================================

Character_DamageNumUI::Character_DamageNumUI()
{
	//テクスチャのロード
	SetNumberTexture("Assets/NumberImage/WhiteNumber.png", 13, 1);

	m_size.x = 16.0f * 1.5f;
	m_size.y = 32.0f * 1.5f;
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
//キャラクターのアイコン
//============================================================

Character_CharacterIconUI::Character_CharacterIconUI()
{
	m_size.x = m_size.y = 100.0f;
}

Character_CharacterIconUI::~Character_CharacterIconUI()
{

}

void Character_CharacterIconUI::Update()
{

}

void Character_CharacterIconUI::PrevDraw()
{

}

void Character_CharacterIconUI::SetIconTexture(const char* filePath)
{
	SetTexture(filePath);
}

//============================================================
//概要
//%を描画するクラス
//============================================================

PercentUI::PercentUI()
{
	//テクスチャのロード
	SetTexture("Assets/NumberImage/PercentImage.png");

	m_size.x = 147.0f * 0.5f;
	m_size.y = 150.0f * 0.5f;
}

PercentUI::~PercentUI()
{
}

void PercentUI::Update()
{
}

void PercentUI::PrevDraw()
{
}

//============================================================
//概要
//上の3つをまとめるクラス
//============================================================

Character_DamageUI::Character_DamageUI()
{
	SetScale(1.0f);
	SetPos(CVector2(100.0f, 100.0f));
}

Character_DamageUI::~Character_DamageUI()
{
}

void Character_DamageUI::Update()
{
	m_IconUI.Update();
	m_DamageUI.Update();
}

void Character_DamageUI::Draw()
{
	m_IconUI.Draw();
	m_DamageUI.Draw();
	m_PercentUI.Draw();
}

Character_DamageNumUI* Character_DamageUI::GetDamageUI()
{
	return &m_DamageUI;
}

Character_CharacterIconUI* Character_DamageUI::GetCharacterIconUI()
{
	return &m_IconUI;
}

PercentUI* Character_DamageUI::GetPercentUI()
{
	return &m_PercentUI;
}

void Character_DamageUI::SetPos(const CVector2& pos)
{
	m_pos = pos;
	m_IconUI.SetPos(m_pos - CVector2(50.0f, 25.0f) * m_scale);
	m_DamageUI.SetPos(m_pos + CVector2(m_DamageUI.GetSize().x * 2.5f, 0.0f) * m_scale);
	m_PercentUI.SetPos(m_pos + CVector2(m_DamageUI.GetSize().x * 3.7f, m_DamageUI.GetSize().y * 0.3f) * m_scale);
}

void Character_DamageUI::SetScale(float scale)
{
	m_scale = scale;
	m_IconUI.SetSize(m_IconUI.GetSize() * m_scale);
	m_DamageUI.SetSize(m_DamageUI.GetSize() * m_scale);
	m_PercentUI.SetSize(m_PercentUI.GetSize() * m_scale);
}

void Character_DamageUI::SetColorBoard(BOARDCOLOR color)
{
	switch (color)
	{
	case Character_DamageUI::BOARDCOLOR::RED:
	{
		
	}
		break;
	case Character_DamageUI::BOARDCOLOR::BLUE:
	{

	}
		break;
	}
}


