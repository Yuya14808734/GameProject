#include "Character_00.h"

void Character_00::AttackSD_Init()
{
	m_FrameCount = 0;
	m_AnimeTime = 0.375f;

	//�����蔻��̍쐬
	CVector3 ColliderPos = m_pos + CVector3::GetUp() * (m_CharacterCollider.GetSize().y * 0.5f);
	float Rotate = 0.0f;

	switch (m_NowLookDir)
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

	ATTACKPARAM Attack;
	Attack.m_Use = false;
	Attack.m_BoxCollider.CreateBox(BoxCollider::BOXTYPE::CENTER,
		ColliderPos, m_pos , CVector3(1.7f, 2.7f, 1.0f));
	Attack.m_CanAttackCharacterBit = 0xffffffff;					//������L�����N�^�[�̐ݒ�

	m_AttackCollider.push_back(Attack);

	m_CharacterModel.PlayAnime("Slide00", true);

	m_PushButton = false;
}

void Character_00::AttackSD_Update()
{
	//============<�U���𓖂Ă邩�̐ݒ�>===================
	//���܂œ����������Ƃ̂���L�����N�^�[�ɂ͓��ĂȂ�
	m_AttackCollider[0].m_CanAttackCharacterBit = ~m_AttackCollider[0].m_haveHitCharacterBit;
	//=====================================================

	const int AnimeAllFrame = 16;								//�A�j���[�V�����S�̂̃t���[��
	const int EndFrame = 30;									//�U���I������
	const float AnimeStartTime = 0.375f;						//�A�j���[�V�����J�n����
	const float AnimeEndTime = 1.417f;							//�A�j���[�V�����I������
	const float AnimeAllTime = AnimeEndTime - AnimeStartTime;	//�A�j���[�V�����̎���

	m_FrameCount++;

	m_AttackCollider[0].m_BoxCollider.SetBasePos(m_pos);

	//�A�j���[�V�����̍Đ����Ԃ̍X�V
	m_AnimeTime = static_cast<float>(m_FrameCount) / static_cast<float>(AnimeAllFrame) * AnimeAllTime + AnimeStartTime;

	//�A�j���[�V�����̍Đ����Ԃ̐ݒ�
	m_CharacterModel.SetAnimeTime(m_AnimeTime);

	m_MoveVector.y = 0.0f;

	switch (m_NowLookDir)
	{
	case Character::LOOKDIR::RIGHT:
		m_MoveVector.x = m_MoveParameter.m_DashSpeed * 0.8f;
		break;
	case Character::LOOKDIR::LEFT:
		m_MoveVector.x = m_MoveParameter.m_DashSpeed * -0.8f;
		break;
	}

	m_pos += m_MoveVector;

	//�t���[�����ƂɃC�x���g��ݒ肷��
	if (m_FrameCount >= EndFrame)
	{
		ChangeState(Character::STATE::IDLE);
	}
}

void Character_00::AttackSD_Uninit()
{
	m_AttackCollider.clear();
}

void Character_00::AttackSD_Hit(Character* HitCharacter)
{

}