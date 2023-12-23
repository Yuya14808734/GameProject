#include "Character_00.h"

void Character_00::Attack13_Init()
{
	m_AttackTime = 0;
	m_AnimeTime = 0.935f;

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
		ColliderPos, CVector3(1.7f, 2.7f, 1.0f));
	Attack.m_CanAttackCharacterBit = 0xffffffff;					//������L�����N�^�[�̐ݒ�


	m_AttackCollider.push_back(Attack);

	m_CharacterModel.PlayAnime("WAIT04", true);
}

void Character_00::Attack13_Update()
{
	//============<�U���𓖂Ă邩�̐ݒ�>===================
	//���܂œ����������Ƃ̂���L�����N�^�[�ɂ͓��ĂȂ�
	m_AttackCollider[0].m_CanAttackCharacterBit = ~m_AttackCollider[0].m_haveHitCharacterBit;
	//=====================================================

	const int AnimeEndFrame = 30;			//�A�j���[�V�������~����t���[��
	const int EndFrame = 30;				//���̃A�^�b�N���I���t���[��
	const float AnimeStartTime = 0.935f;	//�A�j���[�V�����̎n�߂鎞��
	const float AnimeEndTime = 2.069f;		//�A�j���[�V�������I��鎞��
	const float AnimeAllTime = AnimeEndTime - AnimeStartTime;	//�A�j���[�V�����̎���

	m_AttackTime++;
	m_AnimeTime = static_cast<float>(m_AttackTime) / static_cast<float>(AnimeEndFrame) * AnimeAllTime + AnimeStartTime;

	if (m_AnimeTime > AnimeEndTime)
	{
		m_AnimeTime = AnimeEndTime;
	}

	if (m_AttackTime == 8)
	{
		m_AttackCollider[0].m_Use = true;
	}

	if (m_AttackTime == 12)
	{
		m_AttackCollider[0].m_Use = false;
	}

	//�t���[�����ƂɃC�x���g��ݒ肷��
	if (m_AttackTime >= EndFrame)
	{
		ChangeState(Character::STATE::IDLE);
	}

	m_CharacterModel.SetAnimeTime(m_AnimeTime);
}

void Character_00::Attack13_Uninit()
{
	m_AttackCollider.clear();
}

void Character_00::Attack13_Hit(Character* HitCharacter)
{
	HitCharacter->AddDamage(5.0f);								//�_���[�W�̉��Z
	float ForcePower = (HitCharacter->GetDamage() / 100.0f) * 0.5f + 0.3f;			//�_���[�W���琁����΂��x�N�g���̌v�Z

	CVector3 AddVec = CVector2::GetAngleVector(
		m_NowLookDir == Character::LOOKDIR::RIGHT ? -70.0f : 70.0f
	) * ForcePower;
	HitCharacter->AddForce(AddVec); 
	HitCharacter->SetHitStop(5, Character::STATE::BLOWAWAY);
	HitCharacter->SetShake(true);
	if (m_NowLookDir == Character::LOOKDIR::RIGHT)
	{
		HitCharacter->SetLookLeft();
	}
	else
	{
		HitCharacter->SetLookRight();
	}
}
