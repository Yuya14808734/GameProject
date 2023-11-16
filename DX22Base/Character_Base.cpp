#include "Character_Base.h"

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
	Update();
}

void Character::Character_Draw()
{
	Draw();
}

int Character::GetPlayerBit()
{
	return m_PlayerBit;
}

const Character::STATE & Character::GetState() const
{
	return m_State;
}

ModelDrawer* Character::GetModel() const
{
	return const_cast<ModelDrawer*>(&m_CharacterModel);
}

const CVector3 & Character::GetPos() const
{
	return m_pos;
}

void Character::SetPos(const CVector3 & pos)
{
	m_pos = pos;
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

std::vector<SphereCollider>* Character::GetCollider() const
{
	return const_cast<std::vector<SphereCollider>*>(&m_Collider);
}
