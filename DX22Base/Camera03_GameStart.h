#pragma once
#include "CameraBase.h"
#include "Character_Base.h"

class CameraGameStart : public CameraBase
{
private:
	static constexpr float m_CharacterLerpTime = 0.3f;
	static constexpr float m_CharacterLookTime = 0.7f;

public:
	CameraGameStart();
	~CameraGameStart();
	void Update() override;
	void ChangeInit() override;
	void ChangeUninit() override;
	void SetCharacter(std::vector<Character*>& pCharacterVector);

private:
	std::vector<CVector3> m_CharacterPos;
	float m_Time = 0.0f;
	int m_NowLookCharacterNum = 0;
	CVector3 m_StartPos;
	CVector3 m_EndPos;
};

