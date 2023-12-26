#include "Character_00.h"

void Character_00::WakeUpInit()
{
	Character::WakeUpInit();

	m_CharacterModel.PlayAnime("Damage01", true);
	m_AnimeTime = 2.082f;
	m_FrameCount = 0;
	m_Invincible = true;
}

void Character_00::WakeUpUninit()
{
	Character::WakeUpUninit();
	m_Invincible = false;
}

void Character_00::WakeUpUpdate()
{
	Character::WakeUpUpdate();

	const float AnimeEndFrame = 20.0f;			//�A�j���[�V�������~����t���[��
	const float AnimeStartTime = 2.082f;		//�A�j���[�V�����̎n�߂鎞��
	const float AnimeEndTime = 3.6f;		//�A�j���[�V�������I��鎞��
	const float AnimeAllTime = AnimeEndTime - AnimeStartTime;	//�A�j���[�V�����̎���

	m_FrameCount++;

	m_AnimeTime = static_cast<float>(m_FrameCount) / AnimeEndFrame * AnimeAllTime + AnimeStartTime;


	//�N���オ��A�j���[�V�������I��������ҋ@��Ԃɂ���
	if (m_AnimeTime > AnimeEndTime)
	{
		m_AnimeTime = AnimeEndTime;
		ChangeState(Character::STATE::IDLE);
	}

	m_CharacterModel.SetAnimeTime(m_AnimeTime);
}