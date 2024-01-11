#pragma once
#include "Character_Base.h"

class CharacterBase_BlowAwayState : public Character_State
{
public:
	CharacterBase_BlowAwayState() {};
	~CharacterBase_BlowAwayState() override {};

	virtual void Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
};