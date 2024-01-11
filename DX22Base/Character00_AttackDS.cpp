#include "Character00_AttackDS.h"

void Character00_AttackDS::Init()
{
	m_FrameCount = 0;
	m_AnimeTime = 0.375f;

	//当たり判定の作成
	CVector3 ColliderPos = m_pCharacterParameter->Pos + CVector3::GetUp() * (m_pCharacterCollider->GetSize().y * 0.5f);
	float Rotate = 0.0f;

	switch (m_pCharacter->GetLook())
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

	Character::ATTACKPARAM Attack;
	Attack.m_Use = false;
	Attack.m_BoxCollider.CreateBox(BoxCollider::BOXTYPE::CENTER,
		ColliderPos, m_pCharacterParameter->Pos, CVector3(1.7f, 2.7f, 1.0f));
	Attack.m_CanAttackCharacterBit = 0xffffffff;					//当たるキャラクターの設定

	(*m_pAttackCollider).push_back(Attack);

	m_pModelDrawer->PlayAnime("Slide00", true);

	m_PushButton = false;
}

void Character00_AttackDS::Update()
{
	//============<攻撃を当てるかの設定>===================
	//今まで当たったことのあるキャラクターには当てない
	(*m_pAttackCollider)[0].m_CanAttackCharacterBit = ~(*m_pAttackCollider)[0].m_haveHitCharacterBit;
	//=====================================================

	const int AnimeAllFrame = 16;								//アニメーション全体のフレーム
	const int EndFrame = 30;									//攻撃終了時間
	const float AnimeStartTime = 0.375f;						//アニメーション開始時間
	const float AnimeEndTime = 1.417f;							//アニメーション終了時間
	const float AnimeAllTime = AnimeEndTime - AnimeStartTime;	//アニメーションの時間

	m_FrameCount++;

	(*m_pAttackCollider)[0].m_BoxCollider.SetBasePos(m_pCharacterParameter->Pos);

	//アニメーションの再生時間の更新
	m_AnimeTime = static_cast<float>(m_FrameCount) / static_cast<float>(AnimeAllFrame) * AnimeAllTime + AnimeStartTime;

	//アニメーションの再生時間の設定
	m_pModelDrawer->SetAnimeTime(m_AnimeTime);

	m_pCharacterParameter->MoveVector.y = 0.0f;

	switch (m_pCharacter->GetLook())
	{
	case Character::LOOKDIR::RIGHT:
		m_pCharacterParameter->MoveVector.x = m_pMoveParameter->DashSpeed * 0.8f;
		break;
	case Character::LOOKDIR::LEFT:
		m_pCharacterParameter->MoveVector.x = m_pMoveParameter->DashSpeed * -0.8f;
		break;
	}

	m_pCharacterParameter->Pos += m_pCharacterParameter->MoveVector;

	//フレームごとにイベントを設定する
	if (m_FrameCount >= EndFrame)
	{
		m_pCharacter->SetNextState(Character::STATE::State_Idle);
	}
}

void Character00_AttackDS::Uninit()
{
	(*m_pAttackCollider).clear();
}

void Character00_AttackDS::HitCharacter(Character* pHitCharacter)
{

}