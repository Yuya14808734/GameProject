#pragma once
#include "CharacterBase_DeadState.h"

class Character00_DeadState : public CharacterBase_DeadState
{
public:
	Character00_DeadState() {};
	~Character00_DeadState() override {};

	void Init() override;
	void Uninit() override;
	void Update() override;

private:
};