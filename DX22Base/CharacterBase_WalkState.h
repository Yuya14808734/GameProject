#pragma once
#include "Character_Base.h"

class CharacterBase_WalkState : public Character_State
{
public:
	CharacterBase_WalkState() {};
	~CharacterBase_WalkState() override {};

	virtual void Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
};