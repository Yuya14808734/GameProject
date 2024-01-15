#pragma once
#include "Character_State.h"

class CharacterBase_LeanBackState : public Character_State
{
public:
	CharacterBase_LeanBackState() {};
	~CharacterBase_LeanBackState() override {};

	virtual void Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
};