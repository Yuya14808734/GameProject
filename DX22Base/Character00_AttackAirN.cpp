#include "Character00_AttackAirN.h"
#include "Input.h"
#include "XboxKeyboard.h"
#include "CharacterBase_HitStopState.h"
#include "SoundManager.h"
#include "Scene00_Game.h"

void Character00_AttackAirN::Init()
{
	m_FrameCount = 0;
	m_AnimeTime = 0.935f;
	m_HitAttackStopCount = 0;

	//�����蔻��̍쐬
	CVector3 ColliderBasePos = m_pCharacterParameter->Pos;
	CVector3 ColliderSplitSize = CVector3(3.5f * 0.5f, 4.0f * 0.5f, 1.0f);
	CVector3 ColliderSplitPos[4] =
	{
		CVector3(ColliderSplitSize.x * -0.5f,ColliderSplitSize.y *  0.5f, 0.0f),	//����
		CVector3(ColliderSplitSize.x * -0.5f,ColliderSplitSize.y * -0.5f, 0.0f),	//����
		CVector3(ColliderSplitSize.x *  0.5f,ColliderSplitSize.y * -0.5f, 0.0f),	//�E��
		CVector3(ColliderSplitSize.x *  0.5f,ColliderSplitSize.y *  0.5f, 0.0f),	//�E��
	};

	//�U���̓����蔻��𐶐�
	Character::ATTACKPARAM Attack;

	for (int i = 0; i < 4; i++)
	{
		Attack.m_Use = false;
		Attack.m_BoxCollider.CreateBox(BoxCollider::BOXTYPE::CENTER,
			ColliderBasePos, ColliderSplitSize, ColliderSplitPos[i] + CVector3(0.0f,1.0f,0.0f));
		Attack.m_CanAttackCharacterBit = 0xffffffff;					//������L�����N�^�[�̐ݒ�
		m_pAttackCollider->push_back(Attack);
	}

	m_efkHnd_Sword = EffectManager::GetManager()->Play(EffectManager::GetEffect("C00_AirN"), 0, 0, 0);
	EffectManager::GetManager()->SetLocation(m_efkHnd_Sword,
		{ ColliderBasePos.x, ColliderBasePos.y + 1.0f, ColliderBasePos.z + 0.3f });
	EffectManager::GetManager()->SetScale(m_efkHnd_Sword, 1.0f, 1.0f, 1.0f);

	m_pModelDrawer->PlayAnime("WAIT04", true);

	//m_pCharacterParameter->MoveVector = CVector3::GetZero();
}

void Character00_AttackAirN::Uninit()
{
	EffectManager::GetManager()->StopEffect(m_efkHnd_Sword);
	(*m_pAttackCollider).clear();
	m_pCharacter->SetDefaultCollider();
}

