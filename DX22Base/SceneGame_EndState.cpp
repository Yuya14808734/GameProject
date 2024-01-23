#include "SceneGame_EndState.h"
#include "Scene.h"
#include "Scene03_Result.h"
#include "Main.h"
#include "FadeIn00_GameEnd.h"

void SceneGame_EndState::Init()
{
	//=====<文字画像の設定>=====
	m_pGameEndTextUI->StartAnimetion();
	m_pGameEndTextUI->SetStartSize(CVector2(640.0f, 304.0f) * 2.0f);
	m_pGameEndTextUI->SetEndSize(CVector2(640.0f, 304.0f));
	m_SceneChangeCount = 0;
	
	//=====<レンダーターゲットへ描画するかの変数の初期化>=====
	m_WipeTextureWrite = false;
}

void SceneGame_EndState::Uninit()
{

}

void SceneGame_EndState::Update()
{
	m_pGameEndTextUI->Update();

	m_SceneChangeCount++;

	if (m_SceneChangeCount > 60 * 3)
	{
		//次のシーンにリザルト結果を送る
		int WinPlayerNum = 0;
		for (Character* pCharacter : (*m_pCharacters))
		{
			if (pCharacter->GetStock() > 0)
			{
				unsigned int BitPlayerNum = pCharacter->GetCharacterBit();

				WinPlayerNum =
					static_cast<int>(log2f(static_cast<float>(BitPlayerNum)));
				WinPlayerNum++;
			}
		}

		//勝ったプレイヤー番号を設定
		SceneResult::SetWinPlayerNum(WinPlayerNum);

		//=====<次の描画でレンダーターゲットに書き込みを行う>=====
		m_WipeTextureWrite = true;

		//シーンの切り替え
		CScene::SetScene<SceneResult>();
	}
}

void SceneGame_EndState::Draw()
{
	//=====<レンダーターゲットへ描画>=====
	SetRenderTargetTexture();

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

	m_pGameEndTextUI->Draw();

	EnableDepth(true);
}

void SceneGame_EndState::SetRenderTargetTexture()
{
	//=====<フェードで使うレンダーターゲットを設定するか>=====
	if (m_WipeTextureWrite)
	{
		//=====<ワイプで使うテクスチャを作るレンダーターゲットを設定>=====
		FadeInWipe::SetRenderTargets_WipeTexture();

		//=====<深度バッファ有効>=====
		EnableDepth(true);

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

		m_pGameEndTextUI->Draw();

		EnableDepth(true);

		//=====<デフォルトのレンダーターゲットに戻す>=====
		SetDefaultRenderTargets();
		EnableDepth(true);

		//=====<今描画したレンダーターゲットを渡してやる>=====
		FadeInWipe::SetRenderTargets_WipeTexture();
	}
}
