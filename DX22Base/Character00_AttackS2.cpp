#include "Character00_AttackS2.h"
#include "CharacterBase_HitStopState.h"

void Character00_AttackS2::Init()
{
	m_FrameCount = 0;
	m_AnimeTime = 0.332f;

	//当たり判定の作成
	const float DirectValue = m_pCharacter->GetLook() == Character::LOOKDIR::RIGHT ?
		1.0f: -1.0f;
	CVector3 ColliderBasePos = m_pCharacterParameter->Pos;
	ColliderBasePos.x = ColliderBasePos.x;
	ColliderBasePos.y = ColliderBasePos.y + (m_pCharacterCollider->GetSize().y * 0.6f);
	ColliderBasePos.z = ColliderBasePos.z;
	CVector3 ColliderSplitSize = CVector3(1.0f, 1.0f, 1.0f);
	const int StartAngle = 20;
	const int EndAngle = 200;
	const int RotateAngle = 30;
	const float Radius = 1.7f;

	for(int Angle = StartAngle;Angle <= EndAngle; Angle += RotateAngle)
	{
		float Radian = DirectX::XMConvertToRadians(static_cast<float>(Angle));

		//当たり判定の位置を設定
			CVector3 ColliderSplitPos = CVector3(
				sinf(Radian * DirectValue),
				cosf(Radian * DirectValue),
				0.0f) * Radius;

		Character::ATTACKPARAM Attack;
		Attack.m_Use = false; 
		Attack.m_BoxCollider.CreateBox(BoxCollider::BOXTYPE::CENTER,
			ColliderBasePos, ColliderSplitSize, ColliderSplitPos);
		Attack.m_CanAttackCharacterBit = 0xffffffff;					//当たるキャラクターの設定
		m_pAttackCollider->push_back(Attack);
	};	

	m_SwordHandle = EffectManager::GetManager()->Play(EffectManager::GetEffect("C00_S2"),0,0,0);
	EffectManager::GetManager()->SetLocation(m_SwordHandle, 
		{ m_pCharacterParameter->Pos.x + (1.5f * DirectValue),
		m_pCharacterParameter->Pos.y + (m_pCharacterCollider->GetSize().y * 0.5f),
		m_pCharacterParameter->Pos.z });
	EffectManager::GetManager()->SetScale(m_SwordHandle, 1.0f,1.0f,1.0f);
	EffectManager::GetManager()->SetRotation(m_SwordHandle, 
		0.0f,
		(m_pCharacter->GetLook() == Character::LOOKDIR::RIGHT ?
			3.14f : 0.0f)
		,0.0f);

	m_pModelDrawer->PlayAnime("Umatobi", true);

	m_HitAttackStopCount = 0;
}

void Character00_AttackS2::Uninit()
{
	EffectManager::GetManager()->StopEffect(m_SwordHandle);

	m_pAttackCollider->clear();
}

void Character00_AttackS2::Update()
{
	//地面に当たっていないと浮遊状態に変える
	/*if (!m_pCharacterParameter->HitGround)
	{
		m_pCharacter->SetNextState(Character::STATE::State_AirMove);
	}*/

	//============<攻撃を当てるかの設定>====================================
	//今まで当たったことのあるキャラクター
	unsigned int OldHitCharacterBit = 0x00;
	//前のフレームで誰かに当たっていたら
	unsigned int HitTriggerCharacterBit = 0x00;

	for (Character::ATTACKPARAM& copy : (*m_pAttackCollider))
	{
		OldHitCharacterBit |= copy.m_haveHitCharacterBit;
		HitTriggerCharacterBit |= copy.m_HitTriggerCharacterBit;
	}

	//上で求めたBitをコピー
	for (Character::ATTACKPARAM& copy : (*m_pAttackCollider))
	{
		//今まで当たったことのあるキャラクターを設定
		copy.m_haveHitCharacterBit = OldHitCharacterBit;
		//前のフレームで始めて当たったキャラクターを設定
		copy.m_HitTriggerCharacterBit = HitTriggerCharacterBit;
		//次のフレームで当てることが出来るキャラクターを設定
		copy.m_CanAttackCharacterBit = ~copy.m_haveHitCharacterBit;
		//下で使っている攻撃を設定するのでここで使わないように設定
		copy.m_Use = false;
	}

	//============<攻撃を当てた後にヒットストップを行うか>========
	//前のフレームで誰かに当たった場合
	if (HitTriggerCharacterBit != 0x00)
	{
		m_HitAttackStopCount = m_HitStopFrame;
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

	//============<アニメーションの時間を設定>==============================
	const int AnimeFrame = 24;
	const int EndFrame = 24;
	const float AnimeStartTime = 0.332f;
	const float AnimeEndTime = 0.938f;
	const float AnimeAllTime = AnimeEndTime - AnimeStartTime;

	m_FrameCount++;

	//このステートが終わったら
	if (m_FrameCount >= EndFrame)
	{
		m_pCharacter->SetNextState(Character::STATE::State_Idle);
	}

	m_AnimeTime = static_cast<float>(m_FrameCount) / static_cast<float>(AnimeFrame) * AnimeAllTime + AnimeStartTime;

	if (m_AnimeTime > AnimeEndTime)
	{
		m_AnimeTime = AnimeEndTime;
	}
	m_pModelDrawer->SetAnimeTime(m_AnimeTime);
	//======================================================================

	//============<剣の位置によって攻撃の位置を設定>=======
	const int AttackStartFrame = 2;
	const int AttackEndFrame = 16;
	const int AttackAllFrame = AttackEndFrame - AttackStartFrame;

	int AttackFrame = m_FrameCount - AttackStartFrame;
	int AttackNum = AttackFrame / (AttackAllFrame / static_cast<float>(m_pAttackCollider->size()));

	if (AttackNum >= 0 && AttackNum < static_cast<float>(m_pAttackCollider->size()))
	{
		(*m_pAttackCollider)[AttackNum].m_Use = true;
	}
	//=====================================================
}

void Character00_AttackS2::HitCharacter(Character* pHitCharacter)
{
	//ダメージの加算
	pHitCharacter->AddDamage(13.0f);

	//少し上げて地面に当たっていないことにする
	pHitCharacter->SetPos(pHitCharacter->GetPos() + CVector3::GetUp() * 0.1f);
	
	//ダメージから吹っ飛ばすベクトルの計算
	float ForcePower = (pHitCharacter->GetDamage() / 100.0f) + 0.7f;			
	CVector3 AddVec = CVector2::GetAngleVector(
		m_pCharacter->GetLook() == Character::LOOKDIR::RIGHT ? -70.0f : 70.0f
	) * ForcePower;

	//吹っ飛ばすベクトルを設定
	pHitCharacter->AddForce(AddVec);

	//ヒットストップの設定
	CharacterBase_HitStopState* pHitStopState =
		static_cast<CharacterBase_HitStopState*>(pHitCharacter->SetNextState(Character::STATE::State_HitStop));
	pHitCharacter->ChangeNextState();
	pHitStopState->SetHitStop(m_HitStopFrame, Character::STATE::State_BlowAway, true);	//ヒットストップの設定
	m_HitAttackStopCount = m_HitStopFrame;

	//キャラクターの向きを変える
	if(m_pCharacter->GetLook() == Character::LOOKDIR::RIGHT)
	{
		pHitCharacter->SetLookLeft();
	}
	else
	{
		pHitCharacter->SetLookRight();
	}
}
