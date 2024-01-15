#include "SceneGame_StartState.h"
#include "CameraManager.h"

void SceneGame_StartState::Init()
{
	m_Count = 0;
}

void SceneGame_StartState::Uninit()
{

}

void SceneGame_StartState::Update()
{
	m_pGameStartCountUI->Update();

	m_Count++;

	if (m_Count == 1 * 60)
	{
		m_pGameStartCountUI->SetNumDraw(2);
	}

	if (m_Count == 2 * 60)
	{
		m_pGameStartCountUI->SetNumDraw(1);
	}

	if (m_Count == 3 * 60)
	{
		m_pGameStartCountUI->SetGoDraw(true);
		CameraManager::GetInstance().SetSceneCamera("GameCamera");
		m_pGameScene->SetNextState(SceneGame::GAMESTATE::GAMEPLAY);
	}
}

void SceneGame_StartState::Draw()
{
	//=====<ステージの描画>=====
	m_pStage->Stage_Draw();

	//=====<キャラクターの描画>=====
	for (Character* copy : (*m_pCharacters))
	{
		copy->Character_Draw();
	}

	//=====<UIの描画>=====
	EnableDepth(false);

	for (Character* copy : (*m_pCharacters))
	{
		copy->Character_UIDraw();
	}

	m_pGameStartCountUI->Draw();

	EnableDepth(true);
}
