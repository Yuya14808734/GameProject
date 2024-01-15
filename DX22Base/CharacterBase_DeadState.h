#pragma once
#include "Character_State.h"

class CharacterBase_DeadState : public Character_State
{
public:
	CharacterBase_DeadState() {};
	~CharacterBase_DeadState() override {};

	virtual void Init() override;
	virtual void Uninit() override;
	virtual void Update() override;

private:
	int m_ChangeStateCount = 0;
};
