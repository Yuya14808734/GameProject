#include "Character00_LeanBackState.h"

void Character00_LeanBackState::Init()
{
	CharacterBase_LeanBackState::Init();
	m_FrameCount = 0;
	m_AnimeTime = 0.0f;
	m_pModelDrawer->PlayAnime("Damage00", true);
}

void Character00_LeanBackState::Uninit()
{
	CharacterBase_LeanBackState::Uninit();
}

void Character00_LeanBackState::Update()
{
	CharacterBase_LeanBackState::Update();

	const int LeanBackEndFrame = 20;			//アニメーションを停止するフレーム
	const float AnimeStartTime = 0.0f;		//アニメーションの始める時間
	const float AnimeEndTime = 1.167f;		//アニメーションを終わる時間
	const float AnimeAllTime = AnimeEndTime - AnimeStartTime;	//アニメーションの時間

	m_FrameCount++;

	m_AnimeTime = AnimeAllTime * (static_cast<float>(m_FrameCount) / static_cast<float>(LeanBackEndFrame)) + AnimeStartTime;

	//アニメーション
	if (m_AnimeTime > AnimeEndTime)
	{
		m_AnimeTime = AnimeEndTime;
		m_pCharacter->SetNextState(Character::STATE::State_Idle);
	}
}