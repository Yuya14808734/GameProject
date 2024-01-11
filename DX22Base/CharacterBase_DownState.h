#pragma once
#include "Character_Base.h"

class CharacterBase_DownState : public Character_State
{
public:
	CharacterBase_DownState() {};
	~CharacterBase_DownState() override {};

	virtual void Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
};