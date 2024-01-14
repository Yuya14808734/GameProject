#include "Character00_Attack11.h"
#include "Input.h"
#include "XboxKeyboard.h"
#include "CharacterBase_HitStopState.h"

void Character00_Attack11::Init()
{
	m_FrameCount = 0;
	m_AnimeTime = 1.145f;
	
	//�����蔻��̍쐬
	BoxCollider* pCollider = m_pCharacter->GetCharacterCollider();
	CVector3 ColliderPos = m_pCharacterParameter->Pos + CVector3::GetUp() * (pCollider->GetSize().y * 0.5f);	

	switch (m_pCharacter->GetLook())
	{
	case Character::LOOKDIR::RIGHT:
		ColliderPos = ColliderPos +
			CVector3(0.7f,0.4f,0.0f);
		break;
	case Character::LOOKDIR::LEFT:
		ColliderPos = ColliderPos + 
			CVector3(-0.7f,0.4f,0.0f);
		break;
	};

	CVector3 ColliderSize = CVector3(1.0f, 0.9f, 1.0f);

	Character::ATTACKPARAM Attack;
	Attack.m_Use = false;
	Attack.m_BoxCollider.CreateBox(BoxCollider::BOXTYPE::CENTER,
		ColliderPos, ColliderSize);
	Attack.m_CanAttackCharacterBit = 0xffffffff;					//������L�����N�^�[�̐ݒ�

	m_pAttackCollider->push_back(Attack);

	m_pModelDrawer->PlayAnime("Pose2", true);

	m_PushButton = false;
}

void Character00_Attack11::Uninit()
{
	m_pAttackCollider->clear();
}

void Character00_Attack11::Update()
{
	//============<�U���𓖂Ă邩�̐ݒ�>===================
	//���܂œ����������Ƃ̂���L�����N�^�[�ɂ͓��ĂȂ�
	(*m_pAttackCollider)[0].m_CanAttackCharacterBit = ~(*m_pAttackCollider)[0].m_haveHitCharacterBit;
	//=====================================================

	const int AnimeAllFrame = 16;								//�A�j���[�V�����S�̂̃t���[��
	const int EndFrame = 30;									//�U���I������
	const float AnimeStartTime = 1.145f;						//�A�j���[�V�����J�n����
	const float AnimeEndTime = 1.193f;							//�A�j���[�V�����I������
	const float AnimeAllTime = AnimeEndTime - AnimeStartTime;	//�A�j���[�V�����̎���
	
	m_FrameCount++;

	//�A�j���[�V�����̍Đ����Ԃ̍X�V
	m_AnimeTime = static_cast<float>(m_FrameCount) / static_cast<float>(AnimeAllFrame) * AnimeAllTime + AnimeStartTime;

	//�A�j���[�V�������I������ׂ����Ԃ𒴂��Ă����ꍇ
	if (m_AnimeTime > AnimeEndTime)
	{
		m_AnimeTime = AnimeEndTime;
	}

	//�����蔻��J�n
	if (m_FrameCount == 6)					
	{
		(*m_pAttackCollider)[0].m_Use = true;
	}

	//�����蔻��I��
	if (m_FrameCount == 20)					
	{
		(*m_pAttackCollider)[0].m_Use = false;
	}

	//�{�^�������̃t���[���̊Ԃɉ����Ă���Ǝ��̍U���Ɍ�����
	if (m_FrameCount > 5 && m_FrameCount < EndFrame)
	{
		if (m_pController->GetAttack())
		{
			m_PushButton = true;
		}
	}

	//���̃t���[���̊Ԃňړ�����Ȃ�ړ�����
	if (m_FrameCount > 10 && m_FrameCount < EndFrame)	
	{
		//�U��
		if (m_PushButton)	
		{
			m_pCharacter->SetNextState(Character::STATE::State_Attack12); //��̐ݒ�
		}
	}

	//�t���[�����ƂɃC�x���g��ݒ肷��
	if (m_FrameCount >= EndFrame)		
	{
		m_pCharacter->SetNextState(Character::STATE::State_Idle);
	}

	//�A�j���[�V�����̍Đ����Ԃ̐ݒ�
	m_pModelDrawer->SetAnimeTime(m_AnimeTime);
}

void Character00_Attack11::HitCharacter(Character* pHitCharacter)
{
	pHitCharacter->AddDamage(2.0f);								//�_���[�W�̉��Z
	CharacterBase_HitStopState* pHitStopState =
	static_cast<CharacterBase_HitStopState*>(pHitCharacter->SetNextState(Character::STATE::State_HitStop));
	pHitCharacter->ChangeNextState();
	pHitStopState->SetHitStop(5, Character::STATE::State_LeanBack,true);	//�q�b�g�X�g�b�v�̐ݒ�
}
