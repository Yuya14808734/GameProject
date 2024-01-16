#include "Character00_RespawnState.h"

void Character00_RespawnState::Init()
{
	CharacterBase_RespawnState::Init();

	m_pModelDrawer->PlayAnime("Jump", false);
	m_FrameCount = 0;
}

void Character00_RespawnState::Uninit()
{
	CharacterBase_RespawnState::Uninit();
}

void Character00_RespawnState::Update()
{
	CharacterBase_RespawnState::Update();

	m_FrameCount++;
	m_AnimeTime = sinf(static_cast<float>(m_FrameCount) / 60.0f * 3.14f * 3.0f) * 0.03f + 1.08f;

	m_pModelDrawer->SetAnimeTime(m_AnimeTime);
}