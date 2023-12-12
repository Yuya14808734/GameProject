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
#include "XboxKeyboard.h"

//--- �萔��`
const unsigned int SCREEN_WIDTH = 1280;
const unsigned int SCREEN_HEIGHT = 720;

//-- �O���[�o���ϐ�
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
	EffectManager::EffectInit();

	g_pGame = new Game3D();
}
void MainUninit()
{
	delete g_pGame;
	EffectManager::EffectUninit();
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
	//�A�b�v�f�[�g
	//====================================================
	UpdateInput();
	UpdateGamePad();
	g_pGame->Update();

	//====================================================
	//�`��
	//====================================================
	BeginDrawDX();
	CameraBase* pCamera = CameraManager::GetInstance().GetSceneCamera();
	if (pCamera != nullptr)
	{
		SetGeometoryVPMatrix(
			CameraManager::GetInstance().GetSceneCamera()->GetViewMatrix(),
			CameraManager::GetInstance().GetSceneCamera()->GetProjectionMatrix());
	}
	g_pGame->Draw();

	EffectManager::Draw();
	EndDrawDX();

	//====================================================
	//�V�[���̓���ւ�
	//====================================================
	CScene::SceneChange();
}
