#include "Character_00.h"

void Character_00::AirMoveInit()
{
	Character::AirMoveInit();

	if (m_NowState == Character::STATE::WALK ||
		m_NowState == Character::STATE::DASH ||
		m_NowState == Character::STATE::IDLE ||
		m_NowAttack == Character::ATTACK::ATTACK_AIRN)
	{
		m_CharacterModel.PlayAnime("Jump", false);
	}
}

void Character_00::AirMoveUninit()
{
	Character::AirMoveUninit();
}

void Character_00::AirMoveUpdate()
{
	Character::AirMoveUpdate();

	m_AnimeTime = sinf(static_cast<float>(m_FrameCount) / 60.0f * 3.14f * 3.0f) * 0.03f + 1.08f;

	m_CharacterModel.SetAnimeTime(m_AnimeTime);

}