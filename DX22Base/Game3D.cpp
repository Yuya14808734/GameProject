#include "Game3D.h"
#include "Model.h"
#include "Shader.h"
//�V�[���̒ǉ�
#include "Scene.h"
#include "CameraManager.h"
#include "ModelDrawer.h"
#include "Collider.h"
#include "Scene00_Game.h"
#include "Scene01_Select.h"
#include "Select01_CharacterList.h"

Game3D::Game3D()
{
	//�摜�������@�̐ݒ�
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
	//blend.SrcBlend = D3D11_BLEND_ONE;		//������`�����ސF(�摜)
	//blend.DestBlend = D3D11_BLEND_ONE;
	m_pBlend->Create(blend);
	m_pBlend->Bind();

	ModelDrawer::InitModels();	//���f���̏�����	
	CScene::SetScene<SceneGame>();	//�V�[���̏�����

	SelectCharacterList::LoadTexture();

}
Game3D::~Game3D()
{
	SelectCharacterList::ReleaseTexture();

	CScene::DestroyScene();									//�V�[���̍폜
	CameraManager::GetInstance().DestroyAllCamera(true);	//���ׂẴJ�����̍폜
	ModelDrawer::UninitModels();							//���f���̍폜�Ȃ�
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
