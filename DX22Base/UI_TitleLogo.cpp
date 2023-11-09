#include "UI_TitleLogo.h"

UI_TitleLogo::UI_TitleLogo()
{
	LoadTextureFromFile("Assets/2D/Jewelist.png",
		&m_pTexture);
	//m_pos = { 1100.0f,680.0f,0.0f };
	//m_size = { 300.0f,-20.0f };
	m_pos = { 640.0f,350.0f,0.0f };
	m_size = { 700.0f,-700.0f };
}

UI_TitleLogo::~UI_TitleLogo()
{
	m_pTexture->Release();
}

void UI_TitleLogo::Update()
{

}