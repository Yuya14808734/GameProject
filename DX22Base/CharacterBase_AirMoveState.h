#pragma once
#include "Character_Base.h"

class CharacterBase_AirMoveState : public Character_State
{
public:
	CharacterBase_AirMoveState() {};
	~CharacterBase_AirMoveState() override {};

	virtual void Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
};

