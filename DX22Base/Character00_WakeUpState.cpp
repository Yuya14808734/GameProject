#include "Character_00.h"

void Character_00::WakeUpInit()
{
	Character::WakeUpInit();

	m_CharacterModel.PlayAnime("Damage01", true);
	m_AnimeTime = 2.082f;
	m_FrameCount = 0;
	m_Invincible = true;
}

void Character_00::WakeUpUninit()
{
	Character::WakeUpUninit();
	m_Invincible = false;
}

void Character_00::WakeUpUpdate()
{
	Character::WakeUpUpdate();

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
		ChangeState(Character::STATE::IDLE);
	}

	m_CharacterModel.SetAnimeTime(m_AnimeTime);
}