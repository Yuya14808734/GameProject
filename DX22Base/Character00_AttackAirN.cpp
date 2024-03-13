#include "Character00_AttackAirN.h"
#include "Input.h"
#include "XboxKeyboard.h"
#include "CharacterBase_HitStopState.h"
#include "SoundManager.h"
#include "Scene00_Game.h"

void Character00_AttackAirN::Init()
{
	m_FrameCount = 0;
	m_AnimeTime = 0.935f;
	m_HitAttackStopCount = 0;

	//当たり判定の作成
	CVector3 ColliderBasePos = m_pCharacterParameter->Pos;
	CVector3 ColliderSplitSize = CVector3(3.5f * 0.5f, 4.0f * 0.5f, 1.0f);
	CVector3 ColliderSplitPos[4] =
	{
		CVector3(ColliderSplitSize.x * -0.5f,ColliderSplitSize.y *  0.5f, 0.0f),	//左上
		CVector3(ColliderSplitSize.x * -0.5f,ColliderSplitSize.y * -0.5f, 0.0f),	//左下
		CVector3(ColliderSplitSize.x *  0.5f,ColliderSplitSize.y * -0.5f, 0.0f),	//右下
		CVector3(ColliderSplitSize.x *  0.5f,ColliderSplitSize.y *  0.5f, 0.0f),	//右上
	};

	//攻撃の当たり判定を生成
	Character::ATTACKPARAM Attack;

	for (int i = 0; i < 4; i++)
	{
		Attack.m_Use = false;
		Attack.m_BoxCollider.CreateBox(BoxCollider::BOXTYPE::CENTER,
			ColliderBasePos, ColliderSplitSize, ColliderSplitPos[i] + CVector3(0.0f,1.0f,0.0f));
		Attack.m_CanAttackCharacterBit = 0xffffffff;					//当たるキャラクターの設定
		m_pAttackCollider->push_back(Attack);
	}

	m_efkHnd_Sword = EffectManager::GetManager()->Play(EffectManager::GetEffect("C00_AirN"), 0, 0, 0);
	EffectManager::GetManager()->SetLocation(m_efkHnd_Sword,
		{ ColliderBasePos.x, ColliderBasePos.y + 1.0f, ColliderBasePos.z + 0.3f });
	EffectManager::GetManager()->SetScale(m_efkHnd_Sword, 1.0f, 1.0f, 1.0f);

	m_pModelDrawer->PlayAnime("WAIT04", true);

	//m_pCharacterParameter->MoveVector = CVector3::GetZero();
}

void Character00_AttackAirN::Uninit()
{
	EffectManager::GetManager()->StopEffect(m_efkHnd_Sword);
	(*m_pAttackCollider).clear();
	m_pCharacter->SetDefaultCollider();
}

