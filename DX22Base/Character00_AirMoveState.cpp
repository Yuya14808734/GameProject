#include "Character00_AirMoveState.h"

void Character00_AirMoveState::Init()
{
	CharacterBase_AirMoveState::Init();

	//Ç‚ÇÈÇ»ÇÁTypeyeld
	/*if (m_NowState == Character::STATE::WALK ||
		m_NowState == Character::STATE::DASH ||
		m_NowState == Character::STATE::IDLE ||
		m_NowAttack == Character::ATTACK::ATTACK_AIRN)
	{
		m_CharacterModel.PlayAnime("Jump", false);
	}*/
}

void Character00_AirMoveState::Uninit()
{
	CharacterBase_AirMoveState::Uninit();
}

void Character00_AirMoveState::Update()
{
	Character00_AirMoveState::Update();

	m_AnimeTime = sinf(static_cast<float>(m_FrameCount) / 60.0f * 3.14f * 3.0f) * 0.03f + 1.08f;

	m_pModelDrawer->SetAnimeTime(m_AnimeTime);

}