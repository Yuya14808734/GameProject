#pragma once
#include "MiniWindow.h"
#include "Character_Base.h"

class CharacterStateWindow : public MiniWindow
{
public:
	void SetCharacter(Character* pCharacter);
private:
	void Init() override;
	void Uninit() override;
	void DrawUpdate() override;

private:
	Character* m_pCharacter = nullptr;
};