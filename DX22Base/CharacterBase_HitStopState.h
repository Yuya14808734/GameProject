#pragma once
#include "Character_Base.h"

class CharacterBase_HitStopState : public Character_State
{
public:
	CharacterBase_HitStopState() {};
	~CharacterBase_HitStopState() override {};

	virtual void Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
	void SetHitStop(int HitStopTime, Character::STATE NextState, bool IsShake);



private:
	CVector3 m_TempPos;
	Character::STATE m_NextState = Character::STATE::State_None;
	bool m_Shake = false;
	int m_HitStopCount = 0;
};