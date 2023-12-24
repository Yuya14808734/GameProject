#include "Character_00.h"

void Character_00::BlowAwayInit()
{
	Character::BlowAwayInit();
	m_CharacterModel.PlayAnime("Damage01", true);
	m_AttackTime = 0;
	m_AnimeTime = 0.144f;
	m_CharacterModel.SetAnimeTime(m_AnimeTime);
	m_CharacterModel.SetRotatePosShift(true);
	m_ShiftCenterPos = CVector3::GetZero();
}

void Character_00::BlowAwayUninit()
{
	Character::BlowAwayUninit();
}

void Character_00::BlowAwayUpdate()
{
	Character::BlowAwayUpdate();

	const int AnimeEndFrame = 20;			//�A�j���[�V�������~����t���[��
	const float AnimeStartTime = 0.144f;		//�A�j���[�V�����̎n�߂鎞��
	const float AnimeEndTime = 0.387f;		//�A�j���[�V�������I��鎞��
	const float AnimeAllTime = AnimeEndTime - AnimeStartTime;	//�A�j���[�V�����̎���

	m_AttackTime++;
	m_AnimeTime = static_cast<float>(m_AttackTime) / static_cast<float>(AnimeEndFrame) * AnimeAllTime + AnimeStartTime;
	float percent = (m_AnimeTime - AnimeStartTime) / AnimeAllTime;
	
	m_ShiftCenterPos = CVector3::GetForward() * (percent * 0.5f) +
		CVector3::GetUp() * (percent * -0.2f);

	if (m_AnimeTime > AnimeEndTime)
	{
		m_AnimeTime = AnimeEndTime;
	}

	m_CharacterModel.SetAnimeTime(m_AnimeTime);
}

