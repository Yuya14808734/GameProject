#include "GAMEUI.h"
#include "Sprite.h"
#include "DirectXTex/Texture.h"

GameUI::GameUI()
{
	LoadTextureFromFile("Assets/2D/Glass19.png",
		&m_pNazoBar);
}


GameUI::~GameUI()
{
	m_pNazoBar->Release();
}

void GameUI::Draw()
{
	//2D表示のための行列を設定
	//①ビュー行列はカメラの位置が関係ないので
	//初期化されてる行列を使う
	/*単位行列
	|１０００|
	|０１００|
	|００１０|
	|０００１|
	*/

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
			1280.0f,//画面右端の座標
			720.0f,	//画面下端の座標
			0.0f,	//画面上端の座標
			-1.0f,	//2方向で写せる最小値
			1.0f	//2方向で写せる最大値
			)
		));

	//ワールド行列で画面の表示位置を計算
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(
		1100.0f,
		680.0f, 0.0f);
	DirectX::XMFLOAT4X4 fWorld;
	DirectX::XMStoreFloat4x4(&fWorld,
		DirectX::XMMatrixTranspose(T));

	//スプライトの設定
	Sprite::SetWorld(fWorld);
	Sprite::SetView(fView);
	Sprite::SetProjection(fProj);
	Sprite::SetSize(DirectX::XMFLOAT2(300.0f, -20.0f));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetTexture(m_pNazoBar);
	Sprite::Draw();

}