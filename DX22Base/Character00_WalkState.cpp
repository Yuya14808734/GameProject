#include "Character00_WalkState.h"

void Character00_WalkState::Init()
{
	CharacterBase_WalkState::Init();
	m_pModelDrawer->PlayAnime("Walk", true);
	m_AnimeTime = 0.0f;
}

void Character00_WalkState::Uninit()
{
	CharacterBase_WalkState::Uninit();
}

void Character00_WalkState::Update()
{
	CharacterBase_WalkState::Update();

	m_AnimeTime = m_AnimeTime + (0.015f * fabsf(m_pController->GetMoveInput().x));
	if (m_AnimeTime > 1.0f)
	{
		m_AnimeTime -= 1.0f;
	}

	m_pModelDrawer->SetAnimeLerp(m_AnimeTime);
}