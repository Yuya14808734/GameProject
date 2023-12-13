#include "Character_00.h"

void Character_00::AttackS2_Init()
{
	m_AttackTime = 0;
	m_AnimeTime = 0.332f;

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

	AttackParam Attack;
	Attack.m_Use = false;
	Attack.m_BoxCollider.CreateBox(BoxCollider::BOXTYPE::CENTER, 
		ColliderPos	, CVector3(1.7f, 2.7f, 1.0f));

	m_AttackCollider.push_back(Attack);

	m_SwordHandle = EffectManager::GetManager()->Play(EffectManager::GetEffect("C00_S2"),0,0,0);
	EffectManager::GetManager()->SetLocation(m_SwordHandle, { ColliderPos.x,ColliderPos.y,ColliderPos.z });
	EffectManager::GetManager()->SetScale(m_SwordHandle, 1.0f,1.0f,1.0f);
	EffectManager::GetManager()->SetRotation(m_SwordHandle, 
		0.0f,
		Rotate
		,0.0f);

	m_CharacterModel.PlayAnime("Umatobi", true);
}

void Character_00::AttackS2_Update()
{
	m_AttackTime++;
	float AnimeAllTime = 0.938f - 0.332f;
	m_AnimeTime = static_cast<float>(m_AttackTime) / 24.0f  * AnimeAllTime + 0.332f;

	if (m_AttackTime == 6)
	{
		m_AttackCollider[0].m_Use = true;
	}

	if (m_AttackTime == 16)
	{
		m_AttackCollider[0].m_Use = false;
	}

	//フレームごとにイベントを設定する
	if(m_AttackTime >= 24)
	{
		ChangeState(Character::STATE::IDLE);
	}

	if (m_AnimeTime > 0.938f)
	{
		m_AnimeTime = 0.938f;
	}

	m_CharacterModel.SetAnimeTime(m_AnimeTime);
}

void Character_00::AttackS2_Uninit()
{
	EffectManager::GetManager()->StopEffect(m_SwordHandle);

	m_AttackCollider.clear();
}

void Character_00::AttackS2_Hit(Character* HitCharacter)
{
	HitCharacter->AddDamage(13.0f);											//ダメージの加算

	float ForcePower = HitCharacter->GetDamage() / 100.0f * 10.0f;			//ダメージから吹っ飛ばすベクトルの計算
	CVector3 AddVec = CVector2::GetAngleVector(
		m_NowLookDir == Character::LOOKDIR::RIGHT ? 60.0f : -60.0f
	) * ForcePower;
	HitCharacter->AddForce(AddVec);
}
