#include "Character00_AttackAirN.h"
#include "Input.h"
#include "XboxKeyboard.h"
#include "CharacterBase_HitStopState.h"

void Character00_AttackAirN::Init()
{
	m_FrameCount = 0;
	m_AnimeTime = 0.935f;

	//当たり判定の作成
	CVector3 ColliderPos = m_pCharacterParameter->Pos;

	Character::ATTACKPARAM Attack;
	Attack.m_Use = false;
	Attack.m_BoxCollider.CreateBox(BoxCollider::BOXTYPE::CENTER,
		ColliderPos, CVector3(1.7f, 2.7f, 1.0f));

	m_pAttackCollider->push_back(Attack);

	m_AirNEffect = EffectManager::GetManager()->Play(EffectManager::GetEffect("C00_AirN"), 0, 0, 0);
	EffectManager::GetManager()->SetLocation(m_AirNEffect, { ColliderPos.x,ColliderPos.y + 1.0f,ColliderPos.z + 1.0f });
	EffectManager::GetManager()->SetScale(m_AirNEffect, 1.0f, 1.0f, 1.0f);

	m_pModelDrawer->PlayAnime("WAIT04", true);

	m_pCharacterParameter->MoveVector = CVector3::GetZero();
}

void Character00_AttackAirN::Update()
{
	if (m_pCharacterParameter->HitGround)
	{
		m_pCharacter->SetNextState(Character::STATE::State_Idle);
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
		(*m_pAttackCollider)[0].m_Use = true;
	}

	if (m_FrameCount == 12)
	{
		(*m_pAttackCollider)[0].m_Use = false;
	}

	//フレームごとにイベントを設定する
	if (m_FrameCount >= EndFrame)
	{
		m_pCharacter->SetNextState(Character::STATE::State_AirMove);
	}

	m_pModelDrawer->SetAnimeTime(m_AnimeTime);

	bool OnButton = false;

	float LeftStickX = m_pController->GetMoveInput().x * m_pMoveParameter->WalkSpeed;
	m_pCharacterParameter->Velocity.x = fabsf(LeftStickX) > fabsf(m_pCharacterParameter->Velocity.x) ? LeftStickX : m_pCharacterParameter->Velocity.x;

	if (IsKeyPress(VK_RIGHT))
	{
		m_pCharacterParameter->Velocity.x = m_pMoveParameter->AirSideMoveSpeed;
	}

	if (IsKeyPress(VK_LEFT))
	{
		m_pCharacterParameter->Velocity.x = -m_pMoveParameter->AirSideMoveSpeed;
	}

	if (!OnButton)
	{
		m_pCharacterParameter->Velocity.x *= m_pMoveParameter->AirDrag;	//空気抵抗を掛ける
	}

	m_pCharacterParameter->Velocity.y += m_pJumpParameter->FallDownGravity;			//重力を掛ける

	//重力制御(最大の落下速度になったら)
	if (m_pCharacterParameter->Velocity.y < m_pJumpParameter->DefaultFallSpeed)
	{
		m_pCharacterParameter->Velocity.y = m_pJumpParameter->DefaultFallSpeed;
	}

	m_pCharacterParameter->Pos += m_pCharacterParameter->MoveVector;
	m_pCharacterParameter->Pos += m_pCharacterParameter->Velocity;

	EffectManager::GetManager()->SetLocation(m_AirNEffect, { m_pCharacterParameter->Pos.x,m_pCharacterParameter->Pos.y + 1.0f,m_pCharacterParameter->Pos.z + 1.0f });
	(*m_pAttackCollider)[0].m_BoxCollider.SetBasePos(m_pCharacterParameter->Pos);
}

void Character00_AttackAirN::Uninit()
{
	EffectManager::GetManager()->StopEffect(m_AirNEffect);
	(*m_pAttackCollider).clear();
}

void Character00_AttackAirN::HitCharacter(Character* pHitCharacter)
{
	pHitCharacter->AddDamage(5.0f);								//ダメージの加算

	CVector3 AddVec = CVector2::GetAngleVector(
		m_pCharacter->GetLook() == Character::LOOKDIR::RIGHT ? 90.0f : -90.0f
	) * 0.5f;
	pHitCharacter->AddForce(AddVec);
}
