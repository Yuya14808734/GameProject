#include "Game3D.h"
#include "Model.h"
#include "Shader.h"
//�V�[���̒ǉ�
#include "Scene.h"

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

	m_pWVP = new ConstantBuffer();
	m_pWVP->Create(sizeof(DirectX::XMFLOAT4X4) * 3);

	//�V�[���̏�����
	CScene::SetScene<CScene>();
}
Game3D::~Game3D()
{
	CScene::DestroyScene();		//�V�[���̍폜
	delete m_pWVP;
	delete m_pBlend;
}
void Game3D::Update()
{
	CScene::GetScene()->Update();
	CScene::SceneChange();
}
void Game3D::Draw()
{
	CScene::GetScene()->Draw();
}
