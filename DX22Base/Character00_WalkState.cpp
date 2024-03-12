#include "Character00_WalkState.h"

void Character00_WalkState::Init()
{
	CharacterBase_WalkState::Init();
	m_pModelDrawer->PlayAnime("Walk", true);
	m_AnimeTime = 0.0f;

	m_pRightFootStepSE = SoundManager::GetSE("FootSteps01_Walk");
	m_pLeftFootStepSE = SoundManager::GetSE("FootSteps02_Walk");
}

void Character00_WalkState::Uninit()
{
	CharacterBase_WalkState::Uninit();
}

void Character00_WalkState::Update()
{
	CharacterBase_WalkState::Update();
	
	float BeforeAnimeTime = m_AnimeTime;

	m_AnimeTime = m_AnimeTime + (0.02f * fabsf(m_pController->GetMoveInput().x));
	
	//足が地面に付いたアニメーション時間をまたいでいたら
	const float RightFootTime = 0.456f;
	const float LeftFootTime = 1.050f;

	if (BeforeAnimeTime < RightFootTime && m_AnimeTime >= RightFootTime)
	{
		m_pRightFootStepSE->Play();
	}

	if (BeforeAnimeTime < LeftFootTime && m_AnimeTime >= LeftFootTime)
	{
		m_pLeftFootStepSE->Play();
	}
	
	while(m_AnimeTime > 1.333f)
	{
		m_AnimeTime -= 1.333f;
	}

	m_pModelDrawer->SetAnimeTime(m_AnimeTime);
}