#include "CharacterStateWindow.h"

void CharacterStateWindow::Init()
{
	m_WindowName = "AnimetionInspector";

	m_Pos = { 950.0f,50.0f };
	m_Size = { 300.0f,200.0f };
}

void CharacterStateWindow::Uninit()
{

}

void CharacterStateWindow::DrawUpdate()
{
	ImGui::Text("Models");
}

void CharacterStateWindow::SetCharacter(Character* pCharacter)
{
	m_pCharacter = pCharacter;
}
