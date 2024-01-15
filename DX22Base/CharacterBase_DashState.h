#pragma once
#include "Character_State.h"

class CharacterBase_DashState : public Character_State
{
public:
	CharacterBase_DashState() {};
	~CharacterBase_DashState() override {};

	virtual void Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
};