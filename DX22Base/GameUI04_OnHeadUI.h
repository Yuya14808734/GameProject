#pragma once
#include "Image3D.h"

class Character;

class OnHeadUI : public Image3D
{
public:
	OnHeadUI();
	~OnHeadUI() override;
	void Update() override;

	void SetCharacter(Character* pCharacter);
	void SetHeadTexture(int PlayerNum);

private:
	void PrevDraw() override;

private:

	Character* m_pCharacter = nullptr;
};
