#include "Character00_BlowAwayState.h"

void Character00_BlowAwayState::Init()
{
	CharacterBase_BlowAwayState::Init();
	m_pModelDrawer->PlayAnime("Damage01", true);
	m_FrameCount = 0;
	m_AnimeTime = 0.144f;
	m_pModelDrawer->SetAnimeTime(m_AnimeTime);
	m_pModelDrawer->SetRotatePosShift(true);
	m_ShiftCenterPosVector = CVector3::GetZero();
}

void Character00_BlowAwayState::Uninit()
{
	CharacterBase_BlowAwayState::Uninit();
}

void Character00_BlowAwayState::Update()
{
	CharacterBase_BlowAwayState::Update();

	const int AnimeEndFrame = 20;			//�A�j���[�V�������~����t���[��
	const float AnimeStartTime = 0.144f;		//�A�j���[�V�����̎n�߂鎞��
	const float AnimeEndTime = 0.387f;		//�A�j���[�V�������I��鎞��
	const float AnimeAllTime = AnimeEndTime - AnimeStartTime;	//�A�j���[�V�����̎���

	m_FrameCount++;
	m_AnimeTime = static_cast<float>(m_FrameCount) / static_cast<float>(AnimeEndFrame) * AnimeAllTime + AnimeStartTime;
	float percent = (m_AnimeTime - AnimeStartTime) / AnimeAllTime;
	
	m_ShiftCenterPosVector = CVector3::GetForward() * (percent * 0.5f) +
		CVector3::GetUp() * (percent * -0.2f);

	if (m_AnimeTime > AnimeEndTime)
	{
		m_AnimeTime = AnimeEndTime;
	}

	m_pModelDrawer->SetRotatePosShiftVector(m_ShiftCenterPosVector);
	m_pModelDrawer->SetAnimeTime(m_AnimeTime);
}

