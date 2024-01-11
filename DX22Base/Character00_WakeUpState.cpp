#include "Character00_WakeUpState.h"

void Character00_WakeUpState::Init()
{
	CharacterBase_WakeUpState::Init();

	m_pModelDrawer->PlayAnime("Damage01", true);
	m_AnimeTime = 2.082f;
	m_FrameCount = 0;
	m_pCharacter->SetInvincible(true);
}

void Character00_WakeUpState::Uninit()
{
	CharacterBase_WakeUpState::Uninit();
	m_pCharacter->SetInvincible(false);
}

void Character00_WakeUpState::Update()
{
	CharacterBase_WakeUpState::Update();

	const float AnimeEndFrame = 20.0f;			//アニメーションを停止するフレーム
	const float AnimeStartTime = 2.082f;		//アニメーションの始める時間
	const float AnimeEndTime = 3.6f;		//アニメーションを終わる時間
	const float AnimeAllTime = AnimeEndTime - AnimeStartTime;	//アニメーションの時間

	m_FrameCount++;

	m_AnimeTime = static_cast<float>(m_FrameCount) / AnimeEndFrame * AnimeAllTime + AnimeStartTime;


	//起き上がるアニメーションが終了したら待機状態にする
	if (m_AnimeTime > AnimeEndTime)
	{
		m_AnimeTime = AnimeEndTime;
		m_pCharacter->SetNextState(Character::STATE::State_Idle);
	}

	m_pModelDrawer->SetAnimeTime(m_AnimeTime);
}