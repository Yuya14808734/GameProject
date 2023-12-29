#pragma once
#include "CameraBase.h"
#include "Character_Base.h"
#include "Stage_Base.h"

class CameraGame : public CameraBase
{
public:
	CameraGame();
	~CameraGame();
	void Update() override;
	void ChangeInit() override;
	void ChangeUninit() override;
	void SetCharacter(std::vector<Character*>* pCharacterVector);
	void SetStage(Stage* pStage);

private:
	std::vector<Character*>* m_pCharacterVector = nullptr;
	Stage* m_pStage = nullptr;
};
