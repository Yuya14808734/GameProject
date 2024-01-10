#include "Character_00.h"

void Character_00::AttackSD_Init()
{
	m_FrameCount = 0;
	m_AnimeTime = 0.375f;

	//当たり判定の作成
	CVector3 ColliderPos = m_pos + CVector3::GetUp() * (m_CharacterCollider.GetSize().y * 0.5f);
	float Rotate = 0.0f;

	switch (m_NowLookDir)
	{
	case Character::LOOKDIR::RIGHT:
		ColliderPos = ColliderPos + CVector3::GetRight() * 1.5f;
		Rotate = 3.14f;
		break;
	case Character::LOOKDIR::LEFT:
		ColliderPos = ColliderPos + CVector3::GetRight() * -1.5f;
		Rotate = 0.0f;
		break;
	default:
		break;
	}

	ATTACKPARAM Attack;
	Attack.m_Use = false;
	Attack.m_BoxCollider.CreateBox(BoxCollider::BOXTYPE::CENTER,
		ColliderPos, m_pos , CVector3(1.7f, 2.7f, 1.0f));
	Attack.m_CanAttackCharacterBit = 0xffffffff;					//当たるキャラクターの設定

	m_AttackCollider.push_back(Attack);

	m_CharacterModel.PlayAnime("Slide00", true);

	m_PushButton = false;
}

void Character_00::AttackSD_Update()
{
	//============<攻撃を当てるかの設定>===================
	//今まで当たったことのあるキャラクターには当てない
	m_AttackCollider[0].m_CanAttackCharacterBit = ~m_AttackCollider[0].m_haveHitCharacterBit;
	//=====================================================

	const int AnimeAllFrame = 16;								//アニメーション全体のフレーム
	const int EndFrame = 30;									//攻撃終了時間
	const float AnimeStartTime = 0.375f;						//アニメーション開始時間
	const float AnimeEndTime = 1.417f;							//アニメーション終了時間
	const float AnimeAllTime = AnimeEndTime - AnimeStartTime;	//アニメーションの時間

	m_FrameCount++;

	m_AttackCollider[0].m_BoxCollider.SetBasePos(m_pos);

	//アニメーションの再生時間の更新
	m_AnimeTime = static_cast<float>(m_FrameCount) / static_cast<float>(AnimeAllFrame) * AnimeAllTime + AnimeStartTime;

	//アニメーションの再生時間の設定
	m_CharacterModel.SetAnimeTime(m_AnimeTime);

	m_MoveVector.y = 0.0f;

	switch (m_NowLookDir)
	{
	case Character::LOOKDIR::RIGHT:
		m_MoveVector.x = m_MoveParameter.m_DashSpeed * 0.8f;
		break;
	case Character::LOOKDIR::LEFT:
		m_MoveVector.x = m_MoveParameter.m_DashSpeed * -0.8f;
		break;
	}

	m_pos += m_MoveVector;

	//フレームごとにイベントを設定する
	if (m_FrameCount >= EndFrame)
	{
		ChangeState(Character::STATE::IDLE);
	}
}

void Character_00::AttackSD_Uninit()
{
	m_AttackCollider.clear();
}

void Character_00::AttackSD_Hit(Character* HitCharacter)
{

}