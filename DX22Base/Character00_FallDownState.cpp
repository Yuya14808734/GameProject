#include "Character00_FallDownState.h"

void Character00_FallDownState::Init()
{
	CharacterBase_FallDownState::Init();
	m_pModelDrawer->PlayAnime("Damage01", true);
	m_FrameCount = 0;
	m_AnimeTime = 0.387f;;
	m_pModelDrawer->SetAnimeTime(m_AnimeTime);
	m_pModelDrawer->SetRotatePosShift(true);

	//=====<キャラクターの当たり判定の調整>============
	BoxCollider * pCollider = m_pCharacter->GetCharacterCollider();
	float ColliderSize = pCollider->GetSize().y * 0.75f;
	pCollider->SetSize(CVector3::GetOne() * ColliderSize);
	pCollider->SetShiftVec(CVector3(0.0f, -0.5f, 0.0f));
	//=================================================
}

void Character00_FallDownState::Uninit()
{
	m_pCharacter->SetNowLook();
	m_pModelDrawer->SetRotatePosShiftVector(CVector3::GetZero());
	m_pModelDrawer->SetRotatePosShift(false);
	CharacterBase_FallDownState::Uninit();

	//=====<キャラクターの当たり判定の初期化>============
	m_pCharacter->SetDefaultCollider();
	//=================================================
}

void Character00_FallDownState::Update()
{
	CharacterBase_FallDownState::Update();

	const float AnimeEndTime = 0.387f;;		//アニメーションを終わる時間

	m_pModelDrawer->SetAnimeTime(AnimeEndTime);

	m_pCharacterParameter->Rotate *= CQuaternion::AngleAxis(CVector3::GetForward(),
		m_pCharacter->GetLook() == Character::LOOKDIR::RIGHT ? 5.0f : -5.0f);
}