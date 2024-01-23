#include "PraiseWinnerPlayerText.h"
#include "Main.h"

PraiseWinnerPlayerText::PraiseWinnerPlayerText()
{
	const char* FilePath[5] =
	{
		"Assets/UI/GoldLetter_W.png",
		"Assets/UI/GoldLetter_I.png",
		"Assets/UI/GoldLetter_N.png",
		"Assets/UI/GoldLetter_E.png",
		"Assets/UI/GoldLetter_R.png",
	};

	for (int i = 0; i < 5; i++)
	{
		m_WinnerLetters[i].SetTexture(FilePath[i]);
		m_WinnerLetters[i].m_size = CVector2(320.0f, 320.0f) * 0.6f;
		m_WinnerLetters[i].m_pos.y = static_cast<float>(GetAppHeight()) * 0.45f;
		m_WinnerLetters[i].m_color.w = 0.0f;
	}

	m_WinnerPlayerNumImage.SetTexture("Assets/UI/ImageTextPlayer_1.png");
	m_WinnerPlayerNumImage.m_size = CVector2(640.0f, 88.0f);
	m_WinnerPlayerNumImage.m_color.w = 0.0f;
	m_WinnerPlayerNumImage.m_IsVisible = true;

	for (int i = 0; i < 6; i++)
	{
		m_WinnerLetters_PosX[i] = 0.0f;
	}

	m_WinnerLetters_Alpha = 0.0f;

	m_isLeetterMoveFadeIn	=
	m_isLetterMoveFadeOut	=
	m_isWinnerNumFadeIn		=
	m_isWinnerNumFadeOut	= false;

	 m_LetterMoveFadeInCount	=
	 m_LetterMoveFadeOutCount	=
	 m_WinnerNumFadeInCount		=
	 m_WinnerNumFadeOutCount	= 0.0f;
}

PraiseWinnerPlayerText::~PraiseWinnerPlayerText()
{

}

void PraiseWinnerPlayerText::Update()
{
	Update_LetterMoveFadeIn();
	Update_LetterMoveFadeOut();
	Update_WinnerNumFadeIn();
	Update_WinnerNumFadeOut();
}

void PraiseWinnerPlayerText::Draw()
{
	int Num[6] = { 0,1,2,2,3,4 };
	for (int i = 0; i < 6; i++)
	{
		//ポジションとアルファを設定して描画
		m_WinnerLetters[Num[i]].m_pos.x =
			m_WinnerLetters_PosX[i];

		m_WinnerLetters[Num[i]].m_color.w =
			m_WinnerLetters_Alpha;

		m_WinnerLetters[Num[i]].Draw();
	}

	//m_WinnerPlayerNumImage.m_IsVisible = true;
	m_WinnerPlayerNumImage.Draw();
}

void PraiseWinnerPlayerText::SetLetterMovePercent(float Percent)
{
	//=====<各文字の設定>=====
	//WINNERを描画するときにNがかぶるので配列の番号を指定
	float EasePercent = 1.0f - powf(1.0f - Percent, 3);
	float NowDistance = m_LetterDistance * EasePercent;
	float LeftEddgePos = (static_cast<float>(GetAppWidth()) * 0.5f)
		- (NowDistance * 2.5f);

	for (int i = 0; i < 6; i++)
	{
		//各文字の位置を決める
		m_WinnerLetters_PosX[i] = LeftEddgePos +
			(NowDistance * static_cast<float>(i));
	}
	//イージング関数でアルファ値をいじります
	m_WinnerLetters_Alpha = EasePercent;
}

void PraiseWinnerPlayerText::SetPlayerNumAlphaPercent(float Percent)
{
	m_WinnerPlayerNumImage.m_color.w = Percent;
	
	m_WinnerPlayerNumImage.m_pos = 
		(m_WinnerNumDrawStartPos * (1.0f - Percent)) +
		(m_WinnerNumDrawEndPos * Percent);
}

void PraiseWinnerPlayerText::Update_LetterMoveFadeIn()
{
	if(!m_isLeetterMoveFadeIn)
	{
		return;
	}

	float Percent = 0.0f;

	m_LetterMoveFadeInCount += 1.0f / 60.0f;

	if (m_LetterMoveFadeInCount > m_LetterMoveFadeInTime)
	{
		Percent = 1.0f;
		m_isLeetterMoveFadeIn = false;
	}
	else
	{
		Percent = m_LetterMoveFadeInCount / m_LetterMoveFadeInTime;
	}

	SetLetterMovePercent(Percent);
}

void PraiseWinnerPlayerText::Update_LetterMoveFadeOut()
{
	if (!m_isLetterMoveFadeOut)
	{
		return;
	}

	float Percent = 0.0f;

	m_LetterMoveFadeOutCount += 1.0f / 60.0f;

	if (m_LetterMoveFadeOutCount > m_LetterMoveFadeOutTime)
	{
		Percent = 1.0f;
		m_isLetterMoveFadeOut = false;
	}
	else
	{
		Percent = m_LetterMoveFadeOutCount / m_LetterMoveFadeOutTime;
	}

	SetLetterMovePercent(1.0f - Percent);
}

void PraiseWinnerPlayerText::Update_WinnerNumFadeIn()
{
	if(!m_isWinnerNumFadeIn)
	{
		return;
	}

	float Percent = 0.0f;

	m_WinnerNumFadeInCount += 1.0f / 60.0f;

	if (m_WinnerNumFadeInCount > m_WinnerNumDrawFadeInTime)
	{
		Percent = 1.0f;
		m_isWinnerNumFadeIn = false;
	}
	else
	{
		Percent = m_WinnerNumFadeInCount / m_WinnerNumDrawFadeInTime;
	}

	SetPlayerNumAlphaPercent(Percent);
}

void PraiseWinnerPlayerText::Update_WinnerNumFadeOut()
{
	if (!m_isWinnerNumFadeOut)
	{
		return;
	}

	float Percent = 0.0f;

	m_WinnerNumFadeOutCount += 1.0f / 60.0f;

	if (m_WinnerNumFadeOutCount > m_WinnerNumDrawFadeOutTime)
	{
		Percent = 1.0f;
		m_isWinnerNumFadeOut = false;
	}
	else
	{
		Percent = m_WinnerNumFadeOutCount / m_WinnerNumDrawFadeOutTime;
	}

	SetPlayerNumAlphaPercent(1.0f - Percent);
}

void PraiseWinnerPlayerText::StartFadeIn_LetterMove()
{
	m_isLeetterMoveFadeIn = true;
	m_LetterMoveFadeInCount = 0.0f;
}

void PraiseWinnerPlayerText::StartFadeOut_LetterMove()
{
	m_isLetterMoveFadeOut = true;
	m_LetterMoveFadeOutCount = 0.0f;
}

void PraiseWinnerPlayerText::StartFadeIn_WinnerNum()
{
	m_isWinnerNumFadeIn = true;
	m_WinnerNumFadeInCount = 0.0f;
}

void PraiseWinnerPlayerText::StartFadeOut_WinnerNum()
{
	m_isWinnerNumFadeOut = true;
	m_WinnerNumFadeOutCount = 0.0f;
}
