#pragma once
#include "Image2D.h"
#include "Calculation.h"

class ResultWinnerCharacterImage
{
private:
	const CVector2 m_StartPos = CVector2(-100.0f, 368.0f);
	const CVector2 m_EndPos = CVector2(908.0f, 368.0f);;

public:
	ResultWinnerCharacterImage();
	~ResultWinnerCharacterImage();
	void Update();
	void Draw();

	void SetCharacterImage(int CharacterNum);
	void DrawStart(float MoveEndTime);

private:
	Image2D* m_pWinnerCharacterImage = nullptr;
	bool m_isDrawStart = false;
	CVector3 m_CharacterDrawPos;
	float m_CharacterAlpha = 0.0f;
	float m_CountTime = 0.0f;
	float m_MoveEndTime = 0.0f;
};