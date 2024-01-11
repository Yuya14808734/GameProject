#pragma once
#include "Character_Base.h"

class CharacterBase_WakeUpState : public Character_State
{
public:
	CharacterBase_WakeUpState() {};
	~CharacterBase_WakeUpState() override {};

	virtual void Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
};