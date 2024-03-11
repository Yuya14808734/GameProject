#pragma once
#include "Character_State.h"

class CharacterBase_WalkState : public Character_State
{
public:
	CharacterBase_WalkState() {};
	~CharacterBase_WalkState() override {};

	virtual void Init() override;
	virtual void Uninit() override;
	virtual void Update() override;

private:
	int m_WalkTimeCount = 0;
};