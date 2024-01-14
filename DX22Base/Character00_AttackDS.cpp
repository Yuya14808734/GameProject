#include "Character00_AttackDS.h"
#include "CharacterBase_HitStopState.h"

void Character00_AttackDS::Init()
{
	m_FrameCount = 0;
	m_AnimeTime = 0.375f;

	//�����蔻��̍쐬
	CVector3 ColliderBasePos = m_pCharacterParameter->Pos;
	CVector3 ShiftVec = m_pCharacterCollider->GetSize();
	
	CVector3 ColliderSize(
	m_pCharacterCollider->GetSize().y,
		m_pCharacterCollider->GetSize().x,
		m_pCharacterCollider->GetSize().z);

	switch (m_pCharacter->GetLook())
	{
	case Character::LOOKDIR::RIGHT:
		ShiftVec.x = ShiftVec.x * 0.5f;
		ShiftVec.y = ShiftVec.y * 0.3f;
		break;
	case Character::LOOKDIR::LEFT:
		ShiftVec.x = ShiftVec.x * -0.5f;
		ShiftVec.y = ShiftVec.y * 0.3f;
		break;
	}

	//�U���̓����蔻��̐ݒ�
	Character::ATTACKPARAM Attack;
	Attack.m_Use = false;
	Attack.m_BoxCollider.CreateBox(BoxCollider::BOXTYPE::FOOT,
		m_pCharacterParameter->Pos, ColliderSize);// , ShiftVec);
	Attack.m_CanAttackCharacterBit = 0xffffffff;					//������L�����N�^�[�̐ݒ�

	(*m_pAttackCollider).push_back(Attack);

	m_pModelDrawer->PlayAnime("Slide00", true);

	m_HitStopCount = 0;

	m_pCharacterParameter->Velocity = m_pCharacterParameter->MoveVector;
	m_pCharacterParameter->MoveVector = CVector3::GetZero();
}

void Character00_AttackDS::Update()
{
	//�n�ʂɓ�����ƃA�C�h����Ԃɕς���
	if (!m_pCharacterParameter->HitGround)
	{
		m_pCharacter->SetNextState(Character::STATE::State_AirMove);
	}

	//============<�U���𓖂Ă邩�̐ݒ�>===================
	//���܂œ����������Ƃ̂���L�����N�^�[�ɂ͓��ĂȂ�
	(*m_pAttackCollider)[0].m_CanAttackCharacterBit = ~(*m_pAttackCollider)[0].m_haveHitCharacterBit;
	//=====================================================

	//============<�U���𓖂Ă���Ƀq�b�g�X�g�b�v���s����>========
	//�O�̃t���[���ŒN���ɓ��������ꍇ
	if ((*m_pAttackCollider)[0].m_HitTriggerCharacterBit != 0x00)
	{
		m_HitStopCount = m_HitStopFrame;
	}

	//�U���𓖂Ă��q�b�g�X�g�b�v���I���܂œ����Ȃ�
	if (m_HitStopCount > 0)
	{
		m_HitStopCount--;

		//�n�ʂɓ������Ă��Ȃ�����ɂȂ�̂ŏd�͂𑫂��Ă��
		m_pCharacterParameter->Velocity.y += m_pJumpParameter->FallDownGravity;

		//�ŏI�I�Ȉʒu��ݒ�
		m_pCharacterParameter->Pos += m_pCharacterParameter->Velocity;
		(*m_pAttackCollider)[0].m_BoxCollider.SetBasePos(m_pCharacterParameter->Pos);
		return;
	}
	//======================================================================
	
	//============<�A�j���[�V�����̎��Ԃ�ݒ�>==============================
	const int AnimeAllFrame = 30;								//�A�j���[�V�����S�̂̃t���[��
	const int EndFrame = 30;									//�U���I������
	const float AnimeStartTime = 0.375f;						//�A�j���[�V�����J�n����
	const float AnimeEndTime = 1.417f;							//�A�j���[�V�����I������
	const float AnimeAllTime = AnimeEndTime - AnimeStartTime;	//�A�j���[�V�����̎���

	m_FrameCount++;

	//�t���[�����ƂɃC�x���g��ݒ肷��
	if (m_FrameCount >= EndFrame)
	{
		m_pCharacter->SetNextState(Character::STATE::State_Idle);
	}

	//�A�j���[�V�����̍Đ����Ԃ̍X�V
	m_AnimeTime = static_cast<float>(m_FrameCount) / static_cast<float>(AnimeAllFrame) * AnimeAllTime + AnimeStartTime;

	if (m_AnimeTime > AnimeEndTime)
	{
		m_AnimeTime = AnimeEndTime;
	}

	//�A�j���[�V�����̍Đ����Ԃ̐ݒ�
	m_pModelDrawer->SetAnimeTime(m_AnimeTime);
	//======================================================================

	//============<�����蔻��̐ݒ�>=======================================
	if (m_FrameCount == 5)
	{
		(*m_pAttackCollider)[0].m_Use = true;
	}

	if (m_FrameCount == 24)
	{
		(*m_pAttackCollider)[0].m_Use = false;
	}
	
	//======================================================================
	
	//============<�ړ�����>===============================================
	m_pCharacterParameter->Velocity.x *= 0.99f;
	m_pCharacterParameter->Velocity.y += m_pJumpParameter->FallDownGravity;

	//�ŏI�I�Ȉʒu��ݒ�
	m_pCharacterParameter->Pos += m_pCharacterParameter->Velocity;
	(*m_pAttackCollider)[0].m_BoxCollider.SetBasePos(m_pCharacterParameter->Pos);
	//======================================================================

	
}

void Character00_AttackDS::Uninit()
{
	(*m_pAttackCollider).clear();
}

void Character00_AttackDS::HitCharacter(Character* pHitCharacter)
{
	//�_���[�W�̉��Z
	pHitCharacter->AddDamage(15.0f);

	//�����グ�Ēn�ʂɓ������Ă��Ȃ����Ƃɂ���
	pHitCharacter->SetPos(pHitCharacter->GetPos() + CVector3::GetUp() * 0.1f);

	//�_���[�W���琁����΂��x�N�g���̌v�Z
	float ForcePower = (pHitCharacter->GetDamage() / 100.0f) * 0.5f + 0.3f;
	//������΂��x�N�g����ݒ�
	CVector3 AddVec = CVector2::GetAngleVector(
		m_pCharacter->GetLook() == Character::LOOKDIR::RIGHT ? -20.0f : 20.0f
	) * ForcePower;
	pHitCharacter->AddForce(AddVec);

	//�q�b�g�X�g�b�v�̐ݒ�
	CharacterBase_HitStopState* pHitStopState =
		static_cast<CharacterBase_HitStopState*>(pHitCharacter->SetNextState(Character::STATE::State_HitStop));
	pHitCharacter->ChangeNextState();
	pHitStopState->SetHitStop(m_HitStopFrame, Character::STATE::State_BlowAway, true);	//�q�b�g�X�g�b�v�̐ݒ�
	m_HitStopCount = m_HitStopFrame;
}