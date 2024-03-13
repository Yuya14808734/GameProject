#include "Character00_Attack12.h"
#include "Input.h"
#include "XboxKeyboard.h"
#include "CharacterBase_HitStopState.h"
#include "SoundManager.h"

void Character00_Attack12::Init()
{
	m_FrameCount = 0;
	m_AnimeTime = 0.88f;

	//�����蔻��̍쐬
	CVector3 ColliderPos = m_pCharacterParameter->Pos + CVector3::GetUp() * (m_pCharacterCollider->GetSize().y * 0.5f);

	switch (m_pCharacter->GetLook())
	{
	case Character::LOOKDIR::RIGHT:
		ColliderPos = ColliderPos +
			CVector3(0.7f, 0.2f, 0.0f);
		break;
	case Character::LOOKDIR::LEFT:
		ColliderPos = ColliderPos +
			CVector3(-0.7f, 0.2f, 0.0f);
		break;
	};

	CVector3 ColliderSize = CVector3(1.3f, 1.0f, 1.0f);

	Character::ATTACKPARAM Attack;
	Attack.m_Use = false;
	Attack.m_BoxCollider.CreateBox(BoxCollider::BOXTYPE::CENTER,
		ColliderPos, ColliderSize);
	Attack.m_CanAttackCharacterBit = 0xffffffff;					//������L�����N�^�[�̐ݒ�


	m_pAttackCollider->push_back(Attack);

	m_pModelDrawer->PlayAnime("Pose2", true);

	m_PushButton = false;

	SoundManager::PlaySE("MissPunch01");
}

void Character00_Attack12::Uninit()
{
	m_pAttackCollider->clear();
}

void Character00_Attack12::Update()
{
	//============<�U���𓖂Ă邩�̐ݒ�>===================
	//���܂œ����������Ƃ̂���L�����N�^�[�ɂ͓��ĂȂ�
	(*m_pAttackCollider)[0].m_CanAttackCharacterBit = ~(*m_pAttackCollider)[0].m_haveHitCharacterBit;
	//=====================================================

	const int AnimeFrame = 15;
	const int EndFrame = 30;
	const float AnimeStartTime = 0.88f;
	const float AnimeEndTime = 0.932f;
	const float AnimeAllTime = AnimeEndTime - AnimeStartTime;

	m_FrameCount++;
	m_AnimeTime = static_cast<float>(m_FrameCount) / static_cast<float>(AnimeFrame) * AnimeAllTime + AnimeStartTime;

	if (m_AnimeTime > AnimeEndTime)
	{
		m_AnimeTime = AnimeEndTime;
	}

	if (m_FrameCount == 6)
	{
		(*m_pAttackCollider)[0].m_Use = true;
	}

	if (m_FrameCount == 18)
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
	if (m_FrameCount > 12 && m_FrameCount < EndFrame)
	{
		//�U��
		if (m_PushButton)
		{
			m_pCharacter->SetNextState(Character::STATE::State_Attack13);	//��̐ݒ�
		}
	}

	//�t���[�����ƂɃC�x���g��ݒ肷��
	if (m_FrameCount >= EndFrame)
	{
		m_pCharacter->SetNextState(Character::STATE::State_Idle);
	}

	m_pModelDrawer->SetAnimeTime(m_AnimeTime);
}



void Character00_Attack12::HitCharacter(Character* pHitCharacter, Character::ATTACKPARAM* pHitAttack)
{
	SoundManager::PlaySE("HitPunch02");

	pHitCharacter->AddDamage(3.0f);								//�_���[�W�̉��Z
	CharacterBase_HitStopState* pHitStopState =
		static_cast<CharacterBase_HitStopState*>(pHitCharacter->SetNextState(Character::STATE::State_HitStop));
	pHitCharacter->ChangeNextState();
	pHitStopState->SetHitStop(5, Character::STATE::State_LeanBack, true);	//�q�b�g�X�g�b�v�̐ݒ�
}
