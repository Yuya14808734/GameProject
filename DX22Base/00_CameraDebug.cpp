#include "00_CameraDebug.h"
#include "Input.h"

CameraDebug::CameraDebug()
{
	m_pos.z = -10.0f;
}

CameraDebug::~CameraDebug()
{
}

void CameraDebug::Update()
{
	if(IsKeyPress('W'))
	{
		m_pos.z += 1.0f;
	}

	if (IsKeyPress('S'))
	{
		m_pos.z -= 1.0f;
	}

	if (IsKeyPress('D'))
	{
		m_pos.x += 1.0f;
	}

	if (IsKeyPress('A'))
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
