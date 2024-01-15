#include "GameUI01_GameEndText.h"
#include "Main.h"
#include "ShaderManager.h"

GameEndText::GameEndText()
{
	//シェーダーの作成
	SetVertexShader(
		ShaderManager::CreateVertexShader("ComparisonColorPS", CreateShaderPath("ComparisonColorPS")));
	SetPixelShader(
		ShaderManager::CreatePixelShader("ComparisonColorPS", CreateShaderPath("ComparisonColorPS")));

	m_pConstantBuffer_ComparisonColor = new ConstantBuffer();
	m_pConstantBuffer_ComparisonColor->Create(sizeof(m_CamparisonColor));

	//テクスチャの読み込み
	SetTexture("Assets/UI/GameText.png");

	//位置の設定
	//スクリーンの真ん中に置く
	m_BasePos = CVector2(
		static_cast<float>(GetAppWidth() * 0.5f), 
		static_cast<float>(GetAppHeight()) * 0.5f);

	//最初は描画しない
	m_IsVisible = false;
}

GameEndText::~GameEndText()
{

}

void GameEndText::Update()
{
	switch (m_DrawState)
	{
	case GameEndText::SMALLER:
		SmallerUpdate();
		break;
	case GameEndText::SHAKE:
		ShakeUpdate();
		break;
	case GameEndText::NORMAL:
		NormalUpdate();
		break;
	}
}

void GameEndText::PrevDraw()
{
	m_pConstantBuffer_ComparisonColor->Write(&m_CamparisonColor);
	m_pConstantBuffer_ComparisonColor->BindVS(0);
}

void GameEndText::SetStartSize(const CVector3 & size)
{
	m_StartSize = size;
}

void GameEndText::SetEndSize(const CVector3 & size)
{
	m_EndSize = size;
}

void GameEndText::StartAnimetion()
{
	m_DrawState = GameEndText::DRAWSTATE::SMALLER;
	m_TimeCount = 0.0f;
	m_IsVisible = true;
}

void GameEndText::SmallerUpdate()
{
	m_TimeCount += 1.0f / 60.0f;
	
	//小さくする時間を超えていたら
	if (m_TimeCount > m_LerpEndTime)
	{
		m_DrawState = DRAWSTATE::SHAKE;
		m_size = m_EndSize;
		m_TimeCount = 0.0f;
		return;
	}

	float LerpPercent = m_TimeCount / m_LerpEndTime;
	//補間を使ってサイズを変更
	m_size = (m_StartSize * (1.0f - LerpPercent)) + (m_EndSize * LerpPercent);

	//サイズが決まるときにアルファが1になるようにする
	m_color.w = LerpPercent;
}

void GameEndText::ShakeUpdate()
{
	m_TimeCount += 1.0f / 60.0f;
	
	//揺らす時間を超えていたら
	if (m_TimeCount > m_LerpEndTime)
	{
		m_DrawState = DRAWSTATE::NORMAL;
		m_TimeCount = 0.0f;
		m_pos = CVector2::GetZero();
		return;
	}

	//揺らす処理
	//縦横-500~500の間の数値でランダムに揺らしてやる
	m_pos = CVector2(
		static_cast<float>((rand() % 1000) + 1) - 500.0f,
		static_cast<float>((rand() % 1000) + 1) - 500.0f
	);
}

void GameEndText::NormalUpdate()
{
	//最初の一秒のみ白くしてやる
	m_TimeCount += 1.0f / 60.0f;

	float ChangeColorPercent = m_TimeCount / m_TextChangeColorTime;

	//shaderに上の数値を渡す
}
