#include "Character00_DashState.h"

void Character00_DashState::Init()
{
	CharacterBase_DashState::Init();
	m_pModelDrawer->PlayAnime("Dash", true);
	m_AnimeTime = 0.0f;
}

void Character00_DashState::Uninit()
{
	CharacterBase_DashState::Uninit();
}

void Character00_DashState::Update()
{
	CharacterBase_DashState::Update();

	m_AnimeTime += 0.015f;
	if (m_AnimeTime > 1.0f)
	{
		m_AnimeTime -= 1.0f;
	}

	m_pModelDrawer->SetAnimeLerp(m_AnimeTime);
}