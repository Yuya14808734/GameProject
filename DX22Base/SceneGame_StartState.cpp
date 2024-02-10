#include "SceneGame_StartState.h"
#include "CameraManager.h"
#include "ShaderManager.h"

void SceneGame_StartState::Init()
{
	m_Count = 0;

	CameraManager::GetInstance().SetSceneCamera("GameStartCamera");

	for (auto copy : (*m_pCharacters))
	{
		copy->SetNextState(Character::STATE::State_StartAnime);
		copy->ChangeNextState();
	}
}

void SceneGame_StartState::Uninit()
{
	for (auto copy : (*m_pCharacters))
	{
		copy->SetNextState(Character::STATE::State_Idle);
		copy->ChangeNextState();
	}
}

void SceneGame_StartState::Update()
{
	//=====<キャラクターのアップデート>=====

	//ここで攻撃や移動などのアップデートを行う
	for (std::vector<Character*>::iterator it = m_pCharacters->begin();
		it != m_pCharacters->end(); it++)
	{
		(*it)->Character_Update();				//キャラクターのアップデートを行う
	}

	m_pGameStartCountUI->Update();

	m_Count++;

	if (m_Count == 2 * 60)
	{
		m_pGameStartCountUI->SetNumDraw(2);
	}

	if (m_Count == 3 * 60)
	{
		m_pGameStartCountUI->SetNumDraw(1);
	}

	if (m_Count == 4 * 60)
	{
		m_pGameStartCountUI->SetGoDraw(true);
		//CameraManager::GetInstance().SetSceneCamera("GameCamera");
		m_pGameScene->SetNextState(SceneGame::GAMESTATE::GAMEPLAY);
	}
}

void SceneGame_StartState::Draw()
{
	//=====<シャドウマップの描画>=====
	m_pGameScene->LightCameraDraw();
	CameraManager::GetInstance().SetSceneCamera("GameStartCamera");

	//=====<背景の描画>=====
	m_pBackGround->Draw();

	//=====<影のシェーダーの設定>=====
	ShaderManager::SetAllObjectVS("DepthShadowVS");
	ShaderManager::SetAllObjectPS("DepthShadowPS");
	ShaderManager::SetUseAllObjectVS(true);
	ShaderManager::SetUseAllObjectPS(true);
	DirectX::XMMATRIX LVP = 
		m_pLightCamera->GetViewMatrix_TypeXMMAXRIX() *
		m_pLightCamera->GetProjectionMatrix_TypeXMMAXRIX();
	DirectX::XMFLOAT4X4 matrix;
	DirectX::XMStoreFloat4x4(&matrix, 
		DirectX::XMMatrixTranspose(LVP));
	m_pLightLVPMatrixBuffer->Write(&matrix);
	m_pLightLVPMatrixBuffer->BindVS(2);
	SetTexturePS(m_pShadowMapRenderTarget->GetResource(),1);
	m_pLightCamera->SetParameter();

	//=====<ステージの描画>=====
	m_pStage->Stage_Draw();

	//=====<キャラクターの描画>=====
	for (Character* copy : (*m_pCharacters))
	{
		copy->Character_Draw();
	}

	//=====<影の描画は終わる>=====
	ShaderManager::SetUseAllObjectVS(false);
	ShaderManager::SetUseAllObjectPS(false);

	//=====<エフェクトの描画>=====
	for (EffectBase* pEffect : (*m_pEffects))
	{
		pEffect->Draw();
	}

	//=====<UIの描画>=====
	EnableDepth(false);

	for (Character* copy : (*m_pCharacters))
	{
		copy->Character_UIDraw();
	}

	if (m_Count > 1 * 60)
	{
		m_pGameStartCountUI->Draw();
	}

	EnableDepth(true);
}
