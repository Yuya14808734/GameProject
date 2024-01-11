#include "Character00_AttackDS.h"

void Character00_AttackDS::Init()
{
	m_FrameCount = 0;
	m_AnimeTime = 0.375f;

	//�����蔻��̍쐬
	CVector3 ColliderPos = m_pCharacterParameter->Pos + CVector3::GetUp() * (m_pCharacterCollider->GetSize().y * 0.5f);
	float Rotate = 0.0f;

	switch (m_pCharacter->GetLook())
	{
	case Character::LOOKDIR::RIGHT:
		ColliderPos = ColliderPos + CVector3::GetRight() * 1.5f;
		Rotate = 3.14f;
		break;
	case Character::LOOKDIR::LEFT:
		ColliderPos = ColliderPos + CVector3::GetRight() * -1.5f;
		Rotate = 0.0f;
		break;
	default:
		break;
	}

	Character::ATTACKPARAM Attack;
	Attack.m_Use = false;
	Attack.m_BoxCollider.CreateBox(BoxCollider::BOXTYPE::CENTER,
		ColliderPos, m_pCharacterParameter->Pos, CVector3(1.7f, 2.7f, 1.0f));
	Attack.m_CanAttackCharacterBit = 0xffffffff;					//������L�����N�^�[�̐ݒ�

	(*m_pAttackCollider).push_back(Attack);

	m_pModelDrawer->PlayAnime("Slide00", true);

	m_PushButton = false;
}

void Character00_AttackDS::Update()
{
	//============<�U���𓖂Ă邩�̐ݒ�>===================
	//���܂œ����������Ƃ̂���L�����N�^�[�ɂ͓��ĂȂ�
	(*m_pAttackCollider)[0].m_CanAttackCharacterBit = ~(*m_pAttackCollider)[0].m_haveHitCharacterBit;
	//=====================================================

	const int AnimeAllFrame = 16;								//�A�j���[�V�����S�̂̃t���[��
	const int EndFrame = 30;									//�U���I������
	const float AnimeStartTime = 0.375f;						//�A�j���[�V�����J�n����
	const float AnimeEndTime = 1.417f;							//�A�j���[�V�����I������
	const float AnimeAllTime = AnimeEndTime - AnimeStartTime;	//�A�j���[�V�����̎���

	m_FrameCount++;

	(*m_pAttackCollider)[0].m_BoxCollider.SetBasePos(m_pCharacterParameter->Pos);

	//�A�j���[�V�����̍Đ����Ԃ̍X�V
	m_AnimeTime = static_cast<float>(m_FrameCount) / static_cast<float>(AnimeAllFrame) * AnimeAllTime + AnimeStartTime;

	//�A�j���[�V�����̍Đ����Ԃ̐ݒ�
	m_pModelDrawer->SetAnimeTime(m_AnimeTime);

	m_pCharacterParameter->MoveVector.y = 0.0f;

	switch (m_pCharacter->GetLook())
	{
	case Character::LOOKDIR::RIGHT:
		m_pCharacterParameter->MoveVector.x = m_pMoveParameter->DashSpeed * 0.8f;
		break;
	case Character::LOOKDIR::LEFT:
		m_pCharacterParameter->MoveVector.x = m_pMoveParameter->DashSpeed * -0.8f;
		break;
	}

	m_pCharacterParameter->Pos += m_pCharacterParameter->MoveVector;

	//�t���[�����ƂɃC�x���g��ݒ肷��
	if (m_FrameCount >= EndFrame)
	{
		m_pCharacter->SetNextState(Character::STATE::State_Idle);
	}
}

void Character00_AttackDS::Uninit()
{
	(*m_pAttackCollider).clear();
}

void Character00_AttackDS::HitCharacter(Character* pHitCharacter)
{

}