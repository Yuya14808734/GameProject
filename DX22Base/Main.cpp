#include "Main.h"
#include "DirectX.h"
#include "WinUtil.h"
#include "DirectXTex/Texture.h"
#include "Input.h"
#include "Game3D.h"
#include "Geometory.h"
#include "Sprite.h"
#include "Sound.h"
#include "Effect_Manager.h"
#include "CameraManager.h"
#include "CameraBase.h"
#include "XboxKeyboard.h"
#include "MiniWindow.h"
#include "Player_Controller.h"
#include "ShaderManager.h"
#include "ModelDrawer.h"

//--- 定数定義
const unsigned int SCREEN_WIDTH = 1280;
const unsigned int SCREEN_HEIGHT = 720;

//-- グローバル変数
Game3D* g_pGame;

unsigned int GetAppWidth()
{
	return SCREEN_WIDTH;
}
unsigned int GetAppHeight()
{
	return SCREEN_HEIGHT;
}

void MainInit()
{
	if (FAILED(InitDX(GetHWND(), SCREEN_WIDTH, SCREEN_HEIGHT, false)))
	{
		Error("directx initialize failed.");
	}
	if (FAILED(InitTexture(GetDevice())))
	{
		Error("texture initialize failed.");
	}
	if (FAILED(InitInput()))
	{
		Error("input initialize failed.");
	}
	if (FAILED(InitGeometory()))
	{
		Error("geometory initialize failed.");
	}
	Sprite::Init();
	if (FAILED(InitXAudio2()))
	{
		
	}
	
	ShaderManager::InitShaders();
	InputXPad::XpadInit();
	PlayerController::PlayerController_Init();
	MiniWindow::WindowInit();
	EffectManager::EffectInit();
	ModelDrawer::InitModels();

	g_pGame = new Game3D();
}
void MainUninit()
{
	delete g_pGame;
	ModelDrawer::UninitModels();
	EffectManager::EffectUninit();
	MiniWindow::WindowUninit();
	ShaderManager::UninitShaders();
	UninitXAudio2();
	Sprite::Uninit();
	UninitGeometory();
	UninitInput();
	UninitTexture();
	UninitDX();
}
void MainLoop()
{
	//====================================================
	//アップデート
	//====================================================
	UpdateInput();
	InputXPad::XpadUpdate();
	PlayerController::PlayerController_Update();

	g_pGame->Update();
	EffectManager::EffectUpdate();

	//====================================================
	//描画
	//====================================================
	BeginDrawDX();
	CameraBase* pCamera = CameraManager::GetInstance().GetSceneCamera();
	if (pCamera != nullptr)
	{
		SetGeometoryVPMatrix(
			CameraManager::GetInstance().GetSceneCamera()->GetViewMatrix(),
			CameraManager::GetInstance().GetSceneCamera()->GetProjectionMatrix());
			CameraManager::GetInstance().GetSceneCamera()->CreateViewingFrustum();
	}

	g_pGame->Draw();

	//MiniWindow::WindowDrawUpdate();
	//g_pGame->MiniWindowUpdate();

	EndDrawDX();

	//====================================================
	//シーンの入れ替え
	//====================================================
	CScene::SceneChange();
}
