#include "SceneResult_DrawResult.h"
#include "Player_Controller.h"
#include "Scene.h"
#include "Scene01_Select.h"

void SceneResult_DrawResult::Init()
{

}

void SceneResult_DrawResult::Uninit()
{

}

void SceneResult_DrawResult::Update()
{
	//=====<押してほしいボタンのテキストを切り替える>=====
	m_pPushButtonTextImage->Update();

	//=====<各コントローラーを取得してEnterかAが押されたら次のシーンに移動する>=====
	for (auto copyController : PlayerController::GetPlayerControllers())
	{
		if (copyController.IsTriggerReturn())
		{
			CScene::SetScene<SceneSelect>();
		}
	}	
}

void SceneResult_DrawResult::Draw()
{
	//=====<UIの描画>=====
	EnableDepth(false);

	//背景の描画
	m_pBackGround->Draw();

	//[Win]のテキスト描画
	m_pWinPanelImage->Draw();

	//キャラクター画像の位置を設定
	m_pCharacterImage->m_pos = CVector2(908.0f, 368.0f);
	m_pCharacterImage->m_size = CVector2(435.0f, 640.0f) * 1.3f;
	m_pCharacterImage->Draw();

	//[押してください]の描画
	m_pPushButtonTextImage->Draw();

	EnableDepth(true);
}
