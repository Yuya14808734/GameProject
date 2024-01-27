#include "Scene04_Load.h"

void SceneLoad::Init()
{
	m_ColorFade.m_color = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
}

void SceneLoad::Uninit()
{

}

void SceneLoad::Update()
{
	m_LoadStateContext.StateUpdate();
	ChangeNextState();
}

void SceneLoad::Draw()
{
}

State* SceneLoad::SetNextState(LOADSTATE LoadState)
{
	switch (LoadState)
	{
	case SceneLoad::LOADSTATE::FADEIN:
		break;
	case SceneLoad::LOADSTATE::ANIMATION:
		break;
	case SceneLoad::LOADSTATE::LOAD:
		break;
	case SceneLoad::LOADSTATE::FADEOUT:
		break;
	}

	return m_LoadStateContext.GetNextState();
}

void SceneLoad::ChangeNextState()
{
	if (m_LoadStateContext.GetNextState() != nullptr)
	{
		//終了処理
		m_LoadStateContext.StateUninit();

		//次のステートに変更
		m_LoadStateContext.ChangeNextState();

		//今のステートの各変数を設定
		 
		
		//初期化処理
		m_LoadStateContext.StateInit();
	}
}
