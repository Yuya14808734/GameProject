#pragma once
#include "Character_Base.h"

class CharacterBase_JumpState : public Character_State
{
public:
	CharacterBase_JumpState() {};
	~CharacterBase_JumpState() override {};

	virtual void Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
};