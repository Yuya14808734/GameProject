#include "Character_00.h"

void Character_00::DownInit()
{
	Character::DownInit();

	m_CharacterModel.PlayAnime("Damage01", true);
	m_AnimeTime = 0.394f;
	m_FrameCount = 0;
	m_Invincible = true;
}

void Character_00::DownUninit()
{
	Character::DownUninit();
}

void Character_00::DownUpdate()
{
	Character::DownUpdate();

	const int AnimeEndFrame = 20;			//アニメーションを停止するフレーム
	const float AnimeStartTime = 0.394f;		//アニメーションの始める時間
	const float AnimeEndTime = 1.461f;		//アニメーションを終わる時間
	const float AnimeAllTime = AnimeEndTime - AnimeStartTime;	//アニメーションの時間

	m_FrameCount++;

	m_AnimeTime = static_cast<float>(m_FrameCount) / static_cast<float>(AnimeEndFrame) * AnimeAllTime + AnimeStartTime;

	//アニメーションが終了したら待機状態にする
	if (m_AnimeTime > AnimeEndTime)
	{
		m_AnimeTime = AnimeEndTime;

		//転んでいるときに上ボタンを押すと起き上がる
		if (m_Controller.GetWakeUp())
		{
			ChangeState(Character::STATE::WAKEUP);
		}
	}

	//アニメーションが終了してある程度時間がたったら無敵を外す
	if (m_FrameCount > AnimeEndFrame + 30)
	{
		m_Invincible = false;
	}

	m_CharacterModel.SetAnimeTime(m_AnimeTime);
}