#include "ClearUI.h"

ClearUI::ClearUI()
{
	LoadTextureFromFile("Assets/2D/GameClear.png",
		&m_pTexture);
	//m_pos = { 1100.0f,680.0f,0.0f };
	//m_size = { 300.0f,-20.0f };
	m_pos = { 640.0f,300.0f,0.0f };
	m_size = { 700.0f,-700.0f };
}

ClearUI::~ClearUI()
{
	m_pTexture->Release();
}

void ClearUI::Update()
{

}