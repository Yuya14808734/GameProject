#include "SceneResult_DrawResult.h"
#include "Player_Controller.h"
#include "Scene.h"
#include "Scene01_Select.h"

void SceneResult_DrawResult::Init()
{
	m_pResultWinnerCharacterImage->DrawStart(1.0f);
	m_nFrameCount = 0;
	m_pPushButtonTextImage->SetScale(0.9f);
}

void SceneResult_DrawResult::Uninit()
{

}

void SceneResult_DrawResult::Update()
{
	//=====<フレームの更新>=====
	m_nFrameCount++;

	//=====<ある程度時間がたったらパネルを描画>=====
	if (m_nFrameCount == 30)
	{
		m_pResultWinnerNumPanel->DrawStart(1.0f);
	}

	//=====<キャラクターを描画しながら移動する>=====
	m_pResultWinnerCharacterImage->Update();

	//=====<パネルを不透明にしながら小さくする>=====
	m_pResultWinnerNumPanel->Update();

	//=====<ボタンを押せるようにする>=====
	if (m_nFrameCount > 120)
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
}

void SceneResult_DrawResult::Draw()
{
	//=====<UIの描画>=====
	EnableDepth(false);

	//背景の描画
	m_pBackGround->Draw();

	//[Win]のテキスト描画
	m_pResultWinnerNumPanel->Draw();

	//キャラクター画像の位置を設定
	m_pResultWinnerCharacterImage->Draw();

	//[押してください]の描画
	if (m_nFrameCount > 90)
	{
		m_pPushButtonTextImage->Draw();
	}

	EnableDepth(true);
}
