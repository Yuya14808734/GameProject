#include "Character_Base.h"

void Character::DeadInit()
{
	m_ChangeStateCount = 0;	//ステータスを変えるまでの時間をカウントする
	m_CharacterStock--;		//ストックを減らす
}

void Character::DeadUninit()
{
	m_ChangeStateCount = 0;
}

void Character::DeadUpdate()
{
	m_ChangeStateCount++;

	if (m_ChangeStateCount > 30)
	{
		if (m_CharacterStock > 0)
		{
			//まだストックがある場合
			ChangeState(Character::STATE::RESPAWN);
		}
		else
		{
			//ストックがない場合
			ChangeState(Character::STATE::GAMEOVER);
		}
	}
}