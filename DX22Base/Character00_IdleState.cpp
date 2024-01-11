#include "Character00_IdleState.h"

void Character00_IdleState::Init()
{
	CharacterBase_IdleState::Init();
	m_pModelDrawer->PlayAnime("Idle", true);
	m_AnimeTime = 0.0f;
}

void Character00_IdleState::Uninit()
{
	CharacterBase_IdleState::Uninit();
}

void Character00_IdleState::Update()
{
	CharacterBase_IdleState::Update();

	m_AnimeTime += 0.015f;
	if (m_AnimeTime > 1.0f)
	{
		m_AnimeTime -= 1.0f;
	}

	m_pModelDrawer->SetAnimeLerp(m_AnimeTime);
}