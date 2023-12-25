#include "Character_00.h"

void Character_00::FallDownInit()
{
	Character::FallDownInit();
	m_CharacterModel.PlayAnime("Damage01", true);
	m_FrameCount = 0;
	m_AnimeTime = 0.387f;;
	m_CharacterModel.SetAnimeTime(m_AnimeTime);
	m_CharacterModel.SetRotatePosShift(true);
}

void Character_00::FallDownUninit()
{
	m_rotate.SetQuaternion(0.0f,0.0f,0.0f,1.0f);
	m_ShiftCenterPos = CVector3::GetZero();
	m_CharacterModel.SetRotatePosShift(false);
	Character::FallDownUninit();
}

void Character_00::FallDownUpdate()
{
	Character::FallDownUpdate();

	const float AnimeEndTime = 0.387f;;		//アニメーションを終わる時間

	m_CharacterModel.SetAnimeTime(AnimeEndTime);

	m_rotate *= CQuaternion::AngleAxis(CVector3::GetForward(),
		m_NowLookDir == Character::LOOKDIR::RIGHT ? 5.0f : -5.0f);
}