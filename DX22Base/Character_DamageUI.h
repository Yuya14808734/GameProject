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

class Character_CharacterIconUI : public Image2D
{
public:
	Character_CharacterIconUI();
	~Character_CharacterIconUI();
	void Update() override;
	void PrevDraw() override;
	void SetIconTexture(const char* filePath);	//ÉAÉCÉRÉìÇÃê›íË

private:
};

class PercentUI : public Image2D
{
public:
	PercentUI();
	~PercentUI() override;
	void Update() override;
	void PrevDraw() override;
};

class Character_DamageUI
{
public:
	Character_DamageUI();
	~Character_DamageUI();
	void Update();
	void Draw();
	Character_DamageNumUI* GetDamageUI();
	Character_CharacterIconUI* GetCharacterIconUI();
	PercentUI* GetPercentUI();

private:
	CVector2 m_pos;
	float m_scale = 1.0f;

	Character_DamageNumUI m_DamageUI;
	Character_CharacterIconUI m_IconUI;
	PercentUI m_PercentUI;
};