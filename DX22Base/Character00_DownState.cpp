#include "Character_00.h"

void Character_00::DownInit()
{
	Character::DownInit();

	m_CharacterModel.PlayAnime("Damage01", true);
	m_AnimeTime = 0.394f;
	m_FrameCount = 0;
	m_Invincible = true;
}

void Character_00::DownUninit()
{
	Character::DownUninit();
}

void Character_00::DownUpdate()
{
	Character::DownUpdate();

	const int AnimeEndFrame = 20;			//�A�j���[�V�������~����t���[��
	const float AnimeStartTime = 0.394f;		//�A�j���[�V�����̎n�߂鎞��
	const float AnimeEndTime = 1.461f;		//�A�j���[�V�������I��鎞��
	const float AnimeAllTime = AnimeEndTime - AnimeStartTime;	//�A�j���[�V�����̎���

	m_FrameCount++;

	m_AnimeTime = static_cast<float>(m_FrameCount) / static_cast<float>(AnimeEndFrame) * AnimeAllTime + AnimeStartTime;

	//�A�j���[�V�������I��������ҋ@��Ԃɂ���
	if (m_AnimeTime > AnimeEndTime)
	{
		m_AnimeTime = AnimeEndTime;

		//�]��ł���Ƃ��ɏ�{�^���������ƋN���オ��
		if (m_Controller.GetWakeUp())
		{
			ChangeState(Character::STATE::WAKEUP);
		}
	}

	//�A�j���[�V�������I�����Ă�����x���Ԃ��������疳�G���O��
	if (m_FrameCount > AnimeEndFrame + 30)
	{
		m_Invincible = false;
	}

	m_CharacterModel.SetAnimeTime(m_AnimeTime);
}