void Character00_AttackAirN::Update()
{
	//地面に当たるとアイドル状態に変える
	if (m_pCharacterParameter->HitGround)
	{
		m_pCharacter->SetNextState(Character::STATE::State_Idle);
	}

	//============<攻撃を当てるかの設定>===================
	//今まで当たったことのあるキャラクター
	unsigned int OldHitCharacterBit =
		(*m_pAttackCollider)[0].m_haveHitCharacterBit |
		(*m_pAttackCollider)[1].m_haveHitCharacterBit |
		(*m_pAttackCollider)[2].m_haveHitCharacterBit |
		(*m_pAttackCollider)[3].m_haveHitCharacterBit;

	//前のフレームで誰かに当たっていたら
	unsigned int HitTriggerCharacterBit =
		(*m_pAttackCollider)[0].m_HitTriggerCharacterBit |
		(*m_pAttackCollider)[1].m_HitTriggerCharacterBit |
		(*m_pAttackCollider)[2].m_HitTriggerCharacterBit |
		(*m_pAttackCollider)[3].m_HitTriggerCharacterBit;

	for (int i = 0; i < 4; i++)
	{
		//今まで当たったことのあるキャラクターを設定
		(*m_pAttackCollider)[i].m_haveHitCharacterBit = OldHitCharacterBit;
		//前のフレームで始めて当たったキャラクターを設定
		(*m_pAttackCollider)[i].m_HitTriggerCharacterBit = HitTriggerCharacterBit;
		//次のフレームで当てることが出来るキャラクターを設定
		(*m_pAttackCollider)[i].m_CanAttackCharacterBit = ~(*m_pAttackCollider)[i].m_haveHitCharacterBit;
		//下で使っている攻撃を設定するのでここで使わないように設定
		(*m_pAttackCollider)[i].m_Use = false;
	}
	//=====================================================

	//============<攻撃を当てた後にヒットストップを行うか>========
	//前のフレームで誰かに当たっていたら
	if (HitTriggerCharacterBit != 0x00)
	{
		m_HitAttackStopCount = m_HitStopFrame;
		EffectManager::GetManager()->SetPaused(m_efkHnd_Sword, true);
	}

	//攻撃を当てたヒットストップが終わるまで動かない
	if (m_HitAttackStopCount > 0)
	{
		m_HitAttackStopCount--;

		//攻撃が当たった時のストップが消える
		if (m_HitAttackStopCount == 0)
		{
			EffectManager::GetManager()->SetPaused(m_efkHnd_Sword, false);
			m_pEfk_HitBig->PausedEffect(false);
		}

		return;
	}
	//=====================================================

	//============<アニメーションの時間を設定>=============
	const int AnimeFrame = 40;
	const int EndFrame = 40;
	const float AnimeStartTime = 0.677f;
	const float AnimeEndTime = 1.164f;
	const float AnimeAllTime = AnimeEndTime - AnimeStartTime;

	m_FrameCount++;

	if (m_FrameCount == 13)
	{
		SoundManager::PlaySE("MissSword02");
	}


	//最後までアニメーションをした場合
	if (m_FrameCount >= EndFrame)
	{
		m_pCharacter->SetNextState(Character::STATE::State_AirMove);
		return;
	}

	m_AnimeTime = static_cast<float>(m_FrameCount) / static_cast<float>(AnimeFrame) * AnimeAllTime + AnimeStartTime;

	if (m_AnimeTime > AnimeEndTime)
	{
		m_AnimeTime = AnimeEndTime;
	}
	m_pModelDrawer->SetAnimeTime(m_AnimeTime);
	//=====================================================

	//============<剣の位置によって攻撃の位置を設定>=======
	const int AttackStartFrame = 18;
	const int AttackEndFrame = 28;
	const int AttackAllFrame = AttackEndFrame - AttackStartFrame;

	int AttackFrame = m_FrameCount - AttackStartFrame;
	int AttackNum = AttackFrame / (AttackAllFrame / 4);

	if (AttackNum >= 0 && AttackNum < 4)
	{
		(*m_pAttackCollider)[AttackNum].m_Use = true;
	}
	//=====================================================

	//============<移動処理>===============================
	float LeftStickX = m_pController->GetMoveInput().x * m_pMoveParameter->WalkSpeed;
	m_pCharacterParameter->Velocity.x = 
		fabsf(LeftStickX) > fabsf(m_pCharacterParameter->Velocity.x) ? 
		LeftStickX : m_pCharacterParameter->Velocity.x;

	m_pCharacterParameter->Velocity.x *= m_pMoveParameter->AirDrag;	//空気抵抗を掛ける
	m_pCharacterParameter->Velocity.y += m_pJumpParameter->FallDownGravity;	//重力を掛ける

	//重力制御(最大の落下速度になったら)
	if (m_pCharacterParameter->Velocity.y < m_pJumpParameter->DefaultFallSpeed)
	{
		m_pCharacterParameter->Velocity.y = m_pJumpParameter->DefaultFallSpeed;
	}

	//最終的な位置を設定
	m_pCharacterParameter->Pos += m_pCharacterParameter->Velocity;
	//=====================================================

	EffectManager::GetManager()->SetLocation(
		m_efkHnd_Sword, { 
			m_pCharacterParameter->Pos.x,
			m_pCharacterParameter->Pos.y + 1.0f,
			m_pCharacterParameter->Pos.z + 0.3f });
	for (int i = 0; i < 4; i++)
	{
		(*m_pAttackCollider)[i].m_BoxCollider.SetBasePos(m_pCharacterParameter->Pos);
	}
}

void Character00_AttackAirN::Draw()
{
	EffectManager::EffectDraw(m_efkHnd_Sword);
}

void Character00_AttackAirN::HitCharacter(Character* pHitCharacter, Character::ATTACKPARAM* pHitAttack)
{
	SoundManager::PlaySE("HitSword02");

	pHitCharacter->AddDamage(10.0f);								//ダメージの加算
	float ForcePower = (pHitCharacter->GetDamage() / 100.0f) * 1.2f + 0.3f;			//ダメージから吹っ飛ばすベクトルの計算

	pHitCharacter->SetPos(pHitCharacter->GetPos() + CVector3::GetUp() * 0.1f);		//少し上げて地面に当たっていないことにする

	//吹っ飛ばしベクトルを設定
	float DistanceX = pHitCharacter->GetPos().x - m_pCharacterParameter->Pos.x;
	CVector3 AddVec = CVector2::GetAngleVector(
		//当たったキャラクターが右にいる場合
		DistanceX > 0.0f
		? -15.0f : 15.0f
	) * ForcePower;
	pHitCharacter->AddForce(AddVec);

	//キャラクターがダッシュしたときのエフェクト
	SceneGame* pGameScene = static_cast<SceneGame*>(CScene::GetScene());

	m_pEfk_HitBig = new EffectHitBig();
	m_pEfk_HitBig->PlayHitEffect(
		pHitCharacter->GetPos() + (CVector3::GetUp() * pHitCharacter->GetCharacterCollider()->GetSize().y * 0.5f)
	);

	m_pEfk_HitBig->PausedEffect();
	pGameScene->GetEffectVector()->push_back(m_pEfk_HitBig);

	//ヒットストップの設定
	CharacterBase_HitStopState* pHitStopState =
		static_cast<CharacterBase_HitStopState*>(pHitCharacter->SetNextState(Character::STATE::State_HitStop));
	pHitCharacter->ChangeNextState();
	pHitStopState->SetHitStop(m_HitStopFrame, Character::STATE::State_BlowAway, true);	//ヒットストップの設定

	m_HitAttackStopCount = m_HitStopFrame;

	//相手のキャラクターの向きを設定
	if (DistanceX > 0.0f)	//右に吹っ飛ばす場合
	{
		pHitCharacter->SetLookLeft();
	}
	else
	{
		pHitCharacter->SetLookRight();
	}
}