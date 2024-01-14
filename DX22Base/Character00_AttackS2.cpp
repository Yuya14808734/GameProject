#include "Character00_AttackS2.h"
#include "CharacterBase_HitStopState.h"

void Character00_AttackS2::Init()
{
	m_FrameCount = 0;
	m_AnimeTime = 0.332f;

	//�����蔻��̍쐬
	const float DirectValue = m_pCharacter->GetLook() == Character::LOOKDIR::RIGHT ?
		1.0f: -1.0f;
	CVector3 ColliderBasePos = m_pCharacterParameter->Pos;
	ColliderBasePos.x = ColliderBasePos.x;
	ColliderBasePos.y = ColliderBasePos.y + (m_pCharacterCollider->GetSize().y * 0.6f);
	ColliderBasePos.z = ColliderBasePos.z;
	CVector3 ColliderSplitSize = CVector3(1.0f, 1.0f, 1.0f);
	const int StartAngle = 20;
	const int EndAngle = 200;
	const int RotateAngle = 30;
	const float Radius = 1.7f;

	for(int Angle = StartAngle;Angle <= EndAngle; Angle += RotateAngle)
	{
		float Radian = DirectX::XMConvertToRadians(static_cast<float>(Angle));

		//�����蔻��̈ʒu��ݒ�
			CVector3 ColliderSplitPos = CVector3(
				sinf(Radian * DirectValue),
				cosf(Radian * DirectValue),
				0.0f) * Radius;

		Character::ATTACKPARAM Attack;
		Attack.m_Use = false; 
		Attack.m_BoxCollider.CreateBox(BoxCollider::BOXTYPE::CENTER,
			ColliderBasePos, ColliderSplitSize, ColliderSplitPos);
		Attack.m_CanAttackCharacterBit = 0xffffffff;					//������L�����N�^�[�̐ݒ�
		m_pAttackCollider->push_back(Attack);
	};	

	m_SwordHandle = EffectManager::GetManager()->Play(EffectManager::GetEffect("C00_S2"),0,0,0);
	EffectManager::GetManager()->SetLocation(m_SwordHandle, 
		{ m_pCharacterParameter->Pos.x + (1.5f * DirectValue),
		m_pCharacterParameter->Pos.y + (m_pCharacterCollider->GetSize().y * 0.5f),
		m_pCharacterParameter->Pos.z });
	EffectManager::GetManager()->SetScale(m_SwordHandle, 1.0f,1.0f,1.0f);
	EffectManager::GetManager()->SetRotation(m_SwordHandle, 
		0.0f,
		(m_pCharacter->GetLook() == Character::LOOKDIR::RIGHT ?
			3.14f : 0.0f)
		,0.0f);

	m_pModelDrawer->PlayAnime("Umatobi", true);

	m_HitAttackStopCount = 0;
}

void Character00_AttackS2::Uninit()
{
	EffectManager::GetManager()->StopEffect(m_SwordHandle);

	m_pAttackCollider->clear();
}

void Character00_AttackS2::Update()
{
	//�n�ʂɓ������Ă��Ȃ��ƕ��V��Ԃɕς���
	/*if (!m_pCharacterParameter->HitGround)
	{
		m_pCharacter->SetNextState(Character::STATE::State_AirMove);
	}*/

	//============<�U���𓖂Ă邩�̐ݒ�>====================================
	//���܂œ����������Ƃ̂���L�����N�^�[
	unsigned int OldHitCharacterBit = 0x00;
	//�O�̃t���[���ŒN���ɓ������Ă�����
	unsigned int HitTriggerCharacterBit = 0x00;

	for (Character::ATTACKPARAM& copy : (*m_pAttackCollider))
	{
		OldHitCharacterBit |= copy.m_haveHitCharacterBit;
		HitTriggerCharacterBit |= copy.m_HitTriggerCharacterBit;
	}

	//��ŋ��߂�Bit���R�s�[
	for (Character::ATTACKPARAM& copy : (*m_pAttackCollider))
	{
		//���܂œ����������Ƃ̂���L�����N�^�[��ݒ�
		copy.m_haveHitCharacterBit = OldHitCharacterBit;
		//�O�̃t���[���Ŏn�߂ē��������L�����N�^�[��ݒ�
		copy.m_HitTriggerCharacterBit = HitTriggerCharacterBit;
		//���̃t���[���œ��Ă邱�Ƃ��o����L�����N�^�[��ݒ�
		copy.m_CanAttackCharacterBit = ~copy.m_haveHitCharacterBit;
		//���Ŏg���Ă���U����ݒ肷��̂ł����Ŏg��Ȃ��悤�ɐݒ�
		copy.m_Use = false;
	}

	//============<�U���𓖂Ă���Ƀq�b�g�X�g�b�v���s����>========
	//�O�̃t���[���ŒN���ɓ��������ꍇ
	if (HitTriggerCharacterBit != 0x00)
	{
		m_HitAttackStopCount = m_HitStopFrame;
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

	//============<�A�j���[�V�����̎��Ԃ�ݒ�>==============================
	const int AnimeFrame = 24;
	const int EndFrame = 24;
	const float AnimeStartTime = 0.332f;
	const float AnimeEndTime = 0.938f;
	const float AnimeAllTime = AnimeEndTime - AnimeStartTime;

	m_FrameCount++;

	//���̃X�e�[�g���I�������
	if (m_FrameCount >= EndFrame)
	{
		m_pCharacter->SetNextState(Character::STATE::State_Idle);
	}

	m_AnimeTime = static_cast<float>(m_FrameCount) / static_cast<float>(AnimeFrame) * AnimeAllTime + AnimeStartTime;

	if (m_AnimeTime > AnimeEndTime)
	{
		m_AnimeTime = AnimeEndTime;
	}
	m_pModelDrawer->SetAnimeTime(m_AnimeTime);
	//======================================================================

	//============<���̈ʒu�ɂ���čU���̈ʒu��ݒ�>=======
	const int AttackStartFrame = 2;
	const int AttackEndFrame = 16;
	const int AttackAllFrame = AttackEndFrame - AttackStartFrame;

	int AttackFrame = m_FrameCount - AttackStartFrame;
	int AttackNum = AttackFrame / (AttackAllFrame / static_cast<float>(m_pAttackCollider->size()));

	if (AttackNum >= 0 && AttackNum < static_cast<float>(m_pAttackCollider->size()))
	{
		(*m_pAttackCollider)[AttackNum].m_Use = true;
	}
	//=====================================================
}

void Character00_AttackS2::HitCharacter(Character* pHitCharacter)
{
	//�_���[�W�̉��Z
	pHitCharacter->AddDamage(13.0f);

	//�����グ�Ēn�ʂɓ������Ă��Ȃ����Ƃɂ���
	pHitCharacter->SetPos(pHitCharacter->GetPos() + CVector3::GetUp() * 0.1f);
	
	//�_���[�W���琁����΂��x�N�g���̌v�Z
	float ForcePower = (pHitCharacter->GetDamage() / 100.0f) + 0.7f;			
	CVector3 AddVec = CVector2::GetAngleVector(
		m_pCharacter->GetLook() == Character::LOOKDIR::RIGHT ? -70.0f : 70.0f
	) * ForcePower;

	//������΂��x�N�g����ݒ�
	pHitCharacter->AddForce(AddVec);

	//�q�b�g�X�g�b�v�̐ݒ�
	CharacterBase_HitStopState* pHitStopState =
		static_cast<CharacterBase_HitStopState*>(pHitCharacter->SetNextState(Character::STATE::State_HitStop));
	pHitCharacter->ChangeNextState();
	pHitStopState->SetHitStop(m_HitStopFrame, Character::STATE::State_BlowAway, true);	//�q�b�g�X�g�b�v�̐ݒ�
	m_HitAttackStopCount = m_HitStopFrame;

	//�L�����N�^�[�̌�����ς���
	if(m_pCharacter->GetLook() == Character::LOOKDIR::RIGHT)
	{
		pHitCharacter->SetLookLeft();
	}
	else
	{
		pHitCharacter->SetLookRight();
	}
}
