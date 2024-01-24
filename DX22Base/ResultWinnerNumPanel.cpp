#include "ResultWinnerNumPanel.h"
#include "Select01_CharacterList.h"

ResultWinnerNumPanel::ResultWinnerNumPanel()
	:m_isDrawStart(false),
	m_CountTime(0.0f),
	m_MoveEndTime(0.0f)
{
	m_pos = CVector3(320.0f, 205.0f, 0.0f);
}

ResultWinnerNumPanel::~ResultWinnerNumPanel()
{
}

void ResultWinnerNumPanel::Update()
{
	if (!m_isDrawStart) { return; }

	m_CountTime = m_CountTime + 1.0f / 60.0f;

	if (m_CountTime > m_MoveEndTime)
	{
		m_isDrawStart = false;
		m_CountTime = m_MoveEndTime;
	}

	float Percent = m_CountTime / m_MoveEndTime;

	float sizeEase = 1.0f - sqrtf(1 - powf(Percent,2));
	m_size = (m_StartSize * (1.0f - sizeEase)) 
		+ (m_DefaultSize * sizeEase);

	m_color.w = 1.0f - powf(1 - Percent, 4.0f);
}

void ResultWinnerNumPanel::SetPanelImage(int PlayerNum)
{
	//=====<キャラクターの画像を設定>=====
	switch (PlayerNum)
	{
	case 1:
		SetTexture("Assets/UI/Win1Player.png");
		break;
	case 2:
		//2Pが勝っていたら
		SetTexture("Assets/UI/Win2Player.png");
		break;
	default:
		//ほぼないけど他の場合
		SetTexture("Assets/UI/Win1Player.png");
		break;
	}
}

void ResultWinnerNumPanel::DrawStart(float MoveEndTime)
{
	m_isDrawStart = true;
	m_CountTime = 0.0f;
	m_MoveEndTime = MoveEndTime;
}
