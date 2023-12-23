#include "Character_00.h"

void Character_00::BlowAwayInit()
{
	Character::BlowAwayInit();
	m_CharacterModel.PlayAnime("Damage01", true);
	m_AttackTime = 0;
	m_AnimeTime = 0.144f;
	m_CharacterModel.SetAnimeTime(m_AnimeTime);
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

	if (m_AnimeTime > AnimeEndTime)
	{
		m_AnimeTime = AnimeEndTime;
	}

	m_CharacterModel.SetAnimeTime(m_AnimeTime);
}