void Character00_AttackAirN::Update()
{
	//�n�ʂɓ�����ƃA�C�h����Ԃɕς���
	if (m_pCharacterParameter->HitGround)
	{
		m_pCharacter->SetNextState(Character::STATE::State_Idle);
	}

	//============<�U���𓖂Ă邩�̐ݒ�>===================
	//���܂œ����������Ƃ̂���L�����N�^�[
	unsigned int OldHitCharacterBit =
		(*m_pAttackCollider)[0].m_haveHitCharacterBit |
		(*m_pAttackCollider)[1].m_haveHitCharacterBit |
		(*m_pAttackCollider)[2].m_haveHitCharacterBit |
		(*m_pAttackCollider)[3].m_haveHitCharacterBit;

	//�O�̃t���[���ŒN���ɓ������Ă�����
	unsigned int HitTriggerCharacterBit =
		(*m_pAttackCollider)[0].m_HitTriggerCharacterBit |
		(*m_pAttackCollider)[1].m_HitTriggerCharacterBit |
		(*m_pAttackCollider)[2].m_HitTriggerCharacterBit |
		(*m_pAttackCollider)[3].m_HitTriggerCharacterBit;

	for (int i = 0; i < 4; i++)
	{
		//���܂œ����������Ƃ̂���L�����N�^�[��ݒ�
		(*m_pAttackCollider)[i].m_haveHitCharacterBit = OldHitCharacterBit;
		//�O�̃t���[���Ŏn�߂ē��������L�����N�^�[��ݒ�
		(*m_pAttackCollider)[i].m_HitTriggerCharacterBit = HitTriggerCharacterBit;
		//���̃t���[���œ��Ă邱�Ƃ��o����L�����N�^�[��ݒ�
		(*m_pAttackCollider)[i].m_CanAttackCharacterBit = ~(*m_pAttackCollider)[i].m_haveHitCharacterBit;
		//���Ŏg���Ă���U����ݒ肷��̂ł����Ŏg��Ȃ��悤�ɐݒ�
		(*m_pAttackCollider)[i].m_Use = false;
	}
	//=====================================================

	//============<�U���𓖂Ă���Ƀq�b�g�X�g�b�v���s����>========
	//�O�̃t���[���ŒN���ɓ������Ă�����
	if (HitTriggerCharacterBit != 0x00)
	{
		m_HitAttackStopCount = m_HitStopFrame;
		EffectManager::GetManager()->SetPaused(m_efkHnd_Sword, true);
	}

	//�U���𓖂Ă��q�b�g�X�g�b�v���I���܂œ����Ȃ�
	if (m_HitAttackStopCount > 0)
	{
		m_HitAttackStopCount--;

		//�U���������������̃X�g�b�v��������
		if (m_HitAttackStopCount == 0)
		{
			EffectManager::GetManager()->SetPaused(m_efkHnd_Sword, false);
			m_pEfk_HitBig->PausedEffect(false);
		}

		return;
	}
	//=====================================================

	//============<�A�j���[�V�����̎��Ԃ�ݒ�>=============
	const int AnimeFrame = 40;
	const int EndFrame = 40;
	const float AnimeStartTime = 0.677f;
	const float AnimeEndTime = 1.164f;
	const float AnimeAllTime = AnimeEndTime - AnimeStartTime;

	m_FrameCount++;

	if (m_FrameCount == 13)
	{
		SoundManager::PlaySE("MissSword02");
	}


	//�Ō�܂ŃA�j���[�V�����������ꍇ
	if (m_FrameCount >= EndFrame)
	{
		m_pCharacter->SetNextState(Character::STATE::State_AirMove);
		return;
	}

	m_AnimeTime = static_cast<float>(m_FrameCount) / static_cast<float>(AnimeFrame) * AnimeAllTime + AnimeStartTime;

	if (m_AnimeTime > AnimeEndTime)
	{
		m_AnimeTime = AnimeEndTime;
	}
	m_pModelDrawer->SetAnimeTime(m_AnimeTime);
	//=====================================================

	//============<���̈ʒu�ɂ���čU���̈ʒu��ݒ�>=======
	const int AttackStartFrame = 18;
	const int AttackEndFrame = 28;
	const int AttackAllFrame = AttackEndFrame - AttackStartFrame;

	int AttackFrame = m_FrameCount - AttackStartFrame;
	int AttackNum = AttackFrame / (AttackAllFrame / 4);

	if (AttackNum >= 0 && AttackNum < 4)
	{
		(*m_pAttackCollider)[AttackNum].m_Use = true;
	}
	//=====================================================

	//============<�ړ�����>===============================
	float LeftStickX = m_pController->GetMoveInput().x * m_pMoveParameter->WalkSpeed;
	m_pCharacterParameter->Velocity.x = 
		fabsf(LeftStickX) > fabsf(m_pCharacterParameter->Velocity.x) ? 
		LeftStickX : m_pCharacterParameter->Velocity.x;

	m_pCharacterParameter->Velocity.x *= m_pMoveParameter->AirDrag;	//��C��R���|����
	m_pCharacterParameter->Velocity.y += m_pJumpParameter->FallDownGravity;	//�d�͂��|����

	//�d�͐���(�ő�̗������x�ɂȂ�����)
	if (m_pCharacterParameter->Velocity.y < m_pJumpParameter->DefaultFallSpeed)
	{
		m_pCharacterParameter->Velocity.y = m_pJumpParameter->DefaultFallSpeed;
	}

	//�ŏI�I�Ȉʒu��ݒ�
	m_pCharacterParameter->Pos += m_pCharacterParameter->Velocity;
	//=====================================================

	EffectManager::GetManager()->SetLocation(
		m_efkHnd_Sword, { 
			m_pCharacterParameter->Pos.x,
			m_pCharacterParameter->Pos.y + 1.0f,
			m_pCharacterParameter->Pos.z + 0.3f });
	for (int i = 0; i < 4; i++)
	{
		(*m_pAttackCollider)[i].m_BoxCollider.SetBasePos(m_pCharacterParameter->Pos);
	}
}

void Character00_AttackAirN::Draw()
{
	EffectManager::EffectDraw(m_efkHnd_Sword);
}

void Character00_AttackAirN::HitCharacter(Character* pHitCharacter, Character::ATTACKPARAM* pHitAttack)
{
	SoundManager::PlaySE("HitSword02");

	pHitCharacter->AddDamage(10.0f);								//�_���[�W�̉��Z
	float ForcePower = (pHitCharacter->GetDamage() / 100.0f) * 1.2f + 0.3f;			//�_���[�W���琁����΂��x�N�g���̌v�Z

	pHitCharacter->SetPos(pHitCharacter->GetPos() + CVector3::GetUp() * 0.1f);		//�����グ�Ēn�ʂɓ������Ă��Ȃ����Ƃɂ���

	//������΂��x�N�g����ݒ�
	float DistanceX = pHitCharacter->GetPos().x - m_pCharacterParameter->Pos.x;
	CVector3 AddVec = CVector2::GetAngleVector(
		//���������L�����N�^�[���E�ɂ���ꍇ
		DistanceX > 0.0f
		? -15.0f : 15.0f
	) * ForcePower;
	pHitCharacter->AddForce(AddVec);

	//�L�����N�^�[���_�b�V�������Ƃ��̃G�t�F�N�g
	SceneGame* pGameScene = static_cast<SceneGame*>(CScene::GetScene());

	m_pEfk_HitBig = new EffectHitBig();
	m_pEfk_HitBig->PlayHitEffect(
		pHitCharacter->GetPos() + (CVector3::GetUp() * pHitCharacter->GetCharacterCollider()->GetSize().y * 0.5f)
	);

	m_pEfk_HitBig->PausedEffect();
	pGameScene->GetEffectVector()->push_back(m_pEfk_HitBig);

	//�q�b�g�X�g�b�v�̐ݒ�
	CharacterBase_HitStopState* pHitStopState =
		static_cast<CharacterBase_HitStopState*>(pHitCharacter->SetNextState(Character::STATE::State_HitStop));
	pHitCharacter->ChangeNextState();
	pHitStopState->SetHitStop(m_HitStopFrame, Character::STATE::State_BlowAway, true);	//�q�b�g�X�g�b�v�̐ݒ�

	m_HitAttackStopCount = m_HitStopFrame;

	//����̃L�����N�^�[�̌�����ݒ�
	if (DistanceX > 0.0f)	//�E�ɐ�����΂��ꍇ
	{
		pHitCharacter->SetLookLeft();
	}
	else
	{
		pHitCharacter->SetLookRight();
	}
}