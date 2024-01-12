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

	ImGui::InputFloat(u8"�W�����v��", &JumpParameter.FirstJumpPower);
	ImGui::InputFloat(u8"�W�����v�d��", &JumpParameter.JumpUpReduction);
	ImGui::InputFloat(u8"���ɉ�����Ƃ��̏d��", &JumpParameter.FallDownGravity);
	ImGui::InputFloat(u8"�ő嗎�����x", &JumpParameter.DefaultFallSpeed);
	ImGui::InputFloat(u8"�����ɕς��X�s�[�h", &JumpParameter.ChangeFallSpeed);

	m_pCharacter->SetjumpParameter(JumpParameter);
}

void CharacterStateWindow::SetCharacter(Character* pCharacter)
{
	m_pCharacter = pCharacter;
}
