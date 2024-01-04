#include "Character_00.h"
#include "Input.h"
#include "XboxKeyboard.h"

void Character_00::Attack11_Init()
{
	m_FrameCount = 0;
	m_AnimeTime = 1.145f;
	
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

	m_CharacterModel.PlayAnime("Pose2", true);

	m_PushButton = false;
}

void Character_00::Attack11_Update()
{
	//============<攻撃を当てるかの設定>===================
	//今まで当たったことのあるキャラクターには当てない
	m_AttackCollider[0].m_CanAttackCharacterBit = ~m_AttackCollider[0].m_haveHitCharacterBit;
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
		m_AttackCollider[0].m_Use = true;
	}

	//当たり判定終了
	if (m_FrameCount == 20)					
	{
		m_AttackCollider[0].m_Use = false;
	}

	//ボタンをこのフレームの間に押していると次の攻撃に向かう
	if (m_FrameCount > 5 && m_FrameCount < EndFrame)
	{
		if (m_Controller->GetAttack())
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
			ChangeAttack(Character::ATTACK::ATTACK_12);	//弱の設定
		}
	}

	//フレームごとにイベントを設定する
	if (m_FrameCount >= EndFrame)		
	{
		ChangeState(Character::STATE::IDLE);
	}

	//アニメーションの再生時間の設定
	m_CharacterModel.SetAnimeTime(m_AnimeTime);
}

void Character_00::Attack11_Uninit()
{
	m_AttackCollider.clear();
}

void Character_00::Attack11_Hit(Character* HitCharacter)
{
	HitCharacter->AddDamage(2.0f);								//ダメージの加算
	HitCharacter->SetHitStop(5, Character::STATE::LEANBACK);	//ヒットストップの
	HitCharacter->SetShake(true);
}
