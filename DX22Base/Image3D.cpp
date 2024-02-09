#include "Image3D.h"
#include "Main.h"
#include "CameraManager.h"

Image3D::Image3D()
	:m_pTexture(nullptr)
	, m_pVertexShader(nullptr)
	, m_pPixelShader(nullptr)
	, m_BasePos(CVector3(0.0f,0.0f,0.0f))
	, m_pos(CVector3(0.0f,0.0f,0.0f))
	, m_size(CVector2(1.0f,1.0f))
	, m_scale(CVector3(1.0f, 1.0f, 1.0f))
	, m_rotate(CVector3(0.0f, 0.0f, 0.0f))
	, m_UVpos({ 0.0f,0.0f })
	, m_UVsize({ 1.0f,1.0f })
	, m_color({ 1.0f,1.0f,1.0f,1.0f })
	, m_Billboard(false)
{
}

Image3D::~Image3D()
{
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
}

void Image3D::Update()
{
}

void Image3D::Draw()
{
	//テクスチャがない場合
	if (m_pTexture == nullptr)
	{
		return;
	}

	CameraBase* pCamera = CameraManager::GetInstance().GetSceneCamera();

	//カメラが設定されていない場合
	if (pCamera == nullptr)
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

	DirectX::XMFLOAT4X4 mat[3];
	DirectX::XMMATRIX worldmat;

	worldmat = DirectX::XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
	worldmat *= DirectX::XMMatrixRotationQuaternion(m_rotate.v);
	worldmat *= DirectX::XMMatrixTranslation(
		m_pos.x + m_BasePos.x,
		m_pos.y + m_BasePos.y,
		m_pos.z + m_BasePos.z
	);

	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(worldmat));
	mat[1] = pCamera->GetViewMatrix();		//カメラの情報が分かり次第実装

	//ビルボードをする場合
	if (m_Billboard)
	{
		DirectX::XMMATRIX matInv = DirectX::XMLoadFloat4x4(&mat[1]);
		matInv = DirectX::XMMatrixTranspose(matInv);		//転置
		DirectX::XMStoreFloat4x4(&mat[1], matInv);
		mat[1]._41 = mat[1]._42 = mat[1]._43 = 0.0f;
		matInv = DirectX::XMLoadFloat4x4(&mat[1]);
		matInv = DirectX::XMMatrixInverse(nullptr, matInv);	//逆行列
		DirectX::XMStoreFloat4x4(&mat[1], matInv);
		DirectX::XMStoreFloat4x4(&mat[0],
			DirectX::XMMatrixTranspose(matInv * worldmat));
	}

	mat[2] = pCamera->GetProjectionMatrix();		//カメラの情報が分かり次第実装

	//スプライトの設定
	Sprite::SetWorld(mat[0]);
	Sprite::SetView(mat[1]);
	Sprite::SetProjection(mat[2]);
	Sprite::SetSize(m_size.f,true);
	Sprite::SetUVPos(m_UVpos.f);
	Sprite::SetUVScale(m_UVsize.f);
	Sprite::SetTexture(m_pTexture);
	Sprite::SetColor(m_color);
	Sprite::Draw();
}

void Image3D::SetTexture(const char* FilePath)
{
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}

	LoadTextureFromFile(FilePath, &m_pTexture);
}

void Image3D::ReleaseTexture()
{
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
}

void Image3D::SetPos(const DirectX::XMFLOAT3& pos)
{
	m_pos.f = pos;
}

void Image3D::SetPos(const CVector3& pos)
{
	m_pos = pos;
}

void Image3D::SetPos(const CVector2& pos)
{
	m_pos = pos;
}

const CVector3& Image3D::GetPos() const
{
	return m_pos;
}

void Image3D::SetSize(const DirectX::XMFLOAT2& size)
{
	m_size.f = size;
}

void Image3D::SetSize(const CVector2& size)
{
	m_size = size;
}

const CVector2& Image3D::GetSize() const
{
	return m_size;
}

void Image3D::SetScale(const DirectX::XMFLOAT3& size)
{
	m_scale.f = size;
}

void Image3D::SetScale(const CVector3& size)
{
	m_scale = size;
}

const CVector3& Image3D::GetScale() const 
{
	return m_scale;
}

void Image3D::SetRotate(CVector3 rotate)
{
	m_rotate.SetQuaternion(rotate.x, rotate.y, rotate.z);
}

void Image3D::SetRotate(CQuaternion quaternion)
{
	m_rotate = quaternion;
}

void Image3D::SetUVPos(const DirectX::XMFLOAT2& uvpos)
{
	m_UVpos.f = uvpos;
}

void Image3D::SetUVPos(const CVector2& uvpos)
{
	m_UVpos = uvpos;
}

const CVector2& Image3D::GetUVPos() const
{
	return m_UVpos;
}

void Image3D::SetUVSize(const DirectX::XMFLOAT2& uvsize)
{
	m_UVsize.f = uvsize;
}

void Image3D::SetUVSize(const CVector2& uvsize)
{
	m_UVsize = uvsize;
}

const CVector2& Image3D::GetUVSize() const
{
	return m_UVsize;
}

void Image3D::SetVertexShader(VertexShader* pVS)
{
	if (m_pVertexShader != nullptr)
	{
		delete m_pVertexShader;
		m_pVertexShader = nullptr;
	}

	m_pVertexShader = pVS;
}

void Image3D::SetPixelShader(PixelShader* pPS)
{
	if (m_pPixelShader != nullptr)
	{
		delete m_pPixelShader;
		m_pPixelShader = nullptr;
	}

	m_pPixelShader = pPS;
}

void Image3D::SetBillboard(bool billboard)
{
	m_Billboard = billboard;
}
