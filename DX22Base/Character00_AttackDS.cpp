#include "Character00_AttackDS.h"
#include "CharacterBase_HitStopState.h"
#include "SoundManager.h"

void Character00_AttackDS::Init()
{
	m_FrameCount = 0;
	m_AnimeTime = 0.375f;

	//=========<当たり判定の作成>======================
	CVector3 ColliderBasePos = m_pCharacterParameter->Pos;
	CVector3 ShiftVec = m_pCharacterCollider->GetSize();
	
	CVector3 ColliderSize(
	m_pCharacterCollider->GetSize().y,
		m_pCharacterCollider->GetSize().x,
		m_pCharacterCollider->GetSize().z);

	switch (m_pCharacter->GetLook())
	{
	case Character::LOOKDIR::RIGHT:
		ShiftVec.x = ShiftVec.x * 0.5f;
		ShiftVec.y = ShiftVec.y * 0.3f;
		break;
	case Character::LOOKDIR::LEFT:
		ShiftVec.x = ShiftVec.x * -0.5f;
		ShiftVec.y = ShiftVec.y * 0.3f;
		break;
	}

	//=========<攻撃の当たり判定の設定>==================
	Character::ATTACKPARAM Attack;
	Attack.m_Use = false;
	Attack.m_BoxCollider.CreateBox(BoxCollider::BOXTYPE::FOOT,
		m_pCharacterParameter->Pos, ColliderSize + CVector3(-0.2f,0.0f,0.0f));// , ShiftVec);
	Attack.m_CanAttackCharacterBit = 0xffffffff;					//当たるキャラクターの設定

	(*m_pAttackCollider).push_back(Attack);

	m_pModelDrawer->PlayAnime("Slide00", true);

	m_HitStopCount = 0;

	//===========<キャラクターの前に置く当たり判定ボックスを置く>===============
	//もし崖だった場合はそれよりも奥に行かない
	float AddX = m_pCharacterParameter->Velocity.x > 0.0f ?
		1.0f :	//右に行く場合
		-1.0f;	//左に行く場合

	AddX = AddX * ((ColliderSize.x * 0.5f) + 0.2f);

	m_frontBox.SetShiftVec(CVector3(AddX, -0.15f, 0.0f));
	m_frontBox.SetSize(CVector3(0.3f, 0.3f, 0.3f));
}

void Character00_AttackDS::Update()
{
	//地面に当たるとアイドル状態に変える
	if (!m_pCharacterParameter->HitGround)
	{
		m_pCharacter->SetNextState(Character::STATE::State_AirMove);
	}

	//============<攻撃を当てるかの設定>===================
	//今まで当たったことのあるキャラクターには当てない
	(*m_pAttackCollider)[0].m_CanAttackCharacterBit = ~(*m_pAttackCollider)[0].m_haveHitCharacterBit;
	//=====================================================

	//============<攻撃を当てた後にヒットストップを行うか>========
	//前のフレームで誰かに当たった場合
	if ((*m_pAttackCollider)[0].m_HitTriggerCharacterBit != 0x00)
	{
		m_HitStopCount = m_HitStopFrame;
	}

	//攻撃を当てたヒットストップが終わるまで動かない
	if (m_HitStopCount > 0)
	{
		m_HitStopCount--;

		//地面に当たっていない判定になるので重力を足してやる
		m_pCharacterParameter->Velocity.y += m_pJumpParameter->FallDownGravity;

		//最終的な位置を設定
		m_pCharacterParameter->Pos += m_pCharacterParameter->Velocity;
		(*m_pAttackCollider)[0].m_BoxCollider.SetBasePos(m_pCharacterParameter->Pos);
		return;
	}
	//======================================================================

	//============<アニメーションの時間を設定>==============================
	const int AnimeAllFrame = 30;								//アニメーション全体のフレーム
	const int EndFrame = 30;									//攻撃終了時間
	const float AnimeStartTime = 0.375f;						//アニメーション開始時間
	const float AnimeEndTime = 1.417f;							//アニメーション終了時間
	const float AnimeAllTime = AnimeEndTime - AnimeStartTime;	//アニメーションの時間

	m_FrameCount++;

	if (m_FrameCount == 4)
	{
		SoundManager::PlaySE("Slide");
	}

	//フレームごとにイベントを設定する
	if (m_FrameCount >= EndFrame)
	{
		m_pCharacter->SetNextState(Character::STATE::State_Idle);
	}

	//アニメーションの再生時間の更新
	m_AnimeTime = static_cast<float>(m_FrameCount) / static_cast<float>(AnimeAllFrame) * AnimeAllTime + AnimeStartTime;

	if (m_AnimeTime > AnimeEndTime)
	{
		m_AnimeTime = AnimeEndTime;
	}

	//アニメーションの再生時間の設定
	m_pModelDrawer->SetAnimeTime(m_AnimeTime);
	//======================================================================

	//============<当たり判定の設定>=======================================
	if (m_FrameCount == 5)
	{
		(*m_pAttackCollider)[0].m_Use = true;
	}

	if (m_FrameCount == 24)
	{
		(*m_pAttackCollider)[0].m_Use = false;
	}

	//======================================================================

	//============<移動処理>===============================================
	m_frontBox.SetBasePos(m_pCharacterParameter->Pos);

	bool hitStage = false;

	//キャラクターの前にブロックを設置して当たり判定を行う
	for (const BoxCollider& box : (*m_pStage->GetStageCollider()))
	{
		hitStage = m_frontBox.CollisionBox(box);

		if (hitStage)
		{
			break;
		}
	}

	//すべての地面に当たらなかった場合、地面がない
	if (!hitStage)
	{
		m_pCharacterParameter->Velocity.x = 0.0f;
	}

	m_pCharacterParameter->Velocity.x *= 0.99f;
	m_pCharacterParameter->Velocity.y += m_pJumpParameter->FallDownGravity;

	//最終的な位置を設定
	m_pCharacterParameter->Pos += m_pCharacterParameter->Velocity;
	(*m_pAttackCollider)[0].m_BoxCollider.SetBasePos(m_pCharacterParameter->Pos);
	//======================================================================
}

void Character00_AttackDS::Draw()
{

}

void Character00_AttackDS::Uninit()
{
	(*m_pAttackCollider).clear();
}

void Character00_AttackDS::HitCharacter(Character* pHitCharacter)
{
	SoundManager::PlaySE("HitPunch02");

	//ダメージの加算
	pHitCharacter->AddDamage(15.0f);

	//少し上げて地面に当たっていないことにする
	pHitCharacter->SetPos(pHitCharacter->GetPos() + CVector3::GetUp() * 0.1f);

	//ダメージから吹っ飛ばすベクトルの計算
	float ForcePower = (pHitCharacter->GetDamage() / 100.0f) * 0.5f + 0.3f;
	//吹っ飛ばしベクトルを設定
	CVector3 AddVec = CVector2::GetAngleVector(
		m_pCharacter->GetLook() == Character::LOOKDIR::RIGHT ? -20.0f : 20.0f
	) * ForcePower;
	pHitCharacter->AddForce(AddVec);

	//ヒットストップの設定
	CharacterBase_HitStopState* pHitStopState =
		static_cast<CharacterBase_HitStopState*>(pHitCharacter->SetNextState(Character::STATE::State_HitStop));
	pHitCharacter->ChangeNextState();
	pHitStopState->SetHitStop(m_HitStopFrame, Character::STATE::State_BlowAway, true);	//ヒットストップの設定
	m_HitStopCount = m_HitStopFrame;
}