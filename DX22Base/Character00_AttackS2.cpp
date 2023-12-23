#include "Character_00.h"

void Character_00::AttackS2_Init()
{
	m_AttackTime = 0;
	m_AnimeTime = 0.332f;

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

	ATTACKPARAM Attack;												//�U���p�����[�^�[�̐ݒ�
	Attack.m_Use = false;											//�U�������蔻�肷�邩
	Attack.m_BoxCollider.CreateBox(BoxCollider::BOXTYPE::CENTER,	//�����蔻��͈̔͐ݒ�
		ColliderPos	, CVector3(1.7f, 2.7f, 1.0f));
	Attack.m_CanAttackCharacterBit = 0xffffffff;					//������L�����N�^�[�̐ݒ�

	m_AttackCollider.push_back(Attack);

	m_SwordHandle = EffectManager::GetManager()->Play(EffectManager::GetEffect("C00_S2"),0,0,0);
	EffectManager::GetManager()->SetLocation(m_SwordHandle, { ColliderPos.x,ColliderPos.y,ColliderPos.z });
	EffectManager::GetManager()->SetScale(m_SwordHandle, 1.0f,1.0f,1.0f);
	EffectManager::GetManager()->SetRotation(m_SwordHandle, 
		0.0f,
		Rotate
		,0.0f);

	m_CharacterModel.PlayAnime("Umatobi", true);

	m_HitAttackStopCount = 0;
}

void Character_00::AttackS2_Uninit()
{
	m_HitAttackStopCount = 0;

	EffectManager::GetManager()->StopEffect(m_SwordHandle);

	m_AttackCollider.clear();
}

void Character_00::AttackS2_Update()
{
	//============<�U���𓖂Ă邩�̐ݒ�>====================================
	
	//���܂œ����������Ƃ̂���L�����N�^�[�ɂ͓��ĂȂ�
	m_AttackCollider[0].m_CanAttackCharacterBit = ~m_AttackCollider[0].m_haveHitCharacterBit;

	//�O�̃t���[���ŒN���ɓ��������ꍇ
	if (m_AttackCollider[0].m_HitTriggerCharacterBit != 0x00)
	{
		m_HitAttackStopCount = 30;
		EffectManager::GetManager()->SetPaused(m_SwordHandle, true);
	}

	//�U���𓖂Ă��q�b�g�X�g�b�v���I���܂œ����Ȃ�
	if (m_HitAttackStopCount > 0)
	{
		m_HitAttackStopCount--;

		//�U���������������̃X�g�b�v��������
		if (m_HitAttackStopCount == 0)
		{
			EffectManager::GetManager()->SetPaused(m_SwordHandle, false);
		}

		return;
	}

	//======================================================================

	m_AttackTime++;
	float AnimeAllTime = 0.938f - 0.332f;
	m_AnimeTime = static_cast<float>(m_AttackTime) / 24.0f  * AnimeAllTime + 0.332f;

	if (m_AttackTime == 6)
	{
		m_AttackCollider[0].m_Use = true;
	}

	if (m_AttackTime == 16)
	{
		m_AttackCollider[0].m_Use = false;
	}

	//�t���[�����ƂɃC�x���g��ݒ肷��
	if(m_AttackTime >= 24)
	{
		ChangeState(Character::STATE::IDLE);
	}

	if (m_AnimeTime > 0.938f)
	{
		m_AnimeTime = 0.938f;
	}

	m_CharacterModel.SetAnimeTime(m_AnimeTime);
}

void Character_00::AttackS2_Hit(Character* HitCharacter)
{
	HitCharacter->AddDamage(13.0f);											//�_���[�W�̉��Z

	float ForcePower = (HitCharacter->GetDamage() / 100.0f) + 0.7f;			//�_���[�W���琁����΂��x�N�g���̌v�Z
	CVector3 AddVec = CVector2::GetAngleVector(
		m_NowLookDir == Character::LOOKDIR::RIGHT ? -70.0f : 70.0f
	) * ForcePower;
	HitCharacter->AddForce(AddVec);
	HitCharacter->SetHitStop(30,Character::STATE::BLOWAWAY);
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
