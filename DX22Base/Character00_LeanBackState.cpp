#include "Character_00.h"

void Character_00::LeanBackInit()
{
	Character::LeanBackInit();
	m_FrameCount = 0;
	m_AnimeTime = 0.0f;
	m_CharacterModel.PlayAnime("Damage00", true);
}

void Character_00::LeanBackUninit()
{
	Character::LeanBackUninit();
}

void Character_00::LeanBackUpdate()
{
	Character::LeanBackUpdate();

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
		ChangeState(Character::STATE::IDLE);
	}
}