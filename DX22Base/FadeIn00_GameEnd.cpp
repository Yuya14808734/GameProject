
#include "FadeIn00_GameEnd.h"
#include "Main.h"
#include "ShaderManager.h"

//================================================
// static
//================================================

RenderTarget* FadeInWipe::m_pRenderTarget_WipeTexture = nullptr;
DepthStencil* FadeInWipe::m_pDepthStencil_WipeTexture = nullptr;

void FadeInWipe::CreateRenderTarget_WipeTexture()
{
	// =====<念のため消しておく>=====
	ReleaseRenderTargets_WipeTexture();

	// =====<レンダーターゲットの作成>=====
	if (m_pRenderTarget_WipeTexture == nullptr)
	{
		m_pRenderTarget_WipeTexture = new RenderTarget();
		m_pRenderTarget_WipeTexture->Create(DXGI_FORMAT_R8G8B8A8_UNORM,
			GetAppWidth(), GetAppHeight());
	}

	//=====<深度ステンシルの作成>=====
	if (m_pDepthStencil_WipeTexture == nullptr)
	{
		m_pDepthStencil_WipeTexture = new DepthStencil();
		m_pDepthStencil_WipeTexture->Create(
			static_cast<float>(GetAppWidth()),
			static_cast<float>(GetAppHeight()), false);
	}
}

void FadeInWipe::SetRenderTargets_WipeTexture()
{
	//=====<レンダーターゲットを作成する>=====
	CreateRenderTarget_WipeTexture();

	//=====<レンダーターゲットの中を消してやる>=====
	m_pRenderTarget_WipeTexture->Clear();
	m_pDepthStencil_WipeTexture->Clear();

	//=====<レンダーターゲットを設定する>=====
	SetRenderTargets(1, &m_pRenderTarget_WipeTexture, m_pDepthStencil_WipeTexture);
}

void FadeInWipe::ReleaseRenderTargets_WipeTexture()
{
	//=====<レンダーターゲットの削除>=====
	if (m_pRenderTarget_WipeTexture != nullptr)
	{
		delete m_pRenderTarget_WipeTexture;
		m_pRenderTarget_WipeTexture = nullptr;
	}

	//=====<深度ステンシルの削除>=====
	if (m_pDepthStencil_WipeTexture != nullptr)
	{
		delete m_pDepthStencil_WipeTexture;
		m_pDepthStencil_WipeTexture = nullptr;
	}
}

// ================================================
// クラスの実装
// ================================================

FadeInWipe::FadeInWipe()
	:m_WipeTime(0.0f),
	m_CountTime(0.0f),
	m_pConstuntBuffer(nullptr)
{
	//=====<定数バッファの作成>=====
	m_pConstuntBuffer = new ConstantBuffer();
	m_pConstuntBuffer->Create(sizeof(DirectX::XMFLOAT4));

	//=====<Wipe用のシェーダーを作成・設定>=====
	SetPixelShader(
		ShaderManager::CreatePixelShader
		("DirectWipePS", CreateShaderPath("DirectWipePS"))
		,false);

	//=====<テクスチャの設定>=====
	SetWipeTexture();
}

FadeInWipe::~FadeInWipe()
{
	//=====<メモリの削除処理>=====
	delete m_pConstuntBuffer;
}

void FadeInWipe::FadeUpdate()
{
	//=====<WipeTimeが設定していなければ出る>=====
	if (m_WipeTime == 0.0f)
	{
		return;
	}

	//=====<左上から透明にしていくため数値を上げていく>=====
	m_CountTime += (1.0f / 60.0f);

	////=====<すべて見えるようになったらtrueにする>=====
	if (m_CountTime > m_WipeTime)
	{
		m_FadeEnd = true;
	}
}

void FadeInWipe::PrevDraw()
{
	//=====<定数バッファで渡すfloat4の値設定>=====
	float NowSize = (m_CountTime / m_WipeTime) * m_WipeSize;

	DirectX::XMFLOAT4 CB =
	{ m_WipeDirection.x,m_WipeDirection.y,NowSize,0.0f };
	m_pConstuntBuffer->Write(&CB);
	m_pConstuntBuffer->BindPS(0);
}

void FadeInWipe::WipeSetting(float WipeTime, const CVector2& WipeDirection)
{
	SetWipeTime(WipeTime);
	SetWipeDirection(WipeDirection);
	SetWipeTexture();
}

void FadeInWipe::SetWipeTime(float time)
{
	m_WipeTime = time;
}

void FadeInWipe::SetWipeDirection(const CVector2& Direction)
{
	m_WipeDirection = Direction;
	m_WipeDirection = m_WipeDirection.normalize();
	SetWipeSize();
}

void FadeInWipe::SetWipeSize()
{
	//=====<ウィンドウの大きさを設定>=====
	CVector2 WindowSize = 
		CVector2(
			static_cast<float>(GetAppWidth()),
			static_cast<float>(GetAppHeight()));

	//=====<今のDirectionでどっちが早く画面の端につくのかを調べる>=====
	//下で使う変数の作成
	float Width_Percent		= m_WipeDirection.x / WindowSize.x;
	float Height_Percent	= m_WipeDirection.y / WindowSize.y;
	CVector2 WindowWipeVector;
	float WindowPercent = 0.0f;

	//早く着く方の大きさを画面サイズにしたときの長さを調べる
	if (Width_Percent > Height_Percent)
	{
		//横の方が早く着く場合、縦の大きさを使って正方形にする
		WindowPercent = m_WipeDirection.y * (WindowSize.y / m_WipeDirection.y);
	}
	else
	{
		//縦の方が早く着く場合、横の大きさを使って正方形にする
		WindowPercent = m_WipeDirection.x * (WindowSize.x / m_WipeDirection.x);
	}

	//=====<斜めの長さを調べてワイプする長さとする>=====
	WindowWipeVector = m_WipeDirection * WindowPercent;
	m_WipeSize = WindowWipeVector.length();
}

void FadeInWipe::SetWipeTexture()
{
	if (m_pRenderTarget_WipeTexture == nullptr)
	{
		SetTexture("Assets/Texture/Fire.png");
	}
	else
	{
		SetTexture(m_pRenderTarget_WipeTexture->GetResource());
	}

}
