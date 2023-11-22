#include "Character_Base.h"
#include "Input.h"
#include "Attack_Base.h"

void Character::IdleUpdate()
{
	//---�s������---
	//�W�����v
	//�U��(��t���[���̂�,�����Ȃǂ�Walk�ɔC����)
	//����
	//����
	

	if (IsKeyPress(VK_RIGHT) || IsKeyPress(VK_LEFT))
	{
		m_State = Character::STATE::WALK;
	}

	if (IsKeyPress(VK_UP))
	{
		m_State = Character::STATE::JUMP;
	}

	//�U��
	if (false)
	{
		m_State = Character::STATE::ATTACK;
	}

	m_Velocity.y += m_Gravity;

	//�ꉞ�d�͐���������Ă���
	if (m_Velocity.y < m_MaxFallSpeed)
	{
		m_Velocity.y = m_MaxFallSpeed;
	}

	m_pos += m_MoveVector;
	m_pos += m_Velocity;
}

void Character::WalkUpdate()
{
	//---�s������---
	//�W�����v
	//�U��
	//����
	//����

	bool NoButton = true;

	m_MoveVector.x = 0.0f;

	if (IsKeyPress(VK_RIGHT))
	{		
		m_MoveVector.x = m_WalkSpeed;

		NoButton = false;
	}

	if (IsKeyPress(VK_LEFT))
	{
		m_MoveVector.x = -m_WalkSpeed;

		NoButton = false;
	}

	//�{�^��������������Ă��Ȃ����
	if (NoButton)
	{
		m_State = Character::STATE::IDLE;
	}

	//�W�����v
	if (IsKeyPress(VK_UP))
	{
		m_Velocity.y = m_JumpPower;
		m_State = Character::STATE::JUMP;
	}

	//���Ⴊ�݂������


	m_Velocity.y += m_Gravity;

	//�ꉞ�d�͐���������Ă���
	if (m_Velocity.y < m_MaxFallSpeed)
	{
		m_Velocity.y = m_MaxFallSpeed;
	}

	m_pos += m_MoveVector;
	m_pos += m_Velocity;
}

void Character::DashUpdate()
{
	//---�s������---
	//
	//�U��
	//����
	//����

	bool NoButton = true;

	if (IsKeyPress(VK_RIGHT))
	{
		if (m_MoveVector.x < -0.01f)
		{
			//���ɍs���Ă����ꍇ�A���C���|����
			m_MoveVector.x *= m_Friction;
		}
		else
		{
			m_MoveVector.x = m_DashSpeed;
		}

		NoButton = false;
	}

	if (IsKeyPress(VK_LEFT))
	{
		if (m_MoveVector.x > 0.01f)
		{
			//�E�ɍs���Ă����ꍇ�A���C���|����
			m_MoveVector.x *= m_Friction;
		}
		else
		{
			m_MoveVector.x = m_DashSpeed;
		}

		NoButton = false;
	}

	//�{�^��������������Ă��Ȃ����
	if (NoButton)
	{
		//�~�܂�
		m_MoveVector.x *= m_Friction;

		//������x�x���Ȃ�����
		if (m_MoveVector.x < 0.01f || m_MoveVector.x > -0.01f)
		{
			m_MoveVector.x = 0.0f;
			m_State = Character::STATE::IDLE;
		}
	}

	//�W�����v
	if (IsKeyPress(VK_UP))
	{
		m_Velocity.x = m_MoveVector.x;
		m_Velocity.y = m_JumpPower;
		m_State = Character::STATE::JUMP;
	}

	m_Velocity.y += m_Gravity;

	//�ꉞ�d�͐���������Ă���
	if (m_Velocity.y < m_MaxFallSpeed)
	{
		m_Velocity.y = m_MaxFallSpeed;
	}

	m_pos += m_MoveVector;
	m_pos += m_Velocity;
}

void Character::AttackUpdate()
{
	//---�s������---
	//�A�^�b�N�ɂ���ĕς��
	//�n�ʂł̍U���Ȃ�Idle
	//�󒆂Ȃ�Full

	//�A�^�b�N�̍X�V�͔C����
	if(m_pNowAttack != nullptr)
	m_pNowAttack->Attack_Update();
}

//==============================================
//�������ł���Ƃ��̃A�b�v�f�[�g
void Character::BlowOffUpdate()
{
	if (IsKeyPress(VK_RIGHT))
	{
		m_MoveVector.x = m_FallSideMoveSpeed;
	}

	if (IsKeyPress(VK_LEFT))
	{
		m_MoveVector.x = -m_FallSideMoveSpeed;
	}

	//�c�ɔ�΂��x�N�g��������������
	if (m_Velocity.y < m_MaxFallSpeed || m_Velocity.y > 0.01f)
	{
		m_Velocity.y *= m_AirResistance;
	}

	//���ɔ�΂��x�N�g��������������
	m_Velocity.x *= m_AirResistance;

	//������x�����Ȃ��Ȃ����痎����Ԃɕς���
	if (fabsf(m_Velocity.x) < 0.3f && fabsf(m_Velocity.y) < 0.3f)
	{
		m_State = Character::STATE::FALL;
	}

	//�ꉞ�d�͐���������Ă���
	if (m_Velocity.y < m_MaxFallSpeed)
	{
		m_Velocity.y = m_MaxFallSpeed;
	}

	m_pos += m_MoveVector;
	m_pos += m_Velocity;
}

void Character::JumpUpdate()
{
	bool OnButton = false;

	if (IsKeyPress(VK_RIGHT))
	{
		m_Velocity.x = m_FallSideMoveSpeed;
		OnButton = true;
	}

	if (IsKeyPress(VK_LEFT))
	{
		m_Velocity.x = -m_FallSideMoveSpeed;
		OnButton = true;
	}

	//������x�W�����v���ł���
	if (m_JumpCount < m_MaxJumpCount)
	{
		if (IsKeyTrigger(VK_UP))
		{
			m_JumpCount++;
			m_Velocity.y = m_JumpPower;
			m_State = Character::STATE::JUMP;
		}
	}

	if (OnButton)
	{
		m_Velocity.x *= m_AirResistance;	//��C��R���|����
	}
	
	m_Velocity.y += m_Gravity;			//�d�͂��|����

	//�d�͐���(�ő�̗������x�ɂȂ�����)
	if (m_Velocity.y < m_MaxFallSpeed)
	{
		m_Velocity.y = m_MaxFallSpeed;
	}

	//�������n�߂���
	if (m_Velocity.y < 0.1f)
	{
		m_State = Character::STATE::FALL;
	}

	m_pos += m_MoveVector;
	m_pos += m_Velocity;
}

//==============================================
//�����Ă���Ƃ��̃A�b�v�f�[�g
void Character::FallUpdate()
{
	bool OnButton = false;

	if (IsKeyPress(VK_RIGHT))
	{
		m_Velocity.x = m_FallSideMoveSpeed;
		OnButton = true;
	}

	if (IsKeyPress(VK_LEFT))
	{
		m_Velocity.x = -m_FallSideMoveSpeed;
		OnButton = true;
	}

	//������x�W�����v���ł���
	if (m_JumpCount < m_MaxJumpCount)
	{
		if (IsKeyTrigger(VK_UP))
		{
			m_JumpCount++;
			m_Velocity.y = m_JumpPower;
			m_State = Character::STATE::JUMP;
		}
	}

	if (OnButton)
	{
		m_Velocity.x *= m_AirResistance;	//��C��R���|����
	}

	m_Velocity.y += m_Gravity;			//�d�͂��|����

	//�d�͐���(�ő�̗������x�ɂȂ�����)
	if (m_Velocity.y < m_MaxFallSpeed)
	{
		m_Velocity.y = m_MaxFallSpeed;
	}

	m_pos += m_MoveVector;
	m_pos += m_Velocity;
}

//==============================================
//�|��Ă���Ƃ��̃A�b�v�f�[�g
void Character::DownUpdate()
{
	if (IsKeyPress(VK_UP))
	{
		m_State = Character::STATE::IDLE;
	}

	if (IsKeyPress(VK_RIGHT))
	{

	}

	if (IsKeyPress(VK_LEFT))
	{
		
	}
}

//==============================================
//�n�ʂɓ����������ɌĂ΂��
void Character::HitGround()
{
	m_Velocity.y = 0.0f;
}
