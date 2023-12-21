#include "Character_00.h"
#include "Input.h"
#include "XboxKeyboard.h"

void Character_00::Attack11_Init()
{
	m_AttackTime = 0;
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

	m_AttackCollider.push_back(Attack);

	m_CharacterModel.PlayAnime("Pose2", true);
}

void Character_00::Attack11_Update()
{
	const int AnimeFrame = 16;
	const int EndFrame = 30;
	const float AnimeStartTime = 1.145f;
	const float AnimeEndTime = 1.193f;
	const float AnimeAllTime = AnimeEndTime - AnimeStartTime;
	
	m_AttackTime++;
	m_AnimeTime = static_cast<float>(m_AttackTime) / static_cast<float>(AnimeFrame) * AnimeAllTime + AnimeStartTime;

	if (m_AnimeTime > AnimeEndTime)
	{
		m_AnimeTime = AnimeEndTime;
	}

	if (m_AttackTime == 6)
	{
		m_AttackCollider[0].m_Use = true;
	}

	if (m_AttackTime == 20)
	{
		m_AttackCollider[0].m_Use = false;
	}

	//このフレームの間であれば弱2へ行くことが出来る
	if (m_AttackTime > 15 && m_AttackTime < EndFrame)
	{
		//攻撃
		if (m_Controller.GetAttack())
		{
			ChangeAttack(Character::ATTACK::ATTACK_12);	//弱の設定
		}
	}

	//if (m_AttackTime > 24 || m_AttackTime < EndFrame)
	//{
	//	//移動
	//	CVector2 LeftStick = GetPressLeftStick();

	//	//デットゾーンの設定
	//	if (LeftStick.x * LeftStick.x + LeftStick.y * LeftStick.y < 0.15f * 0.15f)
	//	{
	//		LeftStick.x = LeftStick.y = 0.0f;
	//	}


	//	//移動開始
	//	if (LeftStick.x != 0.0f || IsKeyPress(VK_RIGHT) || IsKeyPress(VK_LEFT))
	//	{
	//		if (GetLeftSmash(0.35f) || IsKeyPress('L'))
	//		{
	//			ChangeState(Character::STATE::DASH);
	//		}
	//		else
	//		{
	//			ChangeState(Character::STATE::WALK);
	//		}
	//	}
	//}

	//フレームごとにイベントを設定する
	if (m_AttackTime >= EndFrame)
	{
		ChangeState(Character::STATE::IDLE);
	}

	m_CharacterModel.SetAnimeTime(m_AnimeTime);
}

void Character_00::Attack11_Uninit()
{
	m_AttackCollider.clear();
}

void Character_00::Attack11_Hit(Character* HitCharacter)
{
	HitCharacter->AddDamage(5.0f);								//ダメージの加算

	CVector3 AddVec = CVector2::GetAngleVector(
		m_NowLookDir == Character::LOOKDIR::RIGHT ? 90.0f : -90.0f
	) * 0.5f;
	HitCharacter->AddForce(AddVec);
}
