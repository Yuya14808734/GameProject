#include "Camera00_Debug.h"
#include "Input.h"
#include "Scene.h"
#include "Scene00_Game.h"

CameraDebug::CameraDebug()
{
	m_pos = m_look = CVector3::GetZero();

	m_pos.y = m_look.y = 3.0f;
	m_pos.z = -30.0f;
}

CameraDebug::~CameraDebug()
{
}

void CameraDebug::Update()
{
	
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
