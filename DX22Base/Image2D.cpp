#include "Image2D.h"
#include "Main.h"

Image2D::Image2D()
	:m_pTexture(nullptr)
	, m_isPathLoad(false)
	, m_pVertexShader(nullptr)
	, m_pPixelShader(nullptr)
	, m_BasePos({0.0f,0.0f,0.0f})
	, m_pos({ 0.0f,0.0f,0.0f })
	, m_size({ 1.0f,1.0f })
	, m_UVpos({ 0.0f,0.0f })
	, m_UVsize({ 1.0f,1.0f })
	, m_color({ 1.0f,1.0f,1.0f,1.0f })
	, m_IsVisible(true)
{

}

Image2D::~Image2D()
{
	ReleaseTexture();
}

void Image2D::Update()
{

}

void Image2D::PrevDraw()
{
}

void Image2D::Draw()
{
	if (!m_IsVisible)
	{
		return;
	}

	if (m_pTexture == nullptr)
	{
		return;
	}	

	PrevDraw();

	//シェーダーの変更
	if (m_pVertexShader != nullptr)
	{
		Sprite::SetVertexShader(m_pVertexShader);
	}
	else
	{
		Sprite::SetDefaultVertexShader();
	}

	if (m_pPixelShader != nullptr)
	{
		Sprite::SetPixelShader(m_pPixelShader);
	}
	else
	{
		Sprite::SetDefaultPixelShader();
	}

	DirectX::XMFLOAT4X4 fView;
	DirectX::XMStoreFloat4x4(&fView,
		DirectX::XMMatrixIdentity());

	//②プロジェクション行列が重要
	//この行列で2Dのスクリーンの大きさを決める
	DirectX::XMFLOAT4X4 fProj;
	DirectX::XMStoreFloat4x4(&fProj,
		DirectX::XMMatrixTranspose(
			DirectX::XMMatrixOrthographicOffCenterLH(
				0.0f,//画面左端の座標
				GetAppWidth(),//画面右端の座標
				GetAppHeight(),	//画面下端の座標
				0.0f,	//画面上端の座標
				-1.0f,	//2方向で写せる最小値
				1.0f	//2方向で写せる最大値
			)
		));

	//ワールド行列で画面の表示位置を計算
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(
		m_pos.x + m_BasePos.x,
		m_pos.y + m_BasePos.y,
		m_pos.z + m_BasePos.z);
	DirectX::XMFLOAT4X4 fWorld;
	DirectX::XMStoreFloat4x4(&fWorld,
		DirectX::XMMatrixTranspose(T));

	//スプライトの設定
	Sprite::SetWorld(fWorld);
	Sprite::SetView(fView);
	Sprite::SetProjection(fProj);
	Sprite::SetSize(m_size.f);
	Sprite::SetUVPos(m_UVpos.f);
	Sprite::SetUVScale(m_UVsize.f);
	Sprite::SetTexture(m_pTexture);
	Sprite::SetColor(m_color);
	Sprite::Draw();
}

void Image2D::SetTexture(const char* FilePath)
{
	ReleaseTexture();

	LoadTextureFromFile(FilePath, &m_pTexture);

	m_isPathLoad = true;
}

void Image2D::SetTexture(ID3D11ShaderResourceView* pTextureResource)
{
	ReleaseTexture();

	m_pTexture = pTextureResource;

	m_isPathLoad = false;
}

void Image2D::ReleaseTexture()
{
	//パスでロードをしていた場合
	if (m_isPathLoad)
	{
		if (m_pTexture != nullptr)
		{
			m_pTexture->Release();
			m_pTexture = nullptr;
		}
	}
}

void Image2D::SetPos(const DirectX::XMFLOAT3& pos)
{
	m_pos.f = pos;
}
void Image2D::SetPos(const CVector3& pos)
{
	m_pos = pos;
}
void Image2D::SetPos(const CVector2& pos)
{
	m_pos = pos;
}
const CVector3& Image2D::GetPos()
{
	return m_pos;
}
void Image2D::SetSize(const DirectX::XMFLOAT2& size)
{
	m_size.f = size;
}

void Image2D::SetSize(const CVector2& size)
{
	m_size = size;
}

const CVector2& Image2D::GetSize()
{
	return m_size;
}

void Image2D::SetUVPos(const DirectX::XMFLOAT2& uvpos)
{
	m_UVpos.f = uvpos;
}

void Image2D::SetUVPos(const CVector2& uvpos)
{
	m_UVpos = uvpos;
}

const CVector2& Image2D::GetUVPos()
{
	return m_UVpos;
}

void Image2D::SetUVSize(const DirectX::XMFLOAT2& uvsize)
{
	m_UVsize.f = uvsize;
}

void Image2D::SetUVSize(const CVector2& uvsize)
{
	m_UVsize = uvsize;
}

const CVector2& Image2D::GetUVSize()
{
	return m_UVsize;
}

void Image2D::SetVertexShader(VertexShader* pVS, bool MemoryDelete)
{
	if (MemoryDelete)
	{
		if (m_pVertexShader != nullptr)
		{
			delete m_pVertexShader;
			m_pVertexShader = nullptr;
		}
	}

	m_pVertexShader = pVS;
}

void Image2D::SetPixelShader(PixelShader* pPS, bool MemoryDelete)
{
	if (MemoryDelete)
	{
		if (m_pPixelShader != nullptr)
		{
			delete m_pPixelShader;
			m_pPixelShader = nullptr;
		}
	}

	m_pPixelShader = pPS;
}
