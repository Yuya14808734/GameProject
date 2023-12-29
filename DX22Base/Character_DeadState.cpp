#include "Character_Base.h"

void Character::DeadInit()
{
	m_ChangeStateCount = 0;	//�X�e�[�^�X��ς���܂ł̎��Ԃ��J�E���g����
	m_CharacterStock--;		//�X�g�b�N�����炷
}

void Character::DeadUninit()
{
	m_ChangeStateCount = 0;
}

void Character::DeadUpdate()
{
	m_ChangeStateCount++;

	if (m_ChangeStateCount > 30)
	{
		if (m_CharacterStock > 0)
		{
			//�܂��X�g�b�N������ꍇ
			ChangeState(Character::STATE::RESPAWN);
		}
		else
		{
			//�X�g�b�N���Ȃ��ꍇ
			ChangeState(Character::STATE::GAMEOVER);
		}
	}
}