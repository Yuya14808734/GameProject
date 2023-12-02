#include "Character_00.h"

void Character_00::AttackS2_Init()
{
	m_AttackTime = 0;


	//�����蔻��̍쐬
	CVector3 ColliderPos = m_pos + CVector3::GetUp() * (m_CharacterCollider.GetSize().y * 0.5f);

	switch (m_NowLookDir)
	{
	case Character::LOOKDIR::RIGHT:
		ColliderPos = ColliderPos + CVector3::GetRight() * 1.5f;
		break;
	case Character::LOOKDIR::LEFT:
		ColliderPos = ColliderPos + CVector3::GetRight() * -1.5f;
		break;
	default:
		break;
	}

	AttackParam Attack;
	Attack.m_Use = false;
	Attack.m_BoxCollider.CreateBox(BoxCollider::BOXTYPE::CENTER, 
		ColliderPos	, CVector3(1.7f, 1.7f, 1.0f));

	m_AttackCollider.push_back(Attack);
}

void Character_00::AttackS2_Update()
{
	m_AttackTime++;

	//�t���[�����ƂɃC�x���g��ݒ肷��
	if(m_AttackTime >= 30)
	{
		ChangeState(Character::STATE::IDLE);
	}

}

void Character_00::AttackS2_Uninit()
{
	m_AttackCollider.clear();
}