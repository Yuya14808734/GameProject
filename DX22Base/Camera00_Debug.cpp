#include "Camera00_Debug.h"
#include "Input.h"
#include "Scene.h"
#include "Scene00_Game.h"
#include "Input.h"

CameraDebug::CameraDebug()
{
	m_pos = m_look = CVector3::GetZero();

	m_LookVec = CVector3::GetForward();

	m_pos.y = m_look.y = 3.0f;
	m_pos.z = -30.0f;
}

CameraDebug::~CameraDebug()
{
}

void CameraDebug::Update()
{
	if (IsKeyPress(VK_RIGHT))
	{
		m_pos.x += 0.1f;
	}

	if (IsKeyPress(VK_LEFT))
	{
		m_pos.x -= 0.1f;
	}

	if (IsKeyPress(VK_UP))
	{
		m_pos.y += 0.1f;
	}

	if (IsKeyPress(VK_DOWN))
	{
		m_pos.y -= 0.1f;
	}

	if (IsKeyPress(VK_CONTROL))
	{
		m_pos.z += 0.1f;
	}

	if (IsKeyPress(VK_SHIFT))
	{
		m_pos.z -= 0.1f;
	}

	m_look = CVector3::GetZero();
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
