#pragma once
#include "Character_State.h"

//==========================================================================
//�X�}�u���Ɠ����悤�Ȗ��O�ɂ��Ă��܂�
//https://www.youtube.com/watch?v=V40sMUAE5ek
//==========================================================================

class Character_AttackState : public Character_State
{
public:
	Character_AttackState() :Character_State(Character_State::TYPE::ATTACK) {};
	virtual ~Character_AttackState() {};
	virtual void HitCharacter(Character* pHitCharacter) {};

protected:
	virtual void Init() override {};
	virtual void Uninit() override {};
	virtual void Update() override {};
};