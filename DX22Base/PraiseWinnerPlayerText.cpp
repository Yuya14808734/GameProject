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
		m_WinnerLetters[i].m_pos.y = static_cast<float>(GetAppHeight()) * 0.4f;
		m_WinnerLetters[i].m_color.w = 0.0f;
	}

	
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

void PraiseWinnerPlayerText::SetWinPlayerNum(int WinPlayerNum)
{
	switch (WinPlayerNum)
	{
	case 1:
		m_WinnerPlayerNumImage.SetTexture("Assets/UI/ImageTextPlayer_1.png");
		break;
	case 2:
		m_WinnerPlayerNumImage.SetTexture("Assets/UI/ImageTextPlayer_2.png");
		break;
	}

}

void PraiseWinnerPlayerText::SetLetterMovePercent(float Percent)
{
	//=====<Percentを0～1の数値に入れ込む>=====
	float NormalizePercent = Percent;

	if (NormalizePercent > 1.0f) { NormalizePercent = 1.0f; }
	else if (NormalizePercent < 0.0f) { NormalizePercent = 0.0f; }

	//=====<各文字の設定>=====
	float EasePercent = 1.0f - powf(1.0f - NormalizePercent, 3);			//幅で使う割合
	float NowDistance = m_LetterDistance * EasePercent;
	NowDistance = NowDistance + (Percent * 5.0f);

	float LeftEddgePos = (static_cast<float>(GetAppWidth()) * 0.5f)			//左端の位置
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
	float NormalizePercent = Percent;

	if (NormalizePercent > 1.0f) { NormalizePercent = 1.0f; }
	else if (NormalizePercent < 0.0f) { NormalizePercent = 0.0f; }

	m_WinnerPlayerNumImage.m_color.w = NormalizePercent;
	
	m_WinnerPlayerNumImage.m_pos = 
		(m_WinnerNumDrawStartPos * (1.0f - NormalizePercent)) +
		(m_WinnerNumDrawEndPos * NormalizePercent);
}

//=============================================================
// 文字と文字の間をどんどん広げていきながら不透明にする
//=============================================================
void PraiseWinnerPlayerText::Update_LetterMoveFadeIn()
{
	if(!m_isLeetterMoveFadeIn)
	{
		return;
	}

	float Percent = 0.0f;

	m_LetterMoveFadeInCount += 1.0f / 60.0f;

	Percent = m_LetterMoveFadeInCount / m_LetterMoveFadeInTime;

	SetLetterMovePercent(Percent);
}

//=============================================================
// 文字と文字の間をどんどん狭めながら透明にする
//=============================================================
void PraiseWinnerPlayerText::Update_LetterMoveFadeOut()
{
	if (!m_isLetterMoveFadeOut)
	{
		return;
	}

	float Percent = 0.0f;

	m_LetterMoveFadeOutCount += 1.0f / 60.0f;

	Percent = m_LetterMoveFadeOutCount / m_LetterMoveFadeOutTime;

	SetLetterMovePercent(m_LetterMoveFadePercent * (1.0f - Percent));
}

//=============================================================
// 移動しながら不透明にする
//=============================================================
void PraiseWinnerPlayerText::Update_WinnerNumFadeIn()
{
	if(!m_isWinnerNumFadeIn)
	{
		return;
	}

	float Percent = 0.0f;

	m_WinnerNumFadeInCount += 1.0f / 60.0f;

	Percent = m_WinnerNumFadeInCount / m_WinnerNumFadeInTime;

	SetPlayerNumAlphaPercent(Percent);
}

//=============================================================
// 移動しながら透明にする
//=============================================================
void PraiseWinnerPlayerText::Update_WinnerNumFadeOut()
{
	if (!m_isWinnerNumFadeOut)
	{
		return;
	}

	float Percent = 0.0f;

	m_WinnerNumFadeOutCount += 1.0f / 60.0f;

	Percent = m_WinnerNumFadeOutCount / m_WinnerNumFadeOutTime;

	SetPlayerNumAlphaPercent(1.0f - Percent);
}

void PraiseWinnerPlayerText::StartFadeIn_LetterMove(float FadeInTime)
{
	m_isLeetterMoveFadeIn = true;
	m_LetterMoveFadeInCount = 0.0f;
	m_LetterMoveFadeInTime = FadeInTime;
}

void PraiseWinnerPlayerText::StartFadeOut_LetterMove(float FadeOutTime)
{
	m_isLetterMoveFadeOut = true;
	m_LetterMoveFadeOutCount = 0.0f;
	m_LetterMoveFadeOutTime = FadeOutTime; 
	m_LetterMoveFadePercent = m_LetterMoveFadeInCount / m_LetterMoveFadeInTime;
}

void PraiseWinnerPlayerText::StartFadeIn_WinnerNum(float FadeInTime)
{
	m_isWinnerNumFadeIn = true;
	m_WinnerNumFadeInCount = 0.0f;
	m_WinnerNumFadeInTime = FadeInTime;
}

void PraiseWinnerPlayerText::StartFadeOut_WinnerNum(float FadeOutTime)
{
	m_isWinnerNumFadeOut = true;
	m_WinnerNumFadeOutCount = 0.0f;
	m_WinnerNumFadeOutTime = FadeOutTime;
}
