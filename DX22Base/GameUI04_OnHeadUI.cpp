#include "GameUI04_OnHeadUI.h"
#include "CameraManager.h"
#include "Character_Base.h"

OnHeadUI::OnHeadUI()
{
	m_size = CVector2(400.0f, 288.0f) * 0.005f;
	m_pos = CVector3(0.0f, 100.0f, 0.0f);
}

OnHeadUI::~OnHeadUI()
{

}

void OnHeadUI::Update()
{
	//�L�����N�^�[���ݒ肳��Ă��Ȃ����
	if (m_pCharacter == nullptr)
	{
		return;
	}

	CameraBase* pNowCamera = CameraManager::GetInstance().GetSceneCamera();

	//�J�����̏�񂪂Ȃ��ꍇ
	if (pNowCamera == nullptr)
	{
		return;
	}

	//UI�̈ʒu��ۑ�
	m_pos = m_pCharacter->GetPos() + CVector3(0.0f,3.3f,0.0f);
}

void OnHeadUI::PrevDraw()
{

}

void OnHeadUI::SetCharacter(Character* pCharacter)
{
	m_pCharacter = pCharacter;
}

void OnHeadUI::SetHeadTexture(int PlayerNum)
{
	switch (PlayerNum)
	{
	case 1:
		SetTexture("Assets/UI/Player1Currsol.png");
		break;
	case 2:
		SetTexture("Assets/UI/Player2Currsol.png");
		break;
	}
}
