#include "00_CameraDebug.h"
#include "Input.h"

CameraDebug::CameraDebug()
{
}

CameraDebug::~CameraDebug()
{
}

void CameraDebug::Update()
{
	if(IsKeyPress(VK_UP))
	{
		m_pos.z += 1.0f;
	}

	if (IsKeyPress(VK_DOWN))
	{
		m_pos.z -= 1.0f;
	}

	if (IsKeyPress(VK_RIGHT))
	{
		m_pos.x += 1.0f;
	}

	if (IsKeyPress(VK_LEFT))
	{
		m_pos.x -= 1.0f;
	}

	m_look = m_pos;
	m_look.z += 1.0f;

	if (m_pCharacter == nullptr)
	{
		return;
	}
	m_look = m_pos = m_pCharacter->GetPos().f;
	m_pos.z -= 10.0f;
	m_pos.y -= 10.0f;
	m_look.y -= -10.0f;
}

void CameraDebug::ChangeInit()
{
}

void CameraDebug::ChangeUninit()
{
}

void CameraDebug::SetCharacter(Character * pCharacter)
{
}
