#pragma once
#include "CameraBase.h"
#include "Character_Base.h"

class CameraDebug : public CameraBase
{
public:
	CameraDebug();
	~CameraDebug();
	void Update() override;

private:
	Character* m_pCharacter = nullptr;
	CVector3 m_LookVec;
};
