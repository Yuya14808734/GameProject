#include "UIBase.h"
#include "Main.h"


UI_Base::UI_Base()
	:m_pTexture(nullptr)
	, m_pos({0.0f,0.0f,0.0f})
	,m_size({ 1.0f,1.0f})
	,m_UVpos({ 0.0f,0.0f})
	,m_UVsize({ 1.0f,1.0f})
{

}

UI_Base::~UI_Base()
{

}

void UI_Base::Update()
{

}

void UI_Base::Draw()
{
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
		m_pos.x,
		m_pos.y, m_pos.z);
	DirectX::XMFLOAT4X4 fWorld;
	DirectX::XMStoreFloat4x4(&fWorld,
		DirectX::XMMatrixTranspose(T));

	//スプライトの設定
	Sprite::SetWorld(fWorld);
	Sprite::SetView(fView);
	Sprite::SetProjection(fProj);
	Sprite::SetSize(m_size);
	Sprite::SetUVPos(m_UVpos);
	Sprite::SetUVScale(m_UVsize);
	Sprite::SetTexture(m_pTexture);
	Sprite::Draw();
}

void UI_Base::SetPos(DirectX::XMFLOAT3 pos)
{
	m_pos = pos;
}
void UI_Base::SetSize(DirectX::XMFLOAT2 size)
{
	m_size = size;
}