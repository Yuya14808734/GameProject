#pragma once
#include "Image2D.h"

//Winner�̕����Ə������v���C���[�̔ԍ������X�ɕ`�悵�Ă����N���X
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
	//=====<�����֐�>=====
	void SetLetterMovePercent(float Percent);
	void SetPlayerNumAlphaPercent(float Percent);

	//=====<�����̃t�F�[�h�C��>=====
	void Update_LetterMoveFadeIn();
	//=====<�����̃t�F�[�h�A�E�g>=====
	void Update_LetterMoveFadeOut();
	//=====<�������v���C���[�ԍ��̃t�F�[�h�C��>=====
	void Update_WinnerNumFadeIn();
	//=====<�������v���C���[�ԍ��̃t�F�[�h�A�E�g>=====
	void Update_WinnerNumFadeOut();

public:
	//=====<�����̃t�F�[�h�C��>=====
	void StartFadeIn_LetterMove(float FadeInTime);
	//=====<�����̃t�F�[�h�A�E�g>=====
	void StartFadeOut_LetterMove(float FadeOutTime);
	//=====<�������v���C���[�ԍ��̃t�F�[�h�C��>=====
	void StartFadeIn_WinnerNum(float FadeInTime);
	//=====<�������v���C���[�ԍ��̃t�F�[�h�A�E�g>=====
	void StartFadeOut_WinnerNum(float FadeOutTime);


private:

	//=====<�e�����Ɗe�ʒu�̕ϐ�>=====
	Image2D m_WinnerLetters[5];
	Image2D m_WinnerPlayerNumImage;
	float	m_WinnerLetters_PosX[6] = {};
	float	m_WinnerLetters_Alpha = 0.0f;

	//=====<�����̃t�F�[�h�C��>=====
	float	m_LetterMoveFadeInTime = 0.0f;
	bool	m_isLeetterMoveFadeIn		= false;
	float	m_LetterMoveFadeInCount		= 0.0f;
	float	m_LetterMoveFadePercent = 0.0f;
	
	//=====<�����̃t�F�[�h�A�E�g>=====
	float	m_LetterMoveFadeOutTime = 0.0f;
	bool	m_isLetterMoveFadeOut		= false;
	float	m_LetterMoveFadeOutCount	= 0.0f;
		
	//=====<�������v���C���[�ԍ��̃t�F�[�h�C��>=====
	float	m_WinnerNumFadeInTime = 0.0f;
	bool	m_isWinnerNumFadeIn			= false;
	float	m_WinnerNumFadeInCount		= 0.0f;
		
	//=====<�������v���C���[�ԍ��̃t�F�[�h�A�E�g>=====
	float	m_WinnerNumFadeOutTime = 0.0f;
	bool	m_isWinnerNumFadeOut		= false;
	float	m_WinnerNumFadeOutCount		= 0.0f;	
};