#include "Character_00.h"
#include "Input.h"
#include "XboxKeyboard.h"

void Character_00::AttackAirN_Init()
{
	m_FrameCount = 0;
	m_AnimeTime = 0.935f;

	//当たり判定の作成
	CVector3 ColliderPos = m_pos;

	ATTACKPARAM Attack;
	Attack.m_Use = false;
	Attack.m_BoxCollider.CreateBox(BoxCollider::BOXTYPE::CENTER,
		ColliderPos, CVector3(1.7f, 2.7f, 1.0f));

	m_AttackCollider.push_back(Attack);

	m_AirNEffect = EffectManager::GetManager()->Play(EffectManager::GetEffect("C00_AirN"), 0, 0, 0);
	EffectManager::GetManager()->SetLocation(m_AirNEffect, { ColliderPos.x,ColliderPos.y + 1.0f,ColliderPos.z + 1.0f });
	EffectManager::GetManager()->SetScale(m_AirNEffect, 1.0f, 1.0f, 1.0f);

	m_CharacterModel.PlayAnime("WAIT04", true);

	m_MoveVector = CVector3::GetZero();
}

void Character_00::AttackAirN_Update()
{
	if (m_HitGround)
	{
		ChangeState(Character::STATE::IDLE);
	}

	const int AnimeFrame = 40;
	const int EndFrame = 40;
	const float AnimeStartTime = 0.677f;
	const float AnimeEndTime = 1.164f;
	const float AnimeAllTime = AnimeEndTime - AnimeStartTime;

	m_FrameCount++;
	m_AnimeTime = static_cast<float>(m_FrameCount) / static_cast<float>(AnimeFrame) * AnimeAllTime + AnimeStartTime;

	if (m_AnimeTime > AnimeEndTime)
	{
		m_AnimeTime = AnimeEndTime;
	}

	if (m_FrameCount == 8)
	{
		m_AttackCollider[0].m_Use = true;
	}

	if (m_FrameCount == 12)
	{
		m_AttackCollider[0].m_Use = false;
	}

	//フレームごとにイベントを設定する
	if (m_FrameCount >= EndFrame)
	{
		ChangeState(Character::STATE::AIRMOVE);
	}

	m_CharacterModel.SetAnimeTime(m_AnimeTime);

	bool OnButton = false;

	float LeftStickX = m_Controller->GetMoveInput().x * m_MoveParameter.m_WalkSpeed;
	m_Velocity.x = fabsf(LeftStickX) > fabsf(m_Velocity.x) ? LeftStickX : m_Velocity.x;

	if (IsKeyPress(VK_RIGHT))
	{
		m_Velocity.x = m_MoveParameter.m_AirSideMoveSpeed;
	}

	if (IsKeyPress(VK_LEFT))
	{
		m_Velocity.x = -m_MoveParameter.m_AirSideMoveSpeed;
	}

	if (!OnButton)
	{
		m_Velocity.x *= m_MoveParameter.m_AirDrag;	//空気抵抗を掛ける
	}

	m_Velocity.y += m_JumpParameter.m_FallDownGravity;			//重力を掛ける

	//重力制御(最大の落下速度になったら)
	if (m_Velocity.y < m_JumpParameter.m_DefaultFallSpeed)
	{
		m_Velocity.y = m_JumpParameter.m_DefaultFallSpeed;
	}

	m_pos += m_MoveVector;
	m_pos += m_Velocity;

	EffectManager::GetManager()->SetLocation(m_AirNEffect, { m_pos.x,m_pos.y + 1.0f,m_pos.z + 1.0f });
	m_AttackCollider[0].m_BoxCollider.SetPos(m_pos);
}

void Character_00::AttackAirN_Uninit()
{
	EffectManager::GetManager()->StopEffect(m_AirNEffect);
	m_AttackCollider.clear();
}

void Character_00::AttackAirN_Hit(Character* HitCharacter)
{
	HitCharacter->AddDamage(5.0f);								//ダメージの加算

	CVector3 AddVec = CVector2::GetAngleVector(
		m_NowLookDir == Character::LOOKDIR::RIGHT ? 90.0f : -90.0f
	) * 0.5f;
	HitCharacter->AddForce(AddVec);
}
