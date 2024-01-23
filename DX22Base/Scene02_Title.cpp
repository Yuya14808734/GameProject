#include "Scene02_Title.h"
#include "Main.h"
#include "Player_Controller.h"
#include "Scene01_Select.h"
#include "SceneTitle_TitleScreenState.h"
#include "TextureClass.h"

void SceneTitle::Init()
{
	//===<画像の読み込み処理>===
	m_BackGround.SetTexture("Assets/UI/TitleBackGround.png");
	
	CVector2 WindowSize = 
		CVector2(static_cast<float>(GetAppWidth()), static_cast<float>(GetAppHeight()));

	//===<背景のサイズの変更>===
	m_BackGround.SetPos(WindowSize * 0.5f);
	m_BackGround.SetSize(WindowSize);

	SetNextState(SceneTitle::TITLESTATE::TITLEDRAW);
	ChangeNextState();
}

void SceneTitle::Uninit()
{
	
}

void SceneTitle::Update()
{
	m_TitleStateContext.StateUpdate();
	ChangeNextState();

	for (PlayerController& pController : PlayerController::GetPlayerControllers())
	{
		if (pController.IsTriggerReturn())
		{
			CScene::SetScene<SceneSelect>();
			break;
		}
	}

}

void SceneTitle::Draw()
{
	//=====<画面描画>=====
	EnableDepth(false);
	
	m_BackGround.Draw();

	m_TitleStateContext.StateDraw();

	
	EnableDepth(true);
}

State* SceneTitle::SetNextState(TITLESTATE TitleState)
{
	switch (TitleState)
	{
	case SceneTitle::TITLESTATE::TITLEDRAW:
		m_TitleStateContext.SetNextState(new SceneTitle_TitleScreenState());
		break;
	case SceneTitle::TITLESTATE::TITLESELECT:
		m_TitleStateContext.SetNextState(nullptr);
		break;
	}

	return m_TitleStateContext.GetNextState();
}

void SceneTitle::ChangeNextState()
{
	if (m_TitleStateContext.GetNextState() != nullptr)
	{
		//終了処理
		m_TitleStateContext.StateUninit();

		//次のステートに変更
		m_TitleStateContext.ChangeNextState();

		//今のステートの各変数を設定

		//初期化処理
		m_TitleStateContext.StateInit();
	}
}
