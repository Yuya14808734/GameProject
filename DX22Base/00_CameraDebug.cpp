#include "00_CameraDebug.h"
#include "Input.h"
#include "Scene.h"
#include "00_SceneGame.h"

CameraDebug::CameraDebug()
{
	m_pos = m_AddPos = CVector3::GetZero();
}

CameraDebug::~CameraDebug()
{
}

void CameraDebug::Update()
{
	Character* copyCharacter = static_cast<SceneGame*>(CScene::GetScene())->GetCharacter()[0];
	if (copyCharacter != nullptr)
	{
		m_pos = copyCharacter->GetPos();
		m_pos.z -= 5.0f;
		m_pos.y += copyCharacter->GetCharacterCollider()->GetSize().y * 0.5f;
	}

	if(IsKeyPress('W'))
	{
		m_AddPos.z += 1.0f;
	}

	if (IsKeyPress('S'))
	{
		m_AddPos.z -= 1.0f;
	}

	if (IsKeyPress('D'))
	{
		m_AddPos.x += 1.0f;
	}

	if (IsKeyPress('A'))
	{
		m_AddPos.x -= 1.0f;
	}

	m_look = m_pos + m_AddPos;
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
