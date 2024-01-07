#include "Character_00.h"

void Character_00::FallDownInit()
{
	Character::FallDownInit();
	m_CharacterModel.PlayAnime("Damage01", true);
	m_FrameCount = 0;
	m_AnimeTime = 0.387f;;
	m_CharacterModel.SetAnimeTime(m_AnimeTime);
	m_CharacterModel.SetRotatePosShift(true);

	//=====<キャラクターの当たり判定の調整>============
	float CharacterHeightHarfSize = m_CharacterCollider.GetSize().y * 0.5f;
	m_CharacterCollider.SetPos(m_pos + CVector3::GetRight() * (CharacterHeightHarfSize
		* (m_NowLookDir == Character::LOOKDIR::RIGHT ? 1.0f : -1.0f)));
	m_CharacterCollider.SetSize(CVector3::GetOne() * CharacterHeightHarfSize);
	//=================================================
}

void Character_00::FallDownUninit()
{
	SetNowLook();
	m_ShiftCenterPos = CVector3::GetZero();
	m_CharacterModel.SetRotatePosShift(false);
	Character::FallDownUninit();

	//=====<キャラクターの当たり判定の初期化>============
	SetDefaultCollider();
	//=================================================
}

void Character_00::FallDownUpdate()
{
	Character::FallDownUpdate();

	const float AnimeEndTime = 0.387f;;		//アニメーションを終わる時間

	m_CharacterModel.SetAnimeTime(AnimeEndTime);

	m_rotate *= CQuaternion::AngleAxis(CVector3::GetForward(),
		m_NowLookDir == Character::LOOKDIR::RIGHT ? 5.0f : -5.0f);
}