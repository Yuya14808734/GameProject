#include "Character00_StartAnimation.h"
#include "CameraManager.h"

void Character00_StartAnimationState::Init()
{
	InitAnime("WAIT01");
	m_NowAnimeState = Character00_StartAnimationState::AnimationState::Start;

	m_pCharacter->SetLookFront();

}

void Character00_StartAnimationState::Uninit()
{
	LookStageCenter();
}

void Character00_StartAnimationState::Update()
{
	switch(m_NowAnimeState)
	{
	case Character00_StartAnimationState::AnimationState::Start:
		StartAnimeUpdate();
		break;
	case Character00_StartAnimationState::AnimationState::Idle:
		IdleAnimeUpdate();
		break;
	}
}

void Character00_StartAnimationState::StartAnimeUpdate()
{
	const float AnimeEndTime = 6.625f;
	const float AnimePlayEndTime = 2.0f;

	m_FrameCount++;

	float AnimeNowTime = static_cast<float>(m_FrameCount) / 60.0f;

	float AnimeTime = AnimeNowTime / AnimePlayEndTime * AnimeEndTime;

	if (AnimeTime > AnimeEndTime)
	{
		AnimeTime = AnimeEndTime;
		m_NowAnimeState = Character00_StartAnimationState::AnimationState::Idle; 
		LookStageCenter();
		InitAnime("Idle");
	}
	
	m_pModelDrawer->SetAnimeTime(AnimeTime);
}

void Character00_StartAnimationState::IdleAnimeUpdate()
{
	m_FrameCount++;

	if (m_FrameCount == 60)
	{
		m_FrameCount = 0;
	}

	float AnimeTime = static_cast<float>(m_FrameCount) / 60.0f;

	m_pModelDrawer->SetAnimeTime(AnimeTime);
}

void Character00_StartAnimationState::InitAnime(const std::string& AnimeName)
{
	m_pModelDrawer->PlayAnime(AnimeName, true);
	m_FrameCount = 0;
}

void Character00_StartAnimationState::LookStageCenter()
{
	CameraBase* pCamera = CameraManager::GetInstance().GetSceneCamera();

	//カメラより右にいたら左、左にいたら右を向かせる
	if (pCamera != nullptr)
	{
		bool Right =
			(m_pCharacterParameter->Pos.x -	pCamera->GetPos().x	> 0.0f);

		if (Right)
		{
			//キャラクターが右にいる
			m_pCharacter->SetLookLeft();
		}
		else
		{
			//キャラクターが左にいる
			m_pCharacter->SetLookRight();
		}
	}
}
