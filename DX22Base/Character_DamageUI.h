#pragma once
#include "Image2D.h"

class Character_DamageNumUI : public Image2D
{
	Character_DamageNumUI();
	~Character_DamageNumUI() override;
	void Update() override;
	void PrevDraw() override;
};

class Character_DamageIconUI : public Image2D
{
	Character_DamageIconUI();
	~Character_DamageIconUI();
	void Update() override;
	void PrevDraw() override;
};

class Character_DamageUI
{
private:
	Character_DamageNumUI m_NumUI;
	Character_DamageIconUI m_IconUI;

public:
	Character_DamageUI();
	~Character_DamageUI();
	void Update();
	void Draw();

};