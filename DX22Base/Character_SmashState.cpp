#include "Character_Base.h"
#include "Input.h"
#include "Attack_Base.h"
#include "XboxKeyboard.h"

//===========================================================
//キャラクターが吹っ飛んでいるときの処理を書く
//
//===========================================================


void Character::SmashInit()
{
	CVector3 ChangeVector;

	if (IsPadConnect())
	{
		ChangeVector.x = GetPressLeftStick().x;
		ChangeVector.y = GetPressLeftStick().y;
	}
	else
	{
		if (IsKeyPress(VK_RIGHT))
		{
			ChangeVector.x = 1.0f;
		}

		if (IsKeyPress(VK_LEFT))
		{
			ChangeVector.x = -1.0f;
		}

		if (IsKeyPress(VK_DOWN))
		{
			ChangeVector.x = -1.0f;
		}

		if (IsKeyPress(VK_UP))
		{
			ChangeVector.x = 1.0f;
		}
	}

	//正規化したベクトルの保存
	CVector3 NormalChangeVector = ChangeVector.normalize();
	CVector3 NormalVelocityVector = m_Velocity.normalize();

	//変えれるなら変えたい部分です
	float RotateRadian = acosf(NormalVelocityVector.dot(NormalChangeVector));
		
	m_Velocity = CQuaternion::RadianAxis(
		NormalVelocityVector.cross(NormalChangeVector),	//回す軸
		RotateRadian * m_VectorChangePower				//回す弧度				
	).RotateVector(m_Velocity);							//回すベクトル


	m_MoveVector = CVector3::GetZero();
}

void Character::SmashUninit()
{

}

void Character::SmashUpdate()
{
	//地面に当たっていなければ
	if (m_HitGround)
	{
		ChangeState(Character::STATE::DOWN);
	}

	bool NoButton = true;

	m_Velocity.x *= m_SmashMitigation;
	if (m_Velocity.y > 0.0f)
	{
		m_Velocity.y *= m_SmashMitigation;
	}
	else
	{
		m_Velocity.y += m_Gravity;
	}
	
	float SmashNowLength = m_Velocity.length();
	
	//ある程度短くなったら
	if (SmashNowLength < m_MinimumSmashLength)
	{
		ChangeState(Character::STATE::AIRMOVE);
	}

	m_pos += m_Velocity;
}