// ====================================================
// �C���N���[�h
// ====================================================
#include "Game3D.h"
#include "CameraManager.h"
#include "Collider.h"
#include "Select01_CharacterList.h"

// =====<�V�[���t�@�C���̃C���N���[�h>=====
#include "Scene.h"
#include "Scene00_Game.h"
#include "Scene01_Select.h"
#include "Scene02_Title.h"
#include "Scene03_Result.h"
#include "Scene04_Load.h"

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

	
	//=====<�V�[���̏�����>=====
	CScene::SetScene<SceneLoad>();

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
