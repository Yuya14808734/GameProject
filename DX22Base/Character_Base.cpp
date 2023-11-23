#include "Character_Base.h"
#include "Attack_Base.h"

int Character::m_NewPlayerBit = 0x00;

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
	Init();
}

void Character::Character_Uninit()
{
	Uninit();
}

void Character::Character_Update()
{
	m_oldPos = m_pos;
	Character::STATE BeforeState = m_State;

	Update();

	//========================================
	// 各ステータスのアップデート
	//========================================
	switch (m_State)
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
	case Character::STATE::SMASH:
		SmashUpdate();
		break;
	case Character::STATE::JUMP:
		JumpUpdate();
		break;
	case Character::STATE::AIRMOVE:
		AirMoveUpdate();
		break;
	case Character::STATE::DOWN:
		DownUpdate();
		break;
	case Character::STATE::MAX:
		break;
	default:
		break;
	}

	//========================================
	// 各ステータスが切り替わっていたら
	//========================================
	if (m_State != BeforeState)
	{
		//========================================
		//終了処理
		//========================================
		switch (BeforeState)
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
		case Character::STATE::SMASH:
			SmashUninit();
			break;
		case Character::STATE::JUMP:
			JumpUninit();
			break;
		case Character::STATE::AIRMOVE:
			AirMoveUninit();
			break;
		case Character::STATE::DOWN:
			DownUninit();
			break;
		case Character::STATE::MAX:
			break;
		default:
			break;
		}

		//========================================
		// 初期化
		//========================================
		switch (m_State)
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
		case Character::STATE::SMASH:
			SmashInit();
			break;
		case Character::STATE::JUMP:
			JumpInit();
			break;
		case Character::STATE::AIRMOVE:
			AirMoveInit();
			break;
		case Character::STATE::DOWN:
			DownInit();
			break;
		case Character::STATE::MAX:
			break;
		default:
			break;
		}

	}

	m_CharacterModel.SetPosition(m_pos);
	m_CharacterCollider.SetPos(m_pos);
}

void Character::Character_Draw()
{
	Draw();
}

int Character::GetPlayerBit()
{
	return m_PlayerBit;
}

const Character::STATE& Character::GetState() const
{
	return m_State;
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
	m_CharacterModel.SetPosition(pos);
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

BoxCollider* Character::GetCharacterCollider() const
{
	return const_cast<BoxCollider*>(&m_CharacterCollider);
}

void Character::Character_HitRoof()
{
	HitRoof();
}

void Character::Character_HitGround()
{
	m_Velocity.y = 0.0f;
	m_JumpCount = 0;
	HitGround();
}

void Character::Character_HitWall()
{
	HitWall();
}

void Character::DrawCollider()
{
	m_CharacterCollider.DrawCollider();
}

void Character::SetParameter(float WalkSpeed, float DashSpeed, float FallSideMoveSpeed, int MaxJumpCount, float JumpPower, float GravityScale, float MaxFallSpeed, float Friction, float AirResistance)
{
	m_PlayerBit = GetNewPlayerBit();
	m_WalkSpeed = WalkSpeed;
	m_DashSpeed = DashSpeed;
	m_FallSideMoveSpeed = FallSideMoveSpeed;
	m_MaxJumpCount = MaxJumpCount;
	m_JumpPower = JumpPower;
	m_Gravity = GravityScale;
	m_MaxFallSpeed = MaxFallSpeed;
	m_Friction = Friction;
	m_AirResistance = AirResistance;
}

void Character::SetAttack(Attack* pAttack)
{
	if (m_pNowAttack != nullptr)
	{
		m_pNowAttack->Attack_Uninit();
		delete m_pNowAttack;
	}

	m_pNowAttack = pAttack;
	if (m_pNowAttack != nullptr)
	{
		m_pNowAttack->Attack_Init();
		m_State = Character::STATE::ATTACK;
	}
}

