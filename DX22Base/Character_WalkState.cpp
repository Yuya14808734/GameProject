#include "Character_Base.h"
#include "Input.h"
#include "Attack_Base.h"
#include "XboxKeyboard.h"

void Character::WalkInit()
{
	m_MoveVector.x = 0.0f;
	m_Velocity.x = 0.0f;
}

void Character::WalkUninit()
{

}

void Character::WalkUpdate()
{
	//�n�ʂɓ������Ă��Ȃ����
	if (!m_HitGround)
	{
		ChangeState(Character::STATE::AIRMOVE);
	}

	bool NoButton = true;

	m_MoveVector.x = GetPressLeftStick().x * m_WalkSpeed;

	if(IsKeyPress(VK_RIGHT))
	{
		m_MoveVector.x = m_WalkSpeed;
	}

	if(IsKeyPress(VK_LEFT))
	{
		m_MoveVector.x = -m_WalkSpeed;
	}

	if (m_MoveVector.x != 0.0f)
	{
		NoButton = false;

		if (m_MoveVector.x > 0.0f)
		{
			//�E�ɍs���Ă���
			m_rotate = CQuaternion::AngleAxis(CVector3::GetUp(), 90.0f);
			m_NowLookDir = Character::LOOKDIR::RIGHT;
		}
		else
		{
			//���ɍs���Ă���
			m_rotate = CQuaternion::AngleAxis(CVector3::GetUp(), -90.0f);
			m_NowLookDir = Character::LOOKDIR::LEFT;
		}

	}

	//�{�^��������������Ă��Ȃ����
	if (NoButton)
	{
		ChangeState(Character::STATE::IDLE);
	}

	//�U��
	if (IsKeyTrigger('K') || InputTriggerKey(PadButton::A_BUTTON))
	{
		ChangeAttack(Character::ATTACK::ATTACK_S2);	//�����̐ݒ�
	}

	//�W�����v
	if (InputTriggerKey(PadButton::RIGHT_SHOULDER) || IsKeyTrigger(VK_UP))
	{
		ChangeState(Character::STATE::JUMPIN);
	}

	//���Ⴊ�݂������
	if (IsKeyPress(VK_DOWN))
	{

	}

	m_Velocity.y += m_Gravity;

	//�ꉞ�d�͐���������Ă���
	if (m_Velocity.y < m_DefaultFallSpeed)
	{
		m_Velocity.y = m_DefaultFallSpeed;
	}

	m_pos += m_MoveVector;
	m_pos += m_Velocity;
}