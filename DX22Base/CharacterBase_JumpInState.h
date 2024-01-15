#pragma once
#include "Character_State.h"

class CharacterBase_JumpInState : public Character_State
{
public:
	CharacterBase_JumpInState() {};
	~CharacterBase_JumpInState() override {};

	virtual void Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
};