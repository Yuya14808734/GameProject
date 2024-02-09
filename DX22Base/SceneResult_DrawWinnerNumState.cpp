#include "SceneResult_DrawWinnerNumState.h"
#include "Player_Controller.h"
#include "Scene.h"
#include "Scene01_Select.h"

void SceneResult_DrawWinnderNumState::Init()
{
	//=====<fadeを始める>=====
	m_pStartWipeFade->SetFadeStart(true);
	m_pStartWipeFade->WipeSetting(0.5f, CVector2(1.0f, 1.0f));

	m_pHideImage->m_color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 0.75f);

	m_nCount = 0;
}

void SceneResult_DrawWinnderNumState::Uninit()
{
	//=====<ワイプで使うテクスチャを作るレンダーターゲットを削除>=====
	FadeInWipe::ReleaseRenderTargets_WipeTexture();
}

void SceneResult_DrawWinnderNumState::Update()
{
	m_nCount++;

	//=====<各画像のフェードイン・アウトのタイミング設定>=====
	if (m_nCount == 60)  { m_pPraiseWinnerPlayerText->StartFadeIn_LetterMove(0.8f); }
	if (m_nCount == 120) { m_pPraiseWinnerPlayerText->StartFadeIn_WinnerNum(0.5f);	}
	if (m_nCount == 250) { m_pPraiseWinnerPlayerText->StartFadeOut_LetterMove(0.5f);}
	if (m_nCount == 250) { m_pPraiseWinnerPlayerText->StartFadeOut_WinnerNum(0.5f); }

	//=====<フェードの更新>=====
	m_pStartWipeFade->Update();

	//=====<文字を動かす>=====
	m_pPraiseWinnerPlayerText->Update();

	//=====<後ろを隠している画像のアルファを0にしていく>=====
	const int AlphaChangeFrame = 300;
	if (m_nCount > AlphaChangeFrame)
	{
		float Percent = static_cast<float>(m_nCount - AlphaChangeFrame) / 20.0f;
		Percent = 1.0f - Percent;
		m_pHideImage->m_color.w = 0.75f * Percent;
	}

	//=====<次のステートの読み込み>=====
	if (m_nCount > 340)
	{
		m_pSceneResult->SetNextState(SceneResult::RESULTSTATE::RESULTDRAW);
	}	
}

void SceneResult_DrawWinnderNumState::Draw()
{
	//=====<UIの描画>=====
	EnableDepth(false);

	//背景の描画
	m_pBackGround->Draw();

	//後ろを隠してやる白い画像の描画
	m_pHideImage->Draw();

	//[WINNER]と勝ったプレイヤーの番号のテキスト描画
	m_pPraiseWinnerPlayerText->Draw();

	//フェードの描画
	m_pStartWipeFade->Draw();

	EnableDepth(true);
}
