#pragma once
#include "Character_State.h"

class CharacterBase_FallDownState : public Character_State
{
public:
	CharacterBase_FallDownState() {};
	~CharacterBase_FallDownState() override {};

	virtual void Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
};