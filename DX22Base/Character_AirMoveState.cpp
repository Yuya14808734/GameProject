#include "Character_Base.h"
#include "Input.h"
#include "Attack_Base.h"
#include "XboxKeyboard.h"

void Character::AirMoveInit()
{
	m_MoveVector = CVector3::GetZero();
}

void Character::AirMoveUninit()
{

}

void Character::AirMoveUpdate()
{
	if (m_HitGround)
	{
		ChangeState(Character::STATE::IDLE);
	}

	bool OnButton = false;

	float LeftStickX = GetPressLeftStick().x * m_WalkSpeed;
	m_Velocity.x = fabsf(LeftStickX) > fabsf(m_Velocity.x) ? LeftStickX : m_Velocity.x;

	if (IsKeyPress(VK_RIGHT))
	{
		m_Velocity.x = m_AirSideMoveSpeed;
	}

	if (IsKeyPress(VK_LEFT))
	{
		m_Velocity.x = -m_AirSideMoveSpeed;
	}

	//‚à‚¤ˆê“xƒWƒƒƒ“ƒv‚ª‚Å‚«‚é
	if (m_JumpCount < m_MaxJumpCount)
	{
		if (InputTriggerKey(PadButton::RIGHT_SHOULDER) || IsKeyTrigger(VK_UP))
		{
			m_JumpCount++;
			m_Velocity.y = m_FirstJumpPower;
			ChangeState(Character::STATE::JUMP);
		}
	}

	//UŒ‚
	if (IsKeyPress('K') || InputPressKey(PadButton::A_BUTTON))
	{
		ChangeAttack(Character::ATTACK::ATTACK_AIRN);	//Žã‚ÌÝ’è
	}

	if (!OnButton)
	{
		m_Velocity.x *= m_AirDrag;	//‹ó‹C’ïR‚ðŠ|‚¯‚é
	}

	m_Velocity.y += m_FallDownGravity;			//d—Í‚ðŠ|‚¯‚é

	//d—Í§Œä(Å‘å‚Ì—Ž‰º‘¬“x‚É‚È‚Á‚½‚ç)
	if (m_Velocity.y < m_DefaultFallSpeed)
	{
		m_Velocity.y = m_DefaultFallSpeed;
	}

	m_pos += m_MoveVector;
	m_pos += m_Velocity;
}