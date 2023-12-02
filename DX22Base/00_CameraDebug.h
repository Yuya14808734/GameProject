#pragma once
#include "CameraBase.h"
#include "Character_Base.h"

class CameraDebug : public CameraBase
{
public:
	CameraDebug();
	~CameraDebug();
	void Update() override;
	void ChangeInit() override;
	void ChangeUninit() override;
	void SetCharacter(Character* pCharacter);

private:
	Character* m_pCharacter = nullptr;
	CVector3 m_AddPos;
};
