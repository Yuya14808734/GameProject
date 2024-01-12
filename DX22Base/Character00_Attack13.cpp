#include "Character00_Attack13.h"
#include "CharacterBase_HitStopState.h"

void Character00_Attack13::Init()
{
	m_FrameCount = 0;
	m_AnimeTime = 0.935f;

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
		ColliderPos, CVector3(1.7f, 2.7f, 1.0f));
	Attack.m_CanAttackCharacterBit = 0xffffffff;					//当たるキャラクターの設定


	(*m_pAttackCollider).push_back(Attack);

	m_pModelDrawer->PlayAnime("WAIT04", true);
}

void Character00_Attack13::Update()
{
	//============<攻撃を当てるかの設定>===================
	//今まで当たったことのあるキャラクターには当てない
	(*m_pAttackCollider)[0].m_CanAttackCharacterBit = ~(*m_pAttackCollider)[0].m_haveHitCharacterBit;
	//=====================================================

	const int AnimeEndFrame = 30;			//アニメーションを停止するフレーム
	const int EndFrame = 30;				//このアタックが終わるフレーム
	const float AnimeStartTime = 0.935f;	//アニメーションの始める時間
	const float AnimeEndTime = 2.069f;		//アニメーションを終わる時間
	const float AnimeAllTime = AnimeEndTime - AnimeStartTime;	//アニメーションの時間

	m_FrameCount++;
	m_AnimeTime = static_cast<float>(m_FrameCount) / static_cast<float>(AnimeEndFrame) * AnimeAllTime + AnimeStartTime;

	if (m_AnimeTime > AnimeEndTime)
	{
		m_AnimeTime = AnimeEndTime;
	}

	if (m_FrameCount == 8)
	{
		(*m_pAttackCollider)[0].m_Use = true;
	}

	if (m_FrameCount == 12)
	{
		(*m_pAttackCollider)[0].m_Use = false;
	}

	//フレームごとにイベントを設定する
	if (m_FrameCount >= EndFrame)
	{
		m_pCharacter->SetNextState(Character::STATE::State_Idle);
	}

	m_pModelDrawer->SetAnimeTime(m_AnimeTime);
}

void Character00_Attack13::Uninit()
{
	m_pAttackCollider->clear();
}

void Character00_Attack13::HitCharacter(Character* pHitCharacter)
{
	pHitCharacter->AddDamage(5.0f);								//ダメージの加算
	float ForcePower = (pHitCharacter->GetDamage() / 100.0f) * 0.5f + 0.3f;			//ダメージから吹っ飛ばすベクトルの計算

	CVector3 AddVec = CVector2::GetAngleVector(
		m_pCharacter->GetLook() == Character::LOOKDIR::RIGHT ? -70.0f : 70.0f
	) * ForcePower;
	pHitCharacter->AddForce(AddVec);
	CharacterBase_HitStopState* pHitStopState =
		static_cast<CharacterBase_HitStopState*>(pHitCharacter->SetNextState(Character::STATE::State_HitStop));
	pHitCharacter->ChangeNextState();
	pHitStopState->SetHitStop(5, Character::STATE::State_BlowAway, true);	//ヒットストップの設定
	if (m_pCharacter->GetLook() == Character::LOOKDIR::RIGHT)
	{
		pHitCharacter->SetLookLeft();
	}
	else
	{
		pHitCharacter->SetLookRight();
	}
}
