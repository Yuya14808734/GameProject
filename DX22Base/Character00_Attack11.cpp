#include "Character_00.h"
#include "Input.h"
#include "XboxKeyboard.h"

void Character_00::Attack11_Init()
{
	m_AttackTime = 0;
	m_AnimeTime = 1.145f;
	
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

	m_CharacterModel.PlayAnime("Pose2", true);
}

void Character_00::Attack11_Update()
{
	//============<�U���𓖂Ă邩�̐ݒ�>===================
	//���܂œ����������Ƃ̂���L�����N�^�[�ɂ͓��ĂȂ�
	m_AttackCollider[0].m_CanAttackCharacterBit = ~m_AttackCollider[0].m_haveHitCharacterBit;
	//=====================================================

	const int AnimeAllFrame = 16;								//�A�j���[�V�����S�̂̃t���[��
	const int EndFrame = 30;									//�U���I������
	const float AnimeStartTime = 1.145f;						//�A�j���[�V�����J�n����
	const float AnimeEndTime = 1.193f;							//�A�j���[�V�����I������
	const float AnimeAllTime = AnimeEndTime - AnimeStartTime;	//�A�j���[�V�����̎���
	
	m_AttackTime++;

	//�A�j���[�V�����̍Đ����Ԃ̍X�V
	m_AnimeTime = static_cast<float>(m_AttackTime) / static_cast<float>(AnimeAllFrame) * AnimeAllTime + AnimeStartTime;

	//�A�j���[�V�������I������ׂ����Ԃ𒴂��Ă����ꍇ
	if (m_AnimeTime > AnimeEndTime)
	{
		m_AnimeTime = AnimeEndTime;
	}

	//�����蔻��J�n
	if (m_AttackTime == 6)					
	{
		m_AttackCollider[0].m_Use = true;
	}

	//�����蔻��I��
	if (m_AttackTime == 20)					
	{
		m_AttackCollider[0].m_Use = false;
	}

	//���̃t���[���̊Ԃł���Ύ�2�֍s�����Ƃ��o����
	if (m_AttackTime > 10 && m_AttackTime < EndFrame)	
	{
		//�U��
		if (m_Controller.GetAttack())	
		{
			ChangeAttack(Character::ATTACK::ATTACK_12);	//��̐ݒ�
		}
	}

	//�t���[�����ƂɃC�x���g��ݒ肷��
	if (m_AttackTime >= EndFrame)		
	{
		ChangeState(Character::STATE::IDLE);
	}

	//�A�j���[�V�����̍Đ����Ԃ̐ݒ�
	m_CharacterModel.SetAnimeTime(m_AnimeTime);
}

void Character_00::Attack11_Uninit()
{
	m_AttackCollider.clear();
}

void Character_00::Attack11_Hit(Character* HitCharacter)
{
	HitCharacter->AddDamage(2.0f);								//�_���[�W�̉��Z
	HitCharacter->SetHitStop(5, Character::STATE::BLOWAWAY);	//�q�b�g�X�g�b�v��
	HitCharacter->SetShake(true);
}
