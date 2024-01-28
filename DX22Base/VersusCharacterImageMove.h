#pragma once
#include "Image2D.h"
#include "Select01_CharacterList.h"

class VersusCharacterImageMove
{
public:
	VersusCharacterImageMove();
	~VersusCharacterImageMove();
	void Update();
	void Draw();

	void StartAnimation();
	void SetCharacterImage(SelectCharacterList::CHARACTER CharacterNum);
	void SetAnimeTime(float time);
	void SetLerpPos(const CVector3& StartPos, const CVector3& EndPos);

private:
	Image2D* m_pCharacterImage = nullptr;
	bool m_isDrawStart = false;
	float m_CharacterAlpha = 0.0f;
	CVector3 m_CharacterDrawPos;
	float m_CountTime = 0.0f;
	float m_MoveEndTime = 0.0f;

	CVector3 m_StartPos;
	CVector3 m_EndPos;
	CVector2 m_ImageSize;
};
