#include "CharacterBase_BlowAwayState.h"
#include "Input.h"
#include "XboxKeyboard.h"
#include "Effect01_SingleSmoke.h"

//===========================================================
//�L�����N�^�[���������ł���Ƃ��̏���������
//
//===========================================================


void CharacterBase_BlowAwayState::Init()
{
	//�Q�[���V�[���̐ݒ�
	m_pGameScene = static_cast<SceneGame*>(CScene::GetScene());
	m_Count = 0;

	//�R���g���[���[�̍����͂���Ă��鍶�X�e�B�b�N�̃x�N�g�����擾����
	CVector3 ChangeVector = m_pController->GetLeftInputVector();

	//�x�N�g���𐳋K�����ĕۑ�
	CVector3 NormalChangeVector = ChangeVector.normalize();
	NormalChangeVector.z = 0.0f;
	CVector3 NormalVelocityVector = m_pCharacterParameter->Velocity.normalize();
	NormalVelocityVector.z = 0.0f;

	//����΂���Ă���x�N�g���ƃR���g���[���[�œ��͂��ꂽ�x�N�g����
	//���p�[�Z���g��
	float RotateRadian = acosf(NormalVelocityVector.dot(NormalChangeVector));

	m_pCharacterParameter->Velocity = CQuaternion::RadianAxis(
		NormalVelocityVector.cross(NormalChangeVector).normalize(),						//�񂷎�
		RotateRadian * m_pBlowAwayParameter->VectorChangePower				//�񂷌ʓx
	).RotateVector(NormalVelocityVector);											//�񂷃x�N�g��

	m_pCharacterParameter->MoveVector = CVector3::GetZero();
}

void CharacterBase_BlowAwayState::Uninit()
{

}

void CharacterBase_BlowAwayState::Update()
{
	m_Count++;

	if (m_Count % 20)
	{
		//���ł���G�t�F�N�g��ǉ�
		SingleSmoke* pSingleSmoke = new SingleSmoke();
		pSingleSmoke->PlayEffect(m_pCharacterParameter->Pos,1.0f);

		m_pGameScene->GetEffectVector()->push_back(pSingleSmoke);
	}

	//�n�ʂɓ������Ă��Ȃ����
	if (m_pCharacterParameter->HitGround)
	{
		m_pCharacter->SetNextState(Character::STATE::State_Down);
		return;
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