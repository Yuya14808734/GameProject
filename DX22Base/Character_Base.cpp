#include "Character_Base.h"
#include "Attack_Base.h"
#include "Scene.h"
#include "Scene00_Game.h"

int Character::m_NewPlayerBit = 0x01;

void Character::InitPlayerBit()
{
	m_NewPlayerBit = 0x01;
}

int Character::GetNewPlayerBit()
{
	int ReturnBit = m_NewPlayerBit;
	m_NewPlayerBit = m_NewPlayerBit << 1;
	return ReturnBit;
}

void Character::Character_Init()
{
	m_PlayerBit = GetNewPlayerBit();
	int PlayerNum = static_cast<int>(log2f(static_cast<float>(m_PlayerBit))) + 1;

	//キャラクターの番号によってステージの場所を変える
	std::vector<CVector3>* startPosV = static_cast<SceneGame*>(CScene::GetScene())->GetStage()->GetCharacterStartPos();
	m_pos = (*startPosV)[PlayerNum - 1];
	
	//コントローラーの設定
	if (PlayerNum == 1)
	{
		m_Controller.SetController(
			PlayerController::PLAYCONTROLLERTYPE::KEYBOARD,
			PlayerNum - 1
		);
	}
	else
	{
		m_Controller.SetController(
			PlayerController::PLAYCONTROLLERTYPE::GAMEPAD,
			PlayerNum - 1
		);
	}

	CVector2 BasePos(450.0f, 650.0f);
	CVector2 PosDistance(400.0f, 0.0f);

	m_DamageUI.SetPos(BasePos + (PosDistance * static_cast<float>(PlayerNum - 1)));


	Init();

	m_ChangeState = false;
	m_JumpCount = 0;
	m_HitGround = m_HitCeiling = m_HitWall = false;

	StateInit(m_NowState);
}

void Character::Character_Uninit()
{
	Uninit();
}

void Character::Character_Update()
{
	m_oldPos = m_pos;

	Update();

	//========================================
	// 各ステータスのアップデート
	//========================================
	StateUpdate(m_NowState);

	//========================================
	// 各ステータスが切り替わっていたら
	//========================================
	if (m_ChangeState)
	{
		m_ChangeState = false;

		SetState(m_NextState);

	}

	m_CharacterCollider.SetPos(m_pos);

	m_DamageUI.GetDamageUI()->SetNumber(static_cast<int>(m_DamagePercentage));
	m_DamageUI.Update();
}

void Character::Character_Draw()
{
	Draw();

	m_CharacterModel.SetPosition(m_Shake ? m_pos + m_AddDrawPos : m_pos);
	m_CharacterModel.SetRotatePosShiftVector(m_ShiftCenterPos);
	m_CharacterModel.SetRotate(m_rotate);

	m_CharacterModel.Draw();
}

void Character::Character_UIDraw()
{
	m_DamageUI.Draw();
}

void Character::StateInit(Character::STATE state)
{
	//========================================
	// 初期化
	//========================================
	switch (state)
	{
	case Character::STATE::IDLE:
		IdleInit();
		break;
	case Character::STATE::WALK:
		WalkInit();
		break;
	case Character::STATE::DASH:
		DashInit();
		break;
	case Character::STATE::ATTACK:
		AttackInit();
		break;
	case Character::STATE::BLOWAWAY:
		BlowAwayInit();
		break;
	case Character::STATE::JUMPIN:
		JumpInInit();
		break;
	case Character::STATE::JUMP:
		JumpInit();
		break;
	case Character::STATE::AIRMOVE:
		AirMoveInit();
		break;
	case Character::STATE::FALLDOWN:
		FallDownInit();
		break;
	case Character::STATE::LEANBACK:
		LeanBackInit();
		break;
	case Character::STATE::DOWN:
		DownInit();
		break;
	case Character::STATE::WAKEUP:
		WakeUpInit();
		break;
	case Character::STATE::HITSTOP:
		HitStopInit();
		break;
	case Character::STATE::MAX:
		break;
	default:
		break;
	}
}

void Character::StateUninit(Character::STATE state)
{
	//========================================
	//終了処理
	//========================================
	switch (state)
	{
	case Character::STATE::IDLE:
		IdleUninit();
		break;
	case Character::STATE::WALK:
		WalkUninit();
		break;
	case Character::STATE::DASH:
		DashUninit();
		break;
	case Character::STATE::ATTACK:
		AttackUninit();
		break;
	case Character::STATE::BLOWAWAY:
		BlowAwayUninit();
		break;
	case Character::STATE::JUMPIN:
		JumpInUninit();
		break;
	case Character::STATE::JUMP:
		JumpUninit();
		break;
	case Character::STATE::AIRMOVE:
		AirMoveUninit();
		break;
	case Character::STATE::FALLDOWN:
		FallDownUninit();
		break;
	case Character::STATE::LEANBACK:
		LeanBackUninit();
		break;
	case Character::STATE::DOWN:
		DownUninit();
		break;
	case Character::STATE::WAKEUP:
		WakeUpUninit();
		break;
	case Character::STATE::HITSTOP:
		HitStopUninit();
		break;
	case Character::STATE::MAX:
		break;
	default:
		break;
	}
}

void Character::StateUpdate(Character::STATE state)
{
	//========================================
	// 各ステータスのアップデート
	//========================================
	switch (state)
	{
	case Character::STATE::IDLE:
		IdleUpdate();
		break;
	case Character::STATE::WALK:
		WalkUpdate();
		break;
	case Character::STATE::DASH:
		DashUpdate();
		break;
	case Character::STATE::ATTACK:
		AttackUpdate();
		break;
	case Character::STATE::BLOWAWAY:
		BlowAwayUpdate();
		break;
	case Character::STATE::JUMPIN:
		JumpInUpdate();
		break;
	case Character::STATE::JUMP:
		JumpUpdate();
		break;
	case Character::STATE::AIRMOVE:
		AirMoveUpdate();
		break;
	case Character::STATE::FALLDOWN:
		FallDownUpdate();
		break;
	case Character::STATE::LEANBACK:
		LeanBackUpdate();
		break;
	case Character::STATE::DOWN:
		DownUpdate();
		break;
	case Character::STATE::WAKEUP:
		WakeUpUpdate();
		break;
	case Character::STATE::HITSTOP:
		HitStopUpdate();
		break;
	case Character::STATE::MAX:
		break;
	default:
		break;
	}
}

int Character::GetCharacterBit()
{
	return m_PlayerBit;
}

void Character::SetState(Character::STATE NextState)
{
	//========================================
	//終了処理
	//========================================
	StateUninit(m_NowState);

	//========================================
	// 初期化
	//========================================
	StateInit(NextState);

	m_NowState = NextState;
}

void Character::SetHitStop(int HitStopCount, Character::STATE NextState)
{
	SetState(Character::STATE::HITSTOP);
	m_HitStopCount = HitStopCount;
	m_HitStopNextState = NextState;
}

const Character::STATE& Character::GetState() const
{
	return m_NowState;
}

const Character::ATTACK& Character::GetAttack() const
{
	return m_NowAttack;
}

ModelDrawer* Character::GetModel() const
{
	return const_cast<ModelDrawer*>(&m_CharacterModel);
}

const CVector3& Character::GetPos() const
{
	return m_pos;
}

void Character::SetPos(const CVector3 & pos)
{
	m_pos = pos;
	m_CharacterCollider.SetPos(pos);
}

const CVector3& Character::GetOldPos() const
{
	return m_oldPos;
}

void Character::SetOldPos()
{
	m_oldPos = m_pos;
}

const CVector3 & Character::GetScale() const
{
	return m_scale;
}

void Character::SetScale(const CVector3 & scale)
{
	m_scale = scale;
}

const CQuaternion & Character::GetRotate() const
{
	return m_rotate;
}

void Character::SetRotate(const CQuaternion & rotate)
{
	m_rotate = rotate;
}

void Character::SetRotate(const CVector3 & rotate)
{
	m_rotate.v = DirectX::XMQuaternionRotationRollPitchYaw(
		DirectX::XMConvertToRadians(rotate.x),
		DirectX::XMConvertToRadians(rotate.y),
		DirectX::XMConvertToRadians(rotate.z));
}

void Character::SetShake(bool shake)
{
	m_Shake = shake;
}

bool Character::GetShake()
{
	return m_Shake;
}

void Character::SetLookRight()
{
	m_NowLookDir = Character::LOOKDIR::RIGHT;
	m_rotate = CQuaternion::AngleAxis(CVector3::GetUp(),90.0f);
}

void Character::SetLookLeft()
{
	m_NowLookDir = Character::LOOKDIR::LEFT;
	m_rotate = CQuaternion::AngleAxis(CVector3::GetUp(), -90.0f);
}

void Character::AddForce(const CVector3 & force)
{
	m_Velocity += force;
}

void Character::SetForce(const CVector3 & force)
{
	m_Velocity = force;
}

float Character::GetDamage() const
{
	return m_DamagePercentage;
}

void Character::AddDamage(float damage)
{
	m_DamagePercentage += damage;
}

void Character::SetDamage(float damage)
{
	m_DamagePercentage = damage;
}

void Character::SetInvincible(bool invincible)
{
	m_Invincible = invincible;
}

bool Character::IsInvincible()
{
	return m_Invincible;
}

BoxCollider* Character::GetCharacterCollider() const
{
	return const_cast<BoxCollider*>(&m_CharacterCollider);
}

std::vector<Character::ATTACKPARAM>& Character::GetAttackCollider()
{
	return m_AttackCollider;
}

void Character::Character_ColliderInit()
{
	m_HitCeiling = m_HitGround = m_HitWall = false;
}

void Character::Character_HitCeiling()
{
	m_HitCeiling = true;
	HitCeiling();
}

void Character::Character_HitGround()
{
	m_Velocity.y = 0.0f;
	m_JumpCount = 0;
	m_HitGround = true;
	HitGround();
}

void Character::Character_HitWall()
{
	m_HitWall = true;
	HitWall();
}

void Character::DrawCollider()
{
	m_CharacterCollider.DrawCollider();
}

//=========<この下の関数はUpdateで呼ぶ関数です>=========
void Character::ChangeAttack(Character::ATTACK attack)
{
	ChangeState(Character::STATE::ATTACK);
	m_NowAttack = attack;
}

void Character::ChangeState(Character::STATE state)
{
	m_NextState = state;
	m_ChangeState = true;
}

void Character::ChangeHitStop(int HitStopCount, Character::STATE NextState)
{
	ChangeState(Character::STATE::HITSTOP);
	m_HitStopCount = HitStopCount;
	m_HitStopNextState = NextState;
}

