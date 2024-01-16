#include "Game3D.h"
#include "Model.h"
#include "Shader.h"
//シーンの追加
#include "Scene.h"
#include "CameraManager.h"
#include "ModelDrawer.h"
#include "Collider.h"
#include "Scene00_Game.h"
#include "Scene01_Select.h"
#include "Select01_CharacterList.h"

Game3D::Game3D()
{
	//画像合成方法の設定
	m_pBlend = new BlendState;
	D3D11_RENDER_TARGET_BLEND_DESC blend = {};
	blend.BlendEnable = TRUE;
	blend.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	blend.SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blend.SrcBlendAlpha = D3D11_BLEND_ONE;
	blend.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blend.DestBlendAlpha = D3D11_BLEND_ONE;
	blend.BlendOp = D3D11_BLEND_OP_ADD;
	blend.BlendOpAlpha = D3D11_BLEND_OP_ADD;
	//blend.SrcBlend = D3D11_BLEND_ONE;		//今から描きこむ色(画像)
	//blend.DestBlend = D3D11_BLEND_ONE;
	m_pBlend->Create(blend);
	m_pBlend->Bind();

	ModelDrawer::InitModels();	//モデルの初期化	
	CScene::SetScene<SceneGame>();	//シーンの初期化

	SelectCharacterList::LoadTexture();

}
Game3D::~Game3D()
{
	SelectCharacterList::ReleaseTexture();

	CScene::DestroyScene();									//シーンの削除
	CameraManager::GetInstance().DestroyAllCamera(true);	//すべてのカメラの削除
	ModelDrawer::UninitModels();							//モデルの削除など
	delete m_pBlend;
}
void Game3D::Update()
{
	CameraManager::GetInstance().CameraUpdate();
	CScene::GetScene()->Update();
}
void Game3D::Draw()
{
	CScene::GetScene()->Draw();
}

void Game3D::MiniWindowUpdate()
{
	CScene::GetScene()->MiniWindowUpdate();
}
