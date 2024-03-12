#include "Character00_DownState.h"

void Character00_DownState::Init()
{
	CharacterBase_DownState::Init();

	m_pModelDrawer->PlayAnime("Damage01", true);
	m_AnimeTime = 0.394f;
	m_FrameCount = 0;
	m_pCharacter->SetInvincible(true);

	//=====<�|�ꂽ���̃A�j���[�V�����Ō����ڂ̈ʒu�������̂Ŋe�p�����[�^�̒���>============
	//=====<�L�����N�^�[�̓����蔻��̒���>============
	BoxCollider* pCollider = m_pCharacter->GetCharacterCollider();

	CVector3 copysize = pCollider->GetSize();

	//���ɓ|���̂�X��Y�̃T�C�Y�����ւ���
	pCollider->SetSize(CVector3(
		copysize.y,	//y��
		copysize.x,	//x�����ւ��Ă���
		copysize.z
	));

	//�L�����N�^�[�̓����蔻��̈ʒu��^�񒆂Ɉړ�����
	pCollider->SetShiftVec(CVector3::GetRight() *
		(copysize.y * 
			(m_pCharacter->GetLook() == Character::LOOKDIR::RIGHT ? -0.5f : 0.5f
		)));
	//=================================================

	//=====<���̕����ړ�����>============
	m_pCharacterParameter->Pos.x += (copysize.y * 
		(m_pCharacter->GetLook() == Character::LOOKDIR::RIGHT ? 0.5f : -0.5f));
	//=================================================

}

void Character00_DownState::Uninit()
{
	float ShiftX = m_pCharacterCollider->GetSize().x * 
		(m_pCharacter->GetLook() == Character::LOOKDIR::RIGHT ?
		-0.5f : 0.5f);

	m_pCharacterParameter->Pos.x += ShiftX;

	m_pCharacter->SetDefaultCollider();
	CharacterBase_DownState::Uninit();
}

void Character00_DownState::Update()
{
	CharacterBase_DownState::Update();

	const int AnimeEndFrame = 20;			//�A�j���[�V�������~����t���[��
	const float AnimeStartTime = 0.394f;		//�A�j���[�V�����̎n�߂鎞��
	const float AnimeEndTime = 1.461f;		//�A�j���[�V�������I��鎞��
	const float AnimeAllTime = AnimeEndTime - AnimeStartTime;	//�A�j���[�V�����̎���

	m_FrameCount++;

	m_AnimeTime = static_cast<float>(m_FrameCount) / static_cast<float>(AnimeEndFrame) * AnimeAllTime + AnimeStartTime;

	//�A�j���[�V�������I��������ҋ@��Ԃɂ���
	if (m_AnimeTime > AnimeEndTime)
	{
		m_AnimeTime = AnimeEndTime;

		//�]��ł���Ƃ��ɏ�{�^���������ƋN���オ��
		if (m_pController->GetMoveInput().length() > 0.5f)
		{
			m_pCharacter->SetNextState(Character::STATE::State_WakeUp);
		}
	}

	//�A�j���[�V�������I�����Ă�����x���Ԃ��������疳�G���O��
	if (m_FrameCount > AnimeEndFrame + 15)
	{
		m_pCharacter->SetInvincible(false);
	}

	m_pModelDrawer->SetAnimeTime(m_AnimeTime);
}