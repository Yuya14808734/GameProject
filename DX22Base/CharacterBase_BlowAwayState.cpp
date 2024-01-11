#include "CharacterBase_BlowAwayState.h"
#include "Input.h"
#include "XboxKeyboard.h"

//===========================================================
//�L�����N�^�[���������ł���Ƃ��̏���������
//
//===========================================================


void CharacterBase_BlowAwayState::Init()
{
	//�R���g���[���[�̍����͂���Ă��鍶�X�e�B�b�N�̃x�N�g�����擾����
	CVector3 ChangeVector = m_pController->GetLeftInputVector();

	//�x�N�g���𐳋K�����ĕۑ�
	CVector3 NormalChangeVector = ChangeVector.normalize();
	NormalChangeVector.z = 0.0f;
	CVector3 NormalVelocityVector = m_pCharacterParameter->Velocity.normalize();
	NormalVelocityVector.z = 0.0f;

	//����΂���Ă���x�N�g���ƃR���g���[���[�œ��͂��ꂽ�x�N�g����
	//���p�[�Z���g��
	//float RotateRadian = acosf(NormalVelocityVector.dot(NormalChangeVector));
	//m_Velocity = CQuaternion::RadianAxis(
	//	NormalVelocityVector.cross(NormalChangeVector),						//�񂷎�
	//	RotateRadian * m_BlowAwayParameter.m_VectorChangePower				//�񂷌ʓx
	//).RotateVector(m_Velocity);											//�񂷃x�N�g��

	m_pCharacterParameter->MoveVector = CVector3::GetZero();
}

void CharacterBase_BlowAwayState::Uninit()
{

}

void CharacterBase_BlowAwayState::Update()
{
	//�n�ʂɓ������Ă��Ȃ����
	if (m_pCharacterParameter->HitGround)
	{
		m_pCharacter->SetNextState(Character::STATE::State_Down);
	}

	//������΂��ꂽ�x�N�g�����ǂ�ǂ�Z�����Ă���
	m_pCharacterParameter->Velocity.x *= m_pBlowAwayParameter->SmashMitigation;

	//�ォ�牺�Ɍ������x�N�g���ɕς������
	if (m_pCharacterParameter->Velocity.y > 0.0f)
	{
		m_pCharacterParameter->Velocity.y *= m_pBlowAwayParameter->SmashMitigation;
	}
	else
	{
		m_pCharacterParameter->Velocity.y += m_pJumpParameter->FallDownGravity;
	}
	
	float SmashNowLength = m_pCharacterParameter->Velocity.length();
	
	//������x�Z���Ȃ�����
	if (SmashNowLength < m_pBlowAwayParameter->MinimumSmashLength)
	{
		m_pCharacter->SetNextState(Character::STATE::State_FallDown);
	}

	m_pCharacterParameter->Pos += m_pCharacterParameter->Velocity;
}