#include "ResultWinnerCharacterImage.h"
#include "Select01_CharacterList.h"

ResultWinnerCharacterImage::ResultWinnerCharacterImage()
	:m_pWinnerCharacterImage(nullptr),
	m_isDrawStart(false),
	m_CharacterAlpha(0.0f),
	m_CountTime(0.0f),
	m_MoveEndTime(0.0f)
{
}

ResultWinnerCharacterImage::~ResultWinnerCharacterImage()
{
}

void ResultWinnerCharacterImage::Update()
{
	//‚Ü‚¾“®‚«Žn‚ß‚Ä‚¢‚È‚¯‚ê‚Î
	if (!m_isDrawStart) 
	{ return; }

	//‰æ‘œ‚ªÝ’è‚³‚ê‚Ä‚¢‚È‚¯‚ê‚Î
	if (m_pWinnerCharacterImage == nullptr)
	{ return; }

	m_CountTime = m_CountTime + 1.0f / 60.0f;

	if (m_CountTime > m_MoveEndTime)
	{
		m_CountTime = m_MoveEndTime;
	}

	float m_Percent = m_CountTime / m_MoveEndTime;
	m_Percent = 1.0f - powf(1.0f - m_Percent, 5);

	m_CharacterDrawPos =
		(m_StartPos * (1.0f - m_Percent)) +
		(m_EndPos * m_Percent);

	m_CharacterAlpha = m_Percent;
	
}

void ResultWinnerCharacterImage::Draw()
{
	//‰æ‘œ‚ªÝ’è‚³‚ê‚Ä‚¢‚È‚¯‚ê‚Î
	if (m_pWinnerCharacterImage == nullptr)
	{ return; }

	m_pWinnerCharacterImage->m_pos = m_CharacterDrawPos;
	m_pWinnerCharacterImage->m_size = CVector2(435.0f, 640.0f) * 1.3f;
	m_pWinnerCharacterImage->m_color.w = m_CharacterAlpha;
	m_pWinnerCharacterImage->Draw();
}

void ResultWinnerCharacterImage::SetCharacterImage(int CharacterNum)
{
	switch (static_cast<SelectCharacterList::CHARACTER>(CharacterNum))
	{
	case SelectCharacterList::CHARACTER::NONE:
	case SelectCharacterList::CHARACTER::MAX:
		CharacterNum =
			static_cast<int>(SelectCharacterList::CHARACTER::UNITYCHAN);
		break;
	}

	m_pWinnerCharacterImage =
		&((SelectCharacterList::GetCharacterStandImageList())[CharacterNum]);
}

void ResultWinnerCharacterImage::DrawStart(float MoveEndTime)
{
	m_isDrawStart = true;
	m_CountTime = 0.0f;
	m_MoveEndTime = MoveEndTime;
}