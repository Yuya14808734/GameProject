#pragma once
#include "Character_Base.h"

class CharacterBase_IdleState : public Character_State
{
public:
	CharacterBase_IdleState() {};
	~CharacterBase_IdleState() override {};

	virtual void Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
};