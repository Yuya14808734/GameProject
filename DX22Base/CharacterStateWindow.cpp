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

	Character::JUMPPARAMETER JumpParameter = m_pCharacter->GetJumpParameter();

	ImGui::InputFloat(u8"�W�����v��", &JumpParameter.m_FirstJumpPower);
	ImGui::InputFloat(u8"�W�����v�d��", &JumpParameter.m_JumpUpReduction);
	ImGui::InputFloat(u8"���ɉ�����Ƃ��̏d��", &JumpParameter.m_FallDownGravity);
	ImGui::InputFloat(u8"�ő嗎�����x", &JumpParameter.m_DefaultFallSpeed);
	ImGui::InputFloat(u8"�����ɕς��X�s�[�h", &JumpParameter.m_ChangeFallSpeed);

	m_pCharacter->SetjumpParameter(JumpParameter);
}

void CharacterStateWindow::SetCharacter(Character* pCharacter)
{
	m_pCharacter = pCharacter;
}
