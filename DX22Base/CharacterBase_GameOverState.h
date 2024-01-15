#pragma once
#include "Character_State.h"

class CharacterBase_GameOverState : public Character_State
{
public:
	CharacterBase_GameOverState() {};
	~CharacterBase_GameOverState() override {};

	virtual void Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
};