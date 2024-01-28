#include "VersusCharacterImageMove.h"

VersusCharacterImageMove::VersusCharacterImageMove()
	:m_pCharacterImage(nullptr),
	m_isDrawStart(false),
	m_CharacterAlpha(0.0f),
	m_CountTime(0.0f),
	m_MoveEndTime(0.0f)
{
}

VersusCharacterImageMove::~VersusCharacterImageMove()
{
}

void VersusCharacterImageMove::Update()
{
	//‚Ü‚¾“®‚«Žn‚ß‚Ä‚¢‚È‚¯‚ê‚Î
	if (!m_isDrawStart)
	{
		return;
	}

	//‰æ‘œ‚ªÝ’è‚³‚ê‚Ä‚¢‚È‚¯‚ê‚Î
	if (m_pCharacterImage == nullptr)
	{
		return;
	}

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

void VersusCharacterImageMove::Draw()
{
	//‰æ‘œ‚ªÝ’è‚³‚ê‚Ä‚¢‚È‚¯‚ê‚Î
	if (m_pCharacterImage == nullptr)
	{
		return;
	}

	m_pCharacterImage->m_pos = m_CharacterDrawPos;
	m_pCharacterImage->m_size = m_ImageSize;
	m_pCharacterImage->m_color.w = m_CharacterAlpha;
	m_pCharacterImage->Draw();
}

void VersusCharacterImageMove::StartAnimation()
{
	m_isDrawStart = true;
	m_CountTime = 0.0f;
}

void VersusCharacterImageMove::SetCharacterImage(SelectCharacterList::CHARACTER CharacterNum)
{
	switch (CharacterNum)
	{
	case SelectCharacterList::CHARACTER::NONE:
	case SelectCharacterList::CHARACTER::MAX:
		CharacterNum = SelectCharacterList::CHARACTER::UNITYCHAN;
		m_ImageSize = CVector2(435.0f, 640.0f) * 1.1f;
		break;
	}

	m_pCharacterImage =
		&((SelectCharacterList::GetCharacterStandImageList())
			[static_cast<int>(CharacterNum)]);
}

void VersusCharacterImageMove::SetAnimeTime(float time)
{
	m_MoveEndTime = time;
}

void VersusCharacterImageMove::SetLerpPos(const CVector3& StartPos, const CVector3& EndPos)
{
	m_StartPos = StartPos;
	m_EndPos = EndPos;
}

