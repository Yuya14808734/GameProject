#pragma once
#include "Image2D.h"

//Winnerの文字と勝ったプレイヤーの番号を徐々に描画していくクラス
class PraiseWinnerPlayerText
{
private:
	const float m_LetterDistance = 130.0f;
	const float m_LetterMoveFadeInTime = 0.5f;
	const float m_LetterMoveFadeOutTime = 0.5f;
	const CVector2 m_WinnerNumDrawStartPos = CVector2(1280.0f * 0.5f, 720.0f * 0.65f);
	const CVector2 m_WinnerNumDrawEndPos = CVector2(1280.0f * 0.5f, 720.0f * 0.7f);
	const float m_WinnerNumDrawFadeInTime = 0.7f;
	const float m_WinnerNumDrawFadeOutTime = 0.7f;

public:
	PraiseWinnerPlayerText();
	~PraiseWinnerPlayerText();
	void Update();
	void Draw();

private:
	void SetLetterMovePercent(float Percent);
	void SetPlayerNumAlphaPercent(float Percent);
	void Update_LetterMoveFadeIn();
	void Update_LetterMoveFadeOut();
	void Update_WinnerNumFadeIn();
	void Update_WinnerNumFadeOut();

public:
	void StartFadeIn_LetterMove();
	void StartFadeOut_LetterMove();
	void StartFadeIn_WinnerNum();
	void StartFadeOut_WinnerNum();

private:
	bool	m_isLeetterMoveFadeIn		= false;
	bool	m_isLetterMoveFadeOut		= false;
	bool	m_isWinnerNumFadeIn			= false;
	bool	m_isWinnerNumFadeOut		= false;
	float	m_LetterMoveFadeInCount		= 0.0f;
	float	m_LetterMoveFadeOutCount	= 0.0f;
	float	m_WinnerNumFadeInCount		= 0.0f;
	float	m_WinnerNumFadeOutCount		= 0.0f;


	Image2D m_WinnerLetters[5];
	float	m_WinnerLetters_PosX[6] = {};
	float	m_WinnerLetters_Alpha = 0.0f;
	Image2D m_WinnerPlayerNumImage;
};