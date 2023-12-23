#include "Character_Base.h"
#include "Input.h"
#include "Attack_Base.h"
#include "XboxKeyboard.h"

//===========================================================
//�L�����N�^�[���������ł���Ƃ��̏���������
//
//===========================================================


void Character::BlowAwayInit()
{
	CVector3 ChangeVector = m_Controller.GetLeftInputVector();

	//���K�������x�N�g���̕ۑ�
	CVector3 NormalChangeVector = ChangeVector.normalize();
	NormalChangeVector.z = 0.0f;
	CVector3 NormalVelocityVector = m_Velocity.normalize();
	NormalVelocityVector.z = 0.0f;

	//�ς����Ȃ�ς����������ł�
	//float RotateRadian = acosf(NormalVelocityVector.dot(NormalChangeVector));
	//m_Velocity = CQuaternion::RadianAxis(
	//	NormalVelocityVector.cross(NormalChangeVector),	//�񂷎�
	//	RotateRadian * m_BlowAwayParameter.m_VectorChangePower				//�񂷌ʓx				
	//).RotateVector(m_Velocity);							//�񂷃x�N�g��

	m_MoveVector = CVector3::GetZero();
}

void Character::BlowAwayUninit()
{
	int i = 0;
	i++;
}

void Character::BlowAwayUpdate()
{
	//�n�ʂɓ������Ă��Ȃ����
	if (m_HitGround)
	{
		ChangeState(Character::STATE::DOWN);
	}

	//������΂��ꂽ�x�N�g�����ǂ�ǂ�Z�����Ă���
	m_Velocity.x *= m_BlowAwayParameter.m_SmashMitigation;

	//�ォ�牺�Ɍ������x�N�g���ɕς������
	if (m_Velocity.y > 0.0f)
	{
		m_Velocity.y *= m_BlowAwayParameter.m_SmashMitigation;
	}
	else
	{
		m_Velocity.y += m_JumpParameter.m_FallDownGravity;
	}
	
	float SmashNowLength = m_Velocity.length();
	
	//������x�Z���Ȃ�����
	if (SmashNowLength < m_BlowAwayParameter.m_MinimumSmashLength)
	{
		ChangeState(Character::STATE::AIRMOVE);
	}

	m_pos += m_Velocity;
}