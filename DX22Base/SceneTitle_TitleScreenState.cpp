#include "SceneTitle_TitleScreenState.h"
#include "Main.h"

void SceneTitle_TitleScreenState::Init()
{
	m_TitleName.SetTexture("Assets/UI/TitleImage.png");
	m_TextUnderLine.SetTexture("Assets/UI/PushTextUnderLine.png");

	CVector2 WindowSize =
		CVector2(static_cast<float>(GetAppWidth()), static_cast<float>(GetAppHeight()));

	//===<タイトル名前の画像サイズの変更>===
	m_TitleName.SetPos(CVector2(WindowSize.x * 0.5f, WindowSize.y * 0.4f));
	m_TitleName.SetSize(CVector2(768.0f, 460.0f));

	//===<Enterボタンを押しての画像サイズの変更>===
	m_TextUnderLine.SetPos(CVector2(WindowSize.x * 0.5f, WindowSize.y * 0.8f));
	m_TextUnderLine.SetSize(CVector2(400.0f, 18.0f) * 2.0f);
}

void SceneTitle_TitleScreenState::Uninit()
{

}

void SceneTitle_TitleScreenState::Update()
{
	//===<押してくださいのテキストのアルファを変える>===
	m_PushButtonText.Update();
}

void SceneTitle_TitleScreenState::Draw()
{
	m_TitleName.Draw();
	m_TextUnderLine.Draw();
	m_PushButtonText.Draw();
}