#pragma once
#include "CameraBase.h"
#include "Character_Base.h"

class CameraGame : public CameraBase
{
public:
	CameraGame();
	~CameraGame();
	void Update() override;
	void ChangeInit() override;
	void ChangeUninit() override;
	void SetCharacter(std::vector<Character*>* pCharacterVector);

private:
	std::vector<Character*>* m_CharacterVector = nullptr;
};
