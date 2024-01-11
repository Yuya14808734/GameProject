#include "Character00_JumpInState.h"

void Character00_JumpInState::Init()
{
	CharacterBase_JumpInState::Init();
	m_pModelDrawer->PlayAnime("Jump", false);
	m_AnimeTime = 0.0f;
}

void Character00_JumpInState::Uninit()
{
	CharacterBase_JumpInState::Uninit();
}

void Character00_JumpInState::Update()
{
	CharacterBase_JumpInState::Update();
	m_AnimeTime = (static_cast<float>(m_pCharacterParameter->JumpCharageCount) / 3.0f) * 0.05f + 0.1f;

	m_pModelDrawer->SetAnimeTime(m_AnimeTime);
}


