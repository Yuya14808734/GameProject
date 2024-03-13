#include "Character00_Attack13.h"
#include "CharacterBase_HitStopState.h"
#include "SoundManager.h"
#include "Scene00_Game.h"
#include "Effect04_HitSmall.h"

void Character00_Attack13::Init()
{
	m_FrameCount = 0;
	m_AnimeTime = 0.935f;

	//�����蔻��̍쐬
	CVector3 ColliderPos = m_pCharacterParameter->Pos + CVector3::GetUp() * (m_pCharacterCollider->GetSize().y * 0.5f);

	switch (m_pCharacter->GetLook())
	{
	case Character::LOOKDIR::RIGHT:
		ColliderPos = ColliderPos +
			CVector3(0.9f, 0.2f, 0.0f);
		break;
	case Character::LOOKDIR::LEFT:
		ColliderPos = ColliderPos +
			CVector3(-0.9f, 0.2f, 0.0f);
		break;
	};

	CVector3 ColliderSize = CVector3(1.5f, 1.0f, 1.0f);

	Character::ATTACKPARAM Attack;
	Attack.m_Use = false;
	Attack.m_BoxCollider.CreateBox(BoxCollider::BOXTYPE::CENTER,
		ColliderPos, ColliderSize);
	Attack.m_CanAttackCharacterBit = 0xffffffff;					//������L�����N�^�[�̐ݒ�


	(*m_pAttackCollider).push_back(Attack);

	m_pModelDrawer->PlayAnime("WAIT04", true);

	SoundManager::PlaySE("MissKick01");
}

void Character00_Attack13::Update()
{
	//============<�U���𓖂Ă邩�̐ݒ�>===================
	//���܂œ����������Ƃ̂���L�����N�^�[�ɂ͓��ĂȂ�
	(*m_pAttackCollider)[0].m_CanAttackCharacterBit = ~(*m_pAttackCollider)[0].m_haveHitCharacterBit;
	//=====================================================

	const int AnimeEndFrame = 30;			//�A�j���[�V�������~����t���[��
	const int EndFrame = 30;				//���̃A�^�b�N���I���t���[��
	const float AnimeStartTime = 0.935f;	//�A�j���[�V�����̎n�߂鎞��
	const float AnimeEndTime = 2.069f;		//�A�j���[�V�������I��鎞��
	const float AnimeAllTime = AnimeEndTime - AnimeStartTime;	//�A�j���[�V�����̎���

	m_FrameCount++;
	m_AnimeTime = static_cast<float>(m_FrameCount) / static_cast<float>(AnimeEndFrame) * AnimeAllTime + AnimeStartTime;

	if (m_AnimeTime > AnimeEndTime)
	{
		m_AnimeTime = AnimeEndTime;
	}

	if (m_FrameCount == 8)
	{
		(*m_pAttackCollider)[0].m_Use = true;
	}

	if (m_FrameCount == 12)
	{
		(*m_pAttackCollider)[0].m_Use = false;
	}

	//�t���[�����ƂɃC�x���g��ݒ肷��
	if (m_FrameCount >= EndFrame)
	{
		m_pCharacter->SetNextState(Character::STATE::State_Idle);
	}

	m_pModelDrawer->SetAnimeTime(m_AnimeTime);
}

void Character00_Attack13::Uninit()
{
	m_pAttackCollider->clear();
}

void Character00_Attack13::HitCharacter(Character* pHitCharacter, Character::ATTACKPARAM* pHitAttack)
{
	SoundManager::PlaySE("HitKick01");

	//�_���[�W�̉��Z
	pHitCharacter->AddDamage(5.0f);		

	//�_���[�W���琁����΂��x�N�g���̌v�Z
	float ForcePower = (pHitCharacter->GetDamage() / 100.0f) * 0.5f + 0.3f;			

	//�����グ�Ēn�ʂɓ������Ă��Ȃ����Ƃɂ���
	pHitCharacter->SetPos(pHitCharacter->GetPos() + CVector3::GetUp() * 0.1f);	
	
	//������΂��x�N�g����ݒ�
	CVector3 AddVec = CVector2::GetAngleVector(
		m_pCharacter->GetLook() == Character::LOOKDIR::RIGHT ? -70.0f : 70.0f
	) * ForcePower;
	pHitCharacter->AddForce(AddVec);

	//�q�b�g�X�g�b�v�̐ݒ�
	CharacterBase_HitStopState* pHitStopState =
		static_cast<CharacterBase_HitStopState*>(pHitCharacter->SetNextState(Character::STATE::State_HitStop));
	pHitCharacter->ChangeNextState();
	pHitStopState->SetHitStop(5, Character::STATE::State_BlowAway, true);	//�q�b�g�X�g�b�v�̐ݒ�
	
	if (m_pCharacter->GetLook() == Character::LOOKDIR::RIGHT)
	{
		pHitCharacter->SetLookLeft();
	}
	else
	{
		pHitCharacter->SetLookRight();
	}

	//�G�t�F�N�g
	SceneGame* pGameScene = static_cast<SceneGame*>(CScene::GetScene());

	EffectHitSmall* pEfk_HitSmall = new EffectHitSmall();
	pEfk_HitSmall->PlayHitEffect(
		pHitCharacter->GetPos() + (CVector3::GetUp() * pHitCharacter->GetCharacterCollider()->GetSize().y * 0.7f)
	);

	pGameScene->GetEffectVector()->push_back(pEfk_HitSmall);
}
