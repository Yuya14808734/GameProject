#include "Character_Base.h"
#include "Input.h"
#include "Attack_Base.h"
#include "XboxKeyboard.h"

//===========================================================
//キャラクターが吹っ飛んでいるときの処理を書く
//
//===========================================================


void Character::BlowAwayInit()
{
	CVector3 ChangeVector = m_Controller.GetLeftInputVector();

	//正規化したベクトルの保存
	CVector3 NormalChangeVector = ChangeVector.normalize();
	NormalChangeVector.z = 0.0f;
	CVector3 NormalVelocityVector = m_Velocity.normalize();
	NormalVelocityVector.z = 0.0f;

	//変えれるなら変えたい部分です
	//float RotateRadian = acosf(NormalVelocityVector.dot(NormalChangeVector));
	//m_Velocity = CQuaternion::RadianAxis(
	//	NormalVelocityVector.cross(NormalChangeVector),	//回す軸
	//	RotateRadian * m_BlowAwayParameter.m_VectorChangePower				//回す弧度				
	//).RotateVector(m_Velocity);							//回すベクトル

	m_MoveVector = CVector3::GetZero();
}

void Character::BlowAwayUninit()
{
	int i = 0;
	i++;
}

void Character::BlowAwayUpdate()
{
	//地面に当たっていなければ
	if (m_HitGround)
	{
		ChangeState(Character::STATE::DOWN);
	}

	//吹っ飛ばされたベクトルをどんどん短くしていく
	m_Velocity.x *= m_BlowAwayParameter.m_SmashMitigation;

	//上から下に向かうベクトルに変わったら
	if (m_Velocity.y > 0.0f)
	{
		m_Velocity.y *= m_BlowAwayParameter.m_SmashMitigation;
	}
	else
	{
		m_Velocity.y += m_JumpParameter.m_FallDownGravity;
	}
	
	float SmashNowLength = m_Velocity.length();
	
	//ある程度短くなったら
	if (SmashNowLength < m_BlowAwayParameter.m_MinimumSmashLength)
	{
		ChangeState(Character::STATE::AIRMOVE);
	}

	m_pos += m_Velocity;
}