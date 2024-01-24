#pragma once
#include "Image2D.h"

//Winnerの文字と勝ったプレイヤーの番号を徐々に描画していくクラス
class PraiseWinnerPlayerText
{
private:
	const float m_LetterDistance = 130.0f;
	const CVector2 m_WinnerNumDrawStartPos = CVector2(1280.0f * 0.5f, 720.0f * 0.55f);
	const CVector2 m_WinnerNumDrawEndPos = CVector2(1280.0f * 0.5f, 720.0f * 0.6f);

public:
	PraiseWinnerPlayerText();
	~PraiseWinnerPlayerText();
	void Update();
	void Draw();

private:
	//=====<動き関数>=====
	void SetLetterMovePercent(float Percent);
	void SetPlayerNumAlphaPercent(float Percent);

	//=====<文字のフェードイン>=====
	void Update_LetterMoveFadeIn();
	//=====<文字のフェードアウト>=====
	void Update_LetterMoveFadeOut();
	//=====<勝ったプレイヤー番号のフェードイン>=====
	void Update_WinnerNumFadeIn();
	//=====<勝ったプレイヤー番号のフェードアウト>=====
	void Update_WinnerNumFadeOut();

public:
	//=====<文字のフェードイン>=====
	void StartFadeIn_LetterMove(float FadeInTime);
	//=====<文字のフェードアウト>=====
	void StartFadeOut_LetterMove(float FadeOutTime);
	//=====<勝ったプレイヤー番号のフェードイン>=====
	void StartFadeIn_WinnerNum(float FadeInTime);
	//=====<勝ったプレイヤー番号のフェードアウト>=====
	void StartFadeOut_WinnerNum(float FadeOutTime);


private:

	//=====<各文字と各位置の変数>=====
	Image2D m_WinnerLetters[5];
	Image2D m_WinnerPlayerNumImage;
	float	m_WinnerLetters_PosX[6] = {};
	float	m_WinnerLetters_Alpha = 0.0f;

	//=====<文字のフェードイン>=====
	float	m_LetterMoveFadeInTime = 0.0f;
	bool	m_isLeetterMoveFadeIn		= false;
	float	m_LetterMoveFadeInCount		= 0.0f;
	float	m_LetterMoveFadePercent = 0.0f;
	
	//=====<文字のフェードアウト>=====
	float	m_LetterMoveFadeOutTime = 0.0f;
	bool	m_isLetterMoveFadeOut		= false;
	float	m_LetterMoveFadeOutCount	= 0.0f;
		
	//=====<勝ったプレイヤー番号のフェードイン>=====
	float	m_WinnerNumFadeInTime = 0.0f;
	bool	m_isWinnerNumFadeIn			= false;
	float	m_WinnerNumFadeInCount		= 0.0f;
		
	//=====<勝ったプレイヤー番号のフェードアウト>=====
	float	m_WinnerNumFadeOutTime = 0.0f;
	bool	m_isWinnerNumFadeOut		= false;
	float	m_WinnerNumFadeOutCount		= 0.0f;	
};