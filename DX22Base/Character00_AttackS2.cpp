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

	ATTACKPARAM Attack;												//攻撃パラメーターの設定
	Attack.m_Use = false;											//攻撃当たり判定するか
	Attack.m_BoxCollider.CreateBox(BoxCollider::BOXTYPE::CENTER,	//当たり判定の範囲設定
		ColliderPos	, CVector3(1.7f, 2.7f, 1.0f));
	Attack.m_CanAttackCharacterBit = 0xffffffff;					//当たるキャラクターの設定

	m_AttackCollider.push_back(Attack);

	m_SwordHandle = EffectManager::GetManager()->Play(EffectManager::GetEffect("C00_S2"),0,0,0);
	EffectManager::GetManager()->SetLocation(m_SwordHandle, { ColliderPos.x,ColliderPos.y,ColliderPos.z });
	EffectManager::GetManager()->SetScale(m_SwordHandle, 1.0f,1.0f,1.0f);
	EffectManager::GetManager()->SetRotation(m_SwordHandle, 
		0.0f,
		Rotate
		,0.0f);

	m_CharacterModel.PlayAnime("Umatobi", true);

	m_HitAttackStopCount = 0;
}

void Character_00::AttackS2_Uninit()
{
	m_HitAttackStopCount = 0;

	EffectManager::GetManager()->StopEffect(m_SwordHandle);

	m_AttackCollider.clear();
}

void Character_00::AttackS2_Update()
{
	//============<攻撃を当てるかの設定>====================================
	
	//今まで当たったことのあるキャラクターには当てない
	m_AttackCollider[0].m_CanAttackCharacterBit = ~m_AttackCollider[0].m_haveHitCharacterBit;

	//前のフレームで誰かに当たった場合
	if (m_AttackCollider[0].m_HitTriggerCharacterBit != 0x00)
	{
		m_HitAttackStopCount = 30;
		EffectManager::GetManager()->SetPaused(m_SwordHandle, true);
	}

	//攻撃を当てたヒットストップが終わるまで動かない
	if (m_HitAttackStopCount > 0)
	{
		m_HitAttackStopCount--;

		//攻撃が当たった時のストップが消える
		if (m_HitAttackStopCount == 0)
		{
			EffectManager::GetManager()->SetPaused(m_SwordHandle, false);
		}

		return;
	}

	//======================================================================

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

void Character_00::AttackS2_Hit(Character* HitCharacter)
{
	HitCharacter->AddDamage(13.0f);											//ダメージの加算

	float ForcePower = (HitCharacter->GetDamage() / 100.0f) + 0.7f;			//ダメージから吹っ飛ばすベクトルの計算
	CVector3 AddVec = CVector2::GetAngleVector(
		m_NowLookDir == Character::LOOKDIR::RIGHT ? -70.0f : 70.0f
	) * ForcePower;
	HitCharacter->AddForce(AddVec);
	HitCharacter->SetHitStop(30,Character::STATE::BLOWAWAY);
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
