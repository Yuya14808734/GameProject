#include "Character00_WakeUpState.h"

void Character00_WakeUpState::Init()
{
	CharacterBase_WakeUpState::Init();

	m_pModelDrawer->PlayAnime("Damage01", true);
	m_AnimeTime = 2.082f;
	m_FrameCount = 0;
	m_pCharacter->SetInvincible(true);
}

void Character00_WakeUpState::Uninit()
{
	CharacterBase_WakeUpState::Uninit();
	m_pCharacter->SetInvincible(false);
}

void Character00_WakeUpState::Update()
{
	CharacterBase_WakeUpState::Update();

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
		m_pCharacter->SetNextState(Character::STATE::State_Idle);
	}

	m_pModelDrawer->SetAnimeTime(m_AnimeTime);
}