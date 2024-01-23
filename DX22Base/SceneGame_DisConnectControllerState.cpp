#include "SceneGame_DisConnectControllerState.h"
#include "Main.h"
#include "Player_Controller.h"
#include "Scene01_Select.h"
#include "CameraManager.h"

void SceneGame_DisConnectControllerState::Init()
{
	CVector2 WindowSize = CVector2(
		static_cast<float>(GetAppWidth()),
		static_cast<float>(GetAppHeight())
	);

	m_DissConnectControllerTextImage.SetTexture("Assets/UI/DisConnectControllerImage.png");
	m_DissConnectControllerTextImage.SetPos(WindowSize * 0.5f);
	m_DissConnectControllerTextImage.SetSize(WindowSize);

	m_ReturnCount = 0.0f;

	CameraManager::GetInstance().StopCamera();
}

void SceneGame_DisConnectControllerState::Uninit()
{
	CameraManager::GetInstance().ReStartCamera();
}

void SceneGame_DisConnectControllerState::Update()
{
	//=====<この関数内で使う変数を作成>=====
	bool ReturnSelectScene = false;
	m_ReturnCount += 1.0f / 60.0f;

	//=====<セレクトに戻る>=====
	for (PlayerController& Controller : PlayerController::GetPlayerControllers())
	{
		if (Controller.IsTriggerReturn())
		{
			ReturnSelectScene = true;
			break;
		}
	}

	if (m_ReturnCount > SceneChangeWaitTime)
	{
		ReturnSelectScene = true;
	}

	//=====<セレクトシーンを読み込む>=====
	if (ReturnSelectScene)
	{
		//シーンの切り替え
		CScene::SetScene<SceneSelect>();
	}
}

void SceneGame_DisConnectControllerState::Draw()
{
	//=====<背景の描画>=====
	m_pBackGround->Draw();

	//=====<ステージの描画>=====
	m_pStage->Stage_Draw();

	//=====<キャラクターの描画>=====
	for (Character* copy : (*m_pCharacters))
	{
		copy->Character_Draw();
	}

	//=====<エフェクトの描画>=====
	for (EffectBase* pEffect : (*m_pEffects))
	{
		pEffect->Draw();
	}

	//=====<UIの描画>=====
	EnableDepth(false);

	for (Character* copy : (*m_pCharacters))
	{
		copy->Character_UIDraw();
	}

	m_pStockCountUI->Draw();
	
	//セレクトに戻るの描画
	m_DissConnectControllerTextImage.Draw();

	EnableDepth(true);

}
