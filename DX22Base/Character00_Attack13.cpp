#include "Character_00.h"

void Character_00::Attack13_Init()
{
	m_AttackTime = 0;
	m_AnimeTime = 0.935f;

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
		ColliderPos, CVector3(1.7f, 2.7f, 1.0f));
	Attack.m_CanAttackCharacterBit = 0xffffffff;					//当たるキャラクターの設定


	m_AttackCollider.push_back(Attack);

	m_CharacterModel.PlayAnime("WAIT04", true);
}

void Character_00::Attack13_Update()
{
	//============<攻撃を当てるかの設定>===================
	//今まで当たったことのあるキャラクターには当てない
	m_AttackCollider[0].m_CanAttackCharacterBit = ~m_AttackCollider[0].m_haveHitCharacterBit;
	//=====================================================

	const int AnimeEndFrame = 30;			//アニメーションを停止するフレーム
	const int EndFrame = 30;				//このアタックが終わるフレーム
	const float AnimeStartTime = 0.935f;	//アニメーションの始める時間
	const float AnimeEndTime = 2.069f;		//アニメーションを終わる時間
	const float AnimeAllTime = AnimeEndTime - AnimeStartTime;	//アニメーションの時間

	m_AttackTime++;
	m_AnimeTime = static_cast<float>(m_AttackTime) / static_cast<float>(AnimeEndFrame) * AnimeAllTime + AnimeStartTime;

	if (m_AnimeTime > AnimeEndTime)
	{
		m_AnimeTime = AnimeEndTime;
	}

	if (m_AttackTime == 8)
	{
		m_AttackCollider[0].m_Use = true;
	}

	if (m_AttackTime == 12)
	{
		m_AttackCollider[0].m_Use = false;
	}

	//フレームごとにイベントを設定する
	if (m_AttackTime >= EndFrame)
	{
		ChangeState(Character::STATE::IDLE);
	}

	m_CharacterModel.SetAnimeTime(m_AnimeTime);
}

void Character_00::Attack13_Uninit()
{
	m_AttackCollider.clear();
}

void Character_00::Attack13_Hit(Character* HitCharacter)
{
	HitCharacter->AddDamage(5.0f);								//ダメージの加算
	float ForcePower = (HitCharacter->GetDamage() / 100.0f) * 0.5f + 0.3f;			//ダメージから吹っ飛ばすベクトルの計算

	CVector3 AddVec = CVector2::GetAngleVector(
		m_NowLookDir == Character::LOOKDIR::RIGHT ? -70.0f : 70.0f
	) * ForcePower;
	HitCharacter->AddForce(AddVec); 
	HitCharacter->SetHitStop(5, Character::STATE::BLOWAWAY);
	HitCharacter->SetShake(true);
	if (m_NowLookDir == Character::LOOKDIR::RIGHT)
	{
		HitCharacter->SetLookLeft();
	}
	else
	{
		HitCharacter->SetLookRight();
	}
}
