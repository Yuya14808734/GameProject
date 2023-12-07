#include "Character_Base.h"
#include "Input.h"
#include "Attack_Base.h"
#include "XboxKeyboard.h"

//===========================================================
//�L�����N�^�[���������ł���Ƃ��̏���������
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

	//���K�������x�N�g���̕ۑ�
	CVector3 NormalChangeVector = ChangeVector.normalize();
	CVector3 NormalVelocityVector = m_Velocity.normalize();

	//�ς����Ȃ�ς����������ł�
	float RotateRadian = acosf(NormalVelocityVector.dot(NormalChangeVector));
		
	m_Velocity = CQuaternion::RadianAxis(
		NormalVelocityVector.cross(NormalChangeVector),	//�񂷎�
		RotateRadian * m_VectorChangePower				//�񂷌ʓx				
	).RotateVector(m_Velocity);							//�񂷃x�N�g��


	m_MoveVector = CVector3::GetZero();
}

void Character::SmashUninit()
{

}

void Character::SmashUpdate()
{
	//�n�ʂɓ������Ă��Ȃ����
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
	
	//������x�Z���Ȃ�����
	if (SmashNowLength < m_MinimumSmashLength)
	{
		ChangeState(Character::STATE::AIRMOVE);
	}

	m_pos += m_Velocity;
}