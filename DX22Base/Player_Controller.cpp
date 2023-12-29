#include "Player_Controller.h"

int PlayerController::m_XPadNum = 0;
std::array<PlayerController, 5> PlayerController::m_PlayerControllers;

void PlayerController::PlayerController_Init()
{
	PlayerController::PLAYCONTROLLERTYPE ControllerType[5] =
	{
		PlayerController::PLAYCONTROLLERTYPE::KEYBOARD,
		PlayerController::PLAYCONTROLLERTYPE::GAMEPAD,
		PlayerController::PLAYCONTROLLERTYPE::GAMEPAD,
		PlayerController::PLAYCONTROLLERTYPE::GAMEPAD,
		PlayerController::PLAYCONTROLLERTYPE::GAMEPAD,
	};

	InitXPadNum();	//PADを持ってくるときに使う

	//各コントローラーの設定
	for (int i = 0; i < 5; i++)
	{
		m_PlayerControllers[i].SetController(ControllerType[i], i);
	}
}

std::array<PlayerController, 5>& PlayerController::GetPlayerControllers()
{
	return m_PlayerControllers;
}

void PlayerController::InitXPadNum()
{
	m_XPadNum = 0;
}

void PlayerController::SetController(PLAYCONTROLLERTYPE type, int PlayerNum)
{
	m_ControllerType = type;
	switch (m_ControllerType)
	{
	case PlayerController::PLAYCONTROLLERTYPE::GAMEPAD:
		m_pXPad = InputXPad::GetXPad(m_XPadNum);
		m_XPadNum++;
		break;
	case PlayerController::PLAYCONTROLLERTYPE::KEYBOARD:
		break;
	}
	m_PlayerNum = PlayerNum;
}

bool PlayerController::IsConnect()
{
	bool Connect = false;
	switch (m_ControllerType)
	{
	case PlayerController::PLAYCONTROLLERTYPE::GAMEPAD:
		Connect = m_pXPad->IsPadConnect();
		break;
	case PlayerController::PLAYCONTROLLERTYPE::KEYBOARD:
		Connect = true;
		break;
	}
	return Connect;
}

InputXPad* PlayerController::GetController()
{
	return m_pXPad;
}

PlayerController::PLAYCONTROLLERTYPE PlayerController::GetControllerType()
{
	return m_ControllerType;
}

bool PlayerController::IsPushAnyBotton()
{
	bool IsAnyButton = false;
	switch (m_ControllerType)
	{
	case PlayerController::PLAYCONTROLLERTYPE::GAMEPAD:
		m_pXPad->AllKeyPress();
		break;
	case PlayerController::PLAYCONTROLLERTYPE::KEYBOARD:
		break;
	}
	return IsAnyButton;
}

bool PlayerController::IsReturn()
{
	bool IsReturnButton = false;
	switch (m_ControllerType)
	{
	case PlayerController::PLAYCONTROLLERTYPE::GAMEPAD:
		IsReturnButton = m_pXPad->InputPressKey(PadButton::A_BUTTON);;
		break;
	case PlayerController::PLAYCONTROLLERTYPE::KEYBOARD:
		IsReturnButton = IsKeyPress(VK_RETURN);
		break;
	}
	return IsReturnButton;
}

const CVector2& PlayerController::GetMoveInput()
{
	CVector2 returnVec;
	switch (m_ControllerType)
	{
	case PlayerController::PLAYCONTROLLERTYPE::GAMEPAD:
		returnVec = m_pXPad->GetPressLeftStick();
		break;
	case PlayerController::PLAYCONTROLLERTYPE::KEYBOARD:
		returnVec.x += IsKeyPress('D') ? 1.0f : 0.0f;
		returnVec.x += IsKeyPress('A') ? -1.0f : 0.0f;
		break;
	}
	return returnVec;
}

bool PlayerController::GetLeftSmash()
{
	bool returnSmash = false;
	switch (m_ControllerType)
	{
	case PlayerController::PLAYCONTROLLERTYPE::GAMEPAD:
		returnSmash = m_pXPad->GetLeftSmash(0.35f);
		break;
	case PlayerController::PLAYCONTROLLERTYPE::KEYBOARD:
		returnSmash = IsKeyPress('L');
		break;
	}
	return returnSmash;
}

bool PlayerController::GetJumpTrigger()
{
	bool returnJump = false;
	switch (m_ControllerType)
	{
	case PlayerController::PLAYCONTROLLERTYPE::GAMEPAD:
		returnJump = m_pXPad->InputTriggerKey(PadButton::RIGHT_SHOULDER);
		break;
	case PlayerController::PLAYCONTROLLERTYPE::KEYBOARD:
		returnJump = IsKeyTrigger('W');
		break;
	}
	return returnJump;
}

bool PlayerController::GetJumpPress()
{
	bool returnJump = false;
	switch (m_ControllerType)
	{
	case PlayerController::PLAYCONTROLLERTYPE::GAMEPAD:
		returnJump = m_pXPad->InputPressKey(PadButton::RIGHT_SHOULDER);
		break;
	case PlayerController::PLAYCONTROLLERTYPE::KEYBOARD:
		returnJump = IsKeyPress('W');
		break;
	}
	return returnJump;
}

bool PlayerController::GetAttack()
{
	bool returnAttack = false;
	switch (m_ControllerType)
	{
	case PlayerController::PLAYCONTROLLERTYPE::GAMEPAD:
		returnAttack = m_pXPad->InputTriggerKey(PadButton::B_BUTTON);
		break;
	case PlayerController::PLAYCONTROLLERTYPE::KEYBOARD:
		returnAttack = IsKeyTrigger('K');
		break;
	}
	return returnAttack;
}

const CVector2& PlayerController::GetLeftInputVector()
{
	CVector2 returnVec;
	switch (m_ControllerType)
	{
	case PlayerController::PLAYCONTROLLERTYPE::GAMEPAD:
		returnVec = m_pXPad->GetPressLeftStick();
		break;
	case PlayerController::PLAYCONTROLLERTYPE::KEYBOARD:
		if (IsKeyPress('D'))
		{
			returnVec.x += 1.0f;
		}

		if (IsKeyPress('A'))
		{
			returnVec.x -= -1.0f;
		}

		if (IsKeyPress('S'))
		{
			returnVec.y -= -1.0f;
		}

		if (IsKeyPress('W'))
		{
			returnVec.y += 1.0f;
		}
		break;
	}
	return returnVec;
}

bool PlayerController::GetUp()
{
	bool Check = false;
	switch (m_ControllerType)
	{
	case PlayerController::PLAYCONTROLLERTYPE::GAMEPAD:
		Check = 0.0f < m_pXPad->GetPressLeftStick().y;
		break;
	case PlayerController::PLAYCONTROLLERTYPE::KEYBOARD:

		if (IsKeyPress('W'))
		{
			Check = true;
		}
		break;
	}
	return Check;
}
