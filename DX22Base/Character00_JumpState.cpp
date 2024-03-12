#include "Character00_JumpState.h"
#include "SoundManager.h"

void Character00_JumpState::Init()
{
	CharacterBase_JumpState::Init();
	m_pModelDrawer->PlayAnime("Jump", false);

	SoundManager::PlaySE("FootSteps01_Walk");
}

void Character00_JumpState::Uninit()
{
	CharacterBase_JumpState::Uninit();
}

void Character00_JumpState::Update()
{
	CharacterBase_JumpState::Update();

	m_AnimeTime = (1.0f - (m_pCharacterParameter->Velocity.y / m_pJumpParameter->FirstJumpPower)) * 0.93f + 0.15f;

	m_pModelDrawer->SetAnimeTime(m_AnimeTime);
}