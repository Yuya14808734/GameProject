#include "Character_00.h"
#include "Input.h"
#include "XboxKeyboard.h"

void Character_00::Attack12_Init()
{
	m_AttackTime = 0;
	m_AnimeTime = 0.88f;

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
		ColliderPos, CVector3(1.7f, 2.7f, 1.0f));

	m_AttackCollider.push_back(Attack);

	m_CharacterModel.PlayAnime("Pose2", true);
}

void Character_00::Attack12_Update()
{
	const int AnimeFrame = 15;
	const int EndFrame = 30;
	const float AnimeStartTime = 0.88f;
	const float AnimeEndTime = 0.932f;
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

	if (m_AttackTime == 18)
	{
		m_AttackCollider[0].m_Use = false;
	}

	//このフレームの間であれば弱2へ行くことが出来る
	if (m_AttackTime > 12 && m_AttackTime < EndFrame)
	{
		//攻撃
		if (IsKeyPress('K') || InputPressKey(PadButton::A_BUTTON))
		{
			ChangeAttack(Character::ATTACK::ATTACK_13);	//弱の設定
		}
	}

	//フレームごとにイベントを設定する
	if (m_AttackTime >= EndFrame)
	{
		ChangeState(Character::STATE::IDLE);
	}

	m_CharacterModel.SetAnimeTime(m_AnimeTime);
}

void Character_00::Attack12_Uninit()
{
	m_AttackCollider.clear();
}

void Character_00::Attack12_Hit(Character* HitCharacter)
{
	HitCharacter->AddDamage(5.0f);								//ダメージの加算

	CVector3 AddVec = CVector2::GetAngleVector(
		m_NowLookDir == Character::LOOKDIR::RIGHT ? 90.0f : -90.0f
	) * 0.5f;
	HitCharacter->AddForce(AddVec);
}
