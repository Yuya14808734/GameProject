#include "Character_00.h"

void Character_00::LeanBackInit()
{
	Character::LeanBackInit();
	m_FrameCount = 0;
	m_AnimeTime = 0.0f;
	m_CharacterModel.PlayAnime("Damage00", true);
}

void Character_00::LeanBackUninit()
{
	Character::LeanBackUninit();
}

void Character_00::LeanBackUpdate()
{
	Character::LeanBackUpdate();

	const int LeanBackEndFrame = 20;			//�A�j���[�V�������~����t���[��
	const float AnimeStartTime = 0.0f;		//�A�j���[�V�����̎n�߂鎞��
	const float AnimeEndTime = 1.167f;		//�A�j���[�V�������I��鎞��
	const float AnimeAllTime = AnimeEndTime - AnimeStartTime;	//�A�j���[�V�����̎���

	m_FrameCount++;

	m_AnimeTime = AnimeAllTime * (static_cast<float>(m_FrameCount) / static_cast<float>(LeanBackEndFrame)) + AnimeStartTime;

	//�A�j���[�V����
	if (m_AnimeTime > AnimeEndTime)
	{
		m_AnimeTime = AnimeEndTime;
		ChangeState(Character::STATE::IDLE);
	}
}