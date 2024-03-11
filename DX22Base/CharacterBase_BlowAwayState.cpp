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
		NormalVelocityVector.cross(NormalChangeVector).normalize(),					//�񂷎�
		RotateRadian * m_pBlowAwayParameter->VectorChangePower						//�񂷌ʓx
	).RotateVector(m_pCharacterParameter->Velocity);											//�񂷃x�N�g��

	m_pCharacterParameter->MoveVector = CVector3::GetZero();

	//�G�t�F�N�g�̒ǉ�
	m_pMultipleSmoke = new MultipleSmoke();
	m_pMultipleSmoke->SetSingleSmokeEndTime(1.0f);
	m_pGameScene->GetEffectVector()->push_back(m_pMultipleSmoke);
}

void CharacterBase_BlowAwayState::Uninit()
{
	m_pMultipleSmoke->SetEffectAddEnd(true);
}

void CharacterBase_BlowAwayState::Update()
{
	m_Count++;

	if (m_Count % 2 == 0)
	{
		//���ł���G�t�F�N�g��ǉ�
		m_pMultipleSmoke->AddPlayEffect(m_pCharacterParameter->Pos + CVector3(0.0f,0.5f,0.0f),
			m_pCharacterParameter->Velocity * -0.5f);
	}

	//�n�ʂɓ������Ă��Ȃ����
	if (m_pCharacterParameter->HitGround)
	{
		m_pCharacter->SetNextState(Character::STATE::State_Down);
		return;
	}

	//������΂��ꂽ�x�N�g�����ǂ�ǂ�Z�����Ă���
	m_pCharacterParameter->Velocity *= m_pBlowAwayParameter->SmashMitigation;
	
	float SmashNowLength = m_pCharacterParameter->Velocity.length();
	
	//������x�Z���Ȃ�����
	if (SmashNowLength < m_pBlowAwayParameter->MinimumSmashLength)
	{
		m_pCharacter->SetNextState(Character::STATE::State_FallDown);
	}

	m_pCharacterParameter->Pos += m_pCharacterParameter->Velocity;
}