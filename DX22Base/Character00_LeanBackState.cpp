#include "Character00_LeanBackState.h"

void Character00_LeanBackState::Init()
{
	CharacterBase_LeanBackState::Init();
	m_FrameCount = 0;
	m_AnimeTime = 0.0f;
	m_pModelDrawer->PlayAnime("Damage00", true);
}

void Character00_LeanBackState::Uninit()
{
	CharacterBase_LeanBackState::Uninit();
}

void Character00_LeanBackState::Update()
{
	CharacterBase_LeanBackState::Update();

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
		m_pCharacter->SetNextState(Character::STATE::State_Idle);
	}
}