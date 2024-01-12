#include "Character00_AttackS2.h"
#include "CharacterBase_HitStopState.h"

void Character00_AttackS2::Init()
{
	m_FrameCount = 0;
	m_AnimeTime = 0.332f;

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

	Character::ATTACKPARAM Attack;												//�U���p�����[�^�[�̐ݒ�
	Attack.m_Use = false;											//�U�������蔻�肷�邩
	Attack.m_BoxCollider.CreateBox(BoxCollider::BOXTYPE::CENTER,	//�����蔻��͈̔͐ݒ�
		ColliderPos	, CVector3(1.7f, 2.7f, 1.0f));
	Attack.m_CanAttackCharacterBit = 0xffffffff;					//������L�����N�^�[�̐ݒ�

	m_pAttackCollider->push_back(Attack);

	m_SwordHandle = EffectManager::GetManager()->Play(EffectManager::GetEffect("C00_S2"),0,0,0);
	EffectManager::GetManager()->SetLocation(m_SwordHandle, { ColliderPos.x,ColliderPos.y,ColliderPos.z });
	EffectManager::GetManager()->SetScale(m_SwordHandle, 1.0f,1.0f,1.0f);
	EffectManager::GetManager()->SetRotation(m_SwordHandle, 
		0.0f,
		Rotate
		,0.0f);

	m_pModelDrawer->PlayAnime("Umatobi", true);

	m_HitAttackStopCount = 0;
}

void Character00_AttackS2::Uninit()
{
	m_HitAttackStopCount = 0;

	EffectManager::GetManager()->StopEffect(m_SwordHandle);

	m_pAttackCollider->clear();
}

void Character00_AttackS2::Update()
{
	//============<�U���𓖂Ă邩�̐ݒ�>====================================
	
	//���܂œ����������Ƃ̂���L�����N�^�[�ɂ͓��ĂȂ�
	(*m_pAttackCollider)[0].m_CanAttackCharacterBit = ~(*m_pAttackCollider)[0].m_haveHitCharacterBit;

	//�O�̃t���[���ŒN���ɓ��������ꍇ
	if ((*m_pAttackCollider)[0].m_HitTriggerCharacterBit != 0x00)
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

	m_FrameCount++;
	float AnimeAllTime = 0.938f - 0.332f;
	m_AnimeTime = static_cast<float>(m_FrameCount) / 24.0f  * AnimeAllTime + 0.332f;

	if (m_FrameCount == 6)
	{
		(*m_pAttackCollider)[0].m_Use = true;
	}

	if (m_FrameCount == 16)
	{
		(*m_pAttackCollider)[0].m_Use = false;
	}

	//�t���[�����ƂɃC�x���g��ݒ肷��
	if(m_FrameCount >= 24)
	{
		m_pCharacter->SetNextState(Character::STATE::State_Idle);
	}

	if (m_AnimeTime > 0.938f)
	{
		m_AnimeTime = 0.938f;
	}

	m_pModelDrawer->SetAnimeTime(m_AnimeTime);
}

void Character00_AttackS2::HitCharacter(Character* pHitCharacter)
{
	pHitCharacter->AddDamage(13.0f);											//�_���[�W�̉��Z

	float ForcePower = (pHitCharacter->GetDamage() / 100.0f) + 0.7f;			//�_���[�W���琁����΂��x�N�g���̌v�Z
	CVector3 AddVec = CVector2::GetAngleVector(
		m_pCharacter->GetLook() == Character::LOOKDIR::RIGHT ? -70.0f : 70.0f
	) * ForcePower;
	pHitCharacter->AddForce(AddVec);
	CharacterBase_HitStopState* pHitStopState =
		static_cast<CharacterBase_HitStopState*>(pHitCharacter->SetNextState(Character::STATE::State_HitStop));
	pHitCharacter->ChangeNextState();
	pHitStopState->SetHitStop(5, Character::STATE::State_BlowAway, true);	//�q�b�g�X�g�b�v�̐ݒ�

	if(m_pCharacter->GetLook() == Character::LOOKDIR::RIGHT)
	{
		pHitCharacter->SetLookLeft();
	}
	else
	{
		pHitCharacter->SetLookRight();
	}
}
