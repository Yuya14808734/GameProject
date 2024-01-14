#include "Character00_Attack11.h"
#include "Input.h"
#include "XboxKeyboard.h"
#include "CharacterBase_HitStopState.h"

void Character00_Attack11::Init()
{
	m_FrameCount = 0;
	m_AnimeTime = 1.145f;
	
	//当たり判定の作成
	BoxCollider* pCollider = m_pCharacter->GetCharacterCollider();
	CVector3 ColliderPos = m_pCharacterParameter->Pos + CVector3::GetUp() * (pCollider->GetSize().y * 0.5f);	

	switch (m_pCharacter->GetLook())
	{
	case Character::LOOKDIR::RIGHT:
		ColliderPos = ColliderPos +
			CVector3(0.7f,0.4f,0.0f);
		break;
	case Character::LOOKDIR::LEFT:
		ColliderPos = ColliderPos + 
			CVector3(-0.7f,0.4f,0.0f);
		break;
	};

	CVector3 ColliderSize = CVector3(1.0f, 0.9f, 1.0f);

	Character::ATTACKPARAM Attack;
	Attack.m_Use = false;
	Attack.m_BoxCollider.CreateBox(BoxCollider::BOXTYPE::CENTER,
		ColliderPos, ColliderSize);
	Attack.m_CanAttackCharacterBit = 0xffffffff;					//当たるキャラクターの設定

	m_pAttackCollider->push_back(Attack);

	m_pModelDrawer->PlayAnime("Pose2", true);

	m_PushButton = false;
}

void Character00_Attack11::Uninit()
{
	m_pAttackCollider->clear();
}

void Character00_Attack11::Update()
{
	//============<攻撃を当てるかの設定>===================
	//今まで当たったことのあるキャラクターには当てない
	(*m_pAttackCollider)[0].m_CanAttackCharacterBit = ~(*m_pAttackCollider)[0].m_haveHitCharacterBit;
	//=====================================================

	const int AnimeAllFrame = 16;								//アニメーション全体のフレーム
	const int EndFrame = 30;									//攻撃終了時間
	const float AnimeStartTime = 1.145f;						//アニメーション開始時間
	const float AnimeEndTime = 1.193f;							//アニメーション終了時間
	const float AnimeAllTime = AnimeEndTime - AnimeStartTime;	//アニメーションの時間
	
	m_FrameCount++;

	//アニメーションの再生時間の更新
	m_AnimeTime = static_cast<float>(m_FrameCount) / static_cast<float>(AnimeAllFrame) * AnimeAllTime + AnimeStartTime;

	//アニメーションが終了するべき時間を超えていた場合
	if (m_AnimeTime > AnimeEndTime)
	{
		m_AnimeTime = AnimeEndTime;
	}

	//当たり判定開始
	if (m_FrameCount == 6)					
	{
		(*m_pAttackCollider)[0].m_Use = true;
	}

	//当たり判定終了
	if (m_FrameCount == 20)					
	{
		(*m_pAttackCollider)[0].m_Use = false;
	}

	//ボタンをこのフレームの間に押していると次の攻撃に向かう
	if (m_FrameCount > 5 && m_FrameCount < EndFrame)
	{
		if (m_pController->GetAttack())
		{
			m_PushButton = true;
		}
	}

	//このフレームの間で移動するなら移動する
	if (m_FrameCount > 10 && m_FrameCount < EndFrame)	
	{
		//攻撃
		if (m_PushButton)	
		{
			m_pCharacter->SetNextState(Character::STATE::State_Attack12); //弱の設定
		}
	}

	//フレームごとにイベントを設定する
	if (m_FrameCount >= EndFrame)		
	{
		m_pCharacter->SetNextState(Character::STATE::State_Idle);
	}

	//アニメーションの再生時間の設定
	m_pModelDrawer->SetAnimeTime(m_AnimeTime);
}

void Character00_Attack11::HitCharacter(Character* pHitCharacter)
{
	pHitCharacter->AddDamage(2.0f);								//ダメージの加算
	CharacterBase_HitStopState* pHitStopState =
	static_cast<CharacterBase_HitStopState*>(pHitCharacter->SetNextState(Character::STATE::State_HitStop));
	pHitCharacter->ChangeNextState();
	pHitStopState->SetHitStop(5, Character::STATE::State_LeanBack,true);	//ヒットストップの設定
}
