#include "SceneLoad_LoadState.h"
#include "Scene00_Game.h"

void SceneLoad_LoadState::Init()
{
}

void SceneLoad_LoadState::Uninit()
{
}

void SceneLoad_LoadState::Update()
{
	//読み込みが終わり次第下の関数を呼ぶ(未実装)
	CScene::SetScene<SceneGame>();
}

void SceneLoad_LoadState::Draw()
{
	//===== < 画面描画>=====
	EnableDepth(false);

	m_pBackGround->Draw();

	m_pHideImage->Draw();

	for (VersusCharacterImageMove* copy : (*m_pCharacterImages))
	{
		copy->Draw();
	}

	m_pVersusIconImage->Draw();

	EnableDepth(true);

	EffectManager::EffectDraw(*m_pEfkHnd_FireSparks);
}
