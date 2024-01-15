#pragma once
#include "Character_State.h"

class CharacterBase_RespawnState : public Character_State
{
public:
	CharacterBase_RespawnState() {};
	~CharacterBase_RespawnState() override {};

	virtual void Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
private:
	CVector3 m_RespawnStartPos;
	CVector3 m_RespawnEndPos;
	float m_RespawnLerpPercent = 0.0f;

};