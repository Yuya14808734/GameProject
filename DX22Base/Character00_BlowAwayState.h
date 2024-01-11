#pragma once
#include "CharacterBase_BlowAwayState.h"

class Character00_BlowAwayState : public CharacterBase_BlowAwayState
{
public:
	Character00_BlowAwayState() {};
	~Character00_BlowAwayState() override {};

	void Init() override;
	void Uninit() override;
	void Update() override;

private:
	int m_FrameCount = 0;
	float m_AnimeTime = 0.0f;
	CVector3 m_ShiftCenterPosVector;
};
