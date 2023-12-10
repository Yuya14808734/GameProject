#include "Character_Base.h"
#include "Input.h"
#include "Attack_Base.h"
#include "XboxKeyboard.h"

void Character::JumpInInit()
{
	m_JumpCharageCount = 0;
	m_MoveVector = CVector3::GetZero();
	m_Velocity.x = m_MoveVector.x;
	m_Velocity.y = 0.0f;
}

void Character::JumpInUninit()
{

}

void Character::JumpInUpdate()
{
	m_JumpCharageCount++;

	//�W�����v�{�^���̉����Ă��钷���ɂ���ăW�����v���Ă���͂�ς��Ă��
	if (InputPressKey(PadButton::RIGHT_SHOULDER) || IsKeyPress(VK_UP))
	{
		if (m_JumpCharageCount >= m_MiniJumpPushButtonCount)
		{
			//��W�����v
			m_Velocity.y = m_FirstJumpPower;
		}
		else
		{
			//���W�����v
			m_Velocity.y = m_FirstMiniJumpPower;
		}
	}

	if(m_JumpCharageCount > m_JumpChargeCount)
	{
		ChangeState(Character::STATE::JUMP);
		m_Velocity.x = m_MoveVector.x;	
	}
}