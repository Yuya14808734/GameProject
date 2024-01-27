#include "Scene00_Game.h"
#include "CameraManager.h"
#include "Camera00_Debug.h"
#include "Camera01_Game.h"
#include "Camera03_GameStart.h"
#include "ModelDrawer.h"
#include "Geometory.h"
#include "Input.h"
#include "Stage_00.h"
#include "Character_00.h"
#include "Select00_Character.h"
#include "Scene01_Select.h"
#include "Character_State.h"
#include "Character_Attack.h"

#include "SceneGame_StartState.h"
#include "SceneGame_GamePlayState.h"
#include "SceneGame_EndState.h"
#include "SceneGame_DisConnectControllerState.h"

bool Trigger = false;


void SceneGame::Init()
{
	//=====<カメラの生成>=====
	CameraManager::GetInstance().CreateCamera<CameraGame>("GameCamera");
	CameraManager::GetInstance().CreateCamera<CameraGameStart>("GameStartCamera");
	CameraManager::GetInstance().CreateCamera<CameraDebug>("DebugCamera");
	CameraManager::GetInstance().SetSceneCamera("DebugCamera");
	m_pGameCamera = static_cast<CameraGame*>(CameraManager::GetInstance().GetCamera("GameCamera"));
	CameraGameStart* pCameraGameStart = 
		static_cast<CameraGameStart*>(CameraManager::GetInstance().GetCamera("GameStartCamera"));

	//=====<ステージの作成>=====
	m_pStage = new Stage00();
	m_pStage->Stage_Init();

	//=====<キャラクターの生成>=====
	Character::InitPlayerBit();
	
	//=====<セレクトシーンで選んだキャラクターの生成>=====
	//===<一人目>===
	Character* FirstCharacter = CreateCharacter(SceneSelect::GetFirstPlayerCharacter());
	m_pFirstController = SceneSelect::GetFirstPlayerController();
	m_pFirstController = m_pFirstController == nullptr ?
		&PlayerController::GetPlayerControllers()[0] : m_pFirstController;
	FirstCharacter->SetCharacterController(m_pFirstController);
	FirstCharacter->Character_Init();
	//===<二人目>===
	Character* SecondCharacter = CreateCharacter(SceneSelect::GetSecondPlayerCharacter());
	SecondCharacter->Character_Init();
	m_pSecondController = SceneSelect::GetSecondPlayerController();
	m_pSecondController = m_pSecondController == nullptr ?
		&PlayerController::GetPlayerControllers()[1] : m_pSecondController;
	SecondCharacter->SetCharacterController(m_pSecondController);
	
	//=====<UIのパラメータの設定>=====
	m_GameStartCountUI.SetNumDraw(3);

	//=====<背景画像の設定>=====
	m_BackGround.SetTexture("Assets/BackGroundImage/BackGround00.png");
	m_BackGround.SetPos(CVector3(0.0f, 0.0f, 50.0f));
	m_BackGround.SetSize(CVector2(1200.0f,800.0f));
	m_BackGround.SetScale(CVector3::GetOne() * 0.2f);

	//=====<各オブジェクトに渡したいオブジェクトポインタがあるならここでする>=====
	for (Character* pCharacter : m_Characters)
	{
		pCharacter->SetStage(m_pStage);
	}

	m_pGameCamera->SetCharacter(&m_Characters);
	m_pGameCamera->SetStage(m_pStage);
	pCameraGameStart->SetCharacter(m_Characters);

	//=====<コントローラーが解除されているか>=====
	m_isDisConnectController = false;

	//=====<ゲーム開始に設定>=====
	SetNextState(SceneGame::GAMESTATE::GAMESTART);
	ChangeNextState();

	Trigger = false;
}

void SceneGame::Uninit()
{
	//=====<エフェクトの削除>=====
	SceneGame::EffectRelease();

	//=====<ステートのの削除>=====
	m_GameSceneStateContext.ReleaseAllState();

	//=====<キャラクターの削除>=====
	for (auto it = m_Characters.begin(); it != m_Characters.end();)
	{
		(*it)->Character_Uninit();
		delete (*it);
		it = m_Characters.erase(it);
	}

	//=====<ステージの削除>=====
	m_pStage->Stage_Uninit();
	delete m_pStage;

	//=====<カメラの削除>=====
	CameraManager::GetInstance().DestroyCamera("GameStartCamera", true);
	CameraManager::GetInstance().DestroyCamera("GameCamera", true);
}

void SceneGame::Update()
{
	//=====<コントローラーが抜かれたらゲームを終了する>=====
	//if (!m_isDisConnectController)
	//{	
	//	//もう入らないようにする
	//	m_isDisConnectController = true;

	//	if (!m_pFirstController->IsConnect() || !m_pSecondController->IsConnect())
	//	{
	//		//コントローラーが抜かれた
	//		SetNextState(SceneGame::GAMESTATE::GAMEDISCONNECTCONTROLLER);
	//		ChangeNextState();
	//		return;
	//	}
	//}

	//=====<ゲームシーンのステートのアップデート>=====
	m_GameSceneStateContext.StateUpdate();

	//=====<ゲームシーンのステートの入れ替え>=====
	ChangeNextState();


	//=====<エフェクトのアップデート>=====
	SceneGame::EffectUpdate();
}

void SceneGame::Draw()
{
	m_GameSceneStateContext.StateDraw();
}

Character* SceneGame::CreateCharacter(int Num)
{
	return CreateCharacter(static_cast<SelectCharacterList::CHARACTER>(Num));
}

Character* SceneGame::CreateCharacter(SelectCharacterList::CHARACTER CharacterNum)
{
	switch (CharacterNum)
	{
	case SelectCharacterList::CHARACTER::UNITYCHAN:
		m_Characters.push_back(new Character_00());
		break;
	case SelectCharacterList::CHARACTER::NONE:
	case SelectCharacterList::CHARACTER::MAX:
		m_Characters.push_back(new Character_00());
		break;
	}

	auto it = m_Characters.end();
	it--;
	return (*it);
}

State* SceneGame::SetNextState(GAMESTATE NextState)
{
	switch (NextState)
	{
	case SceneGame::GAMESTATE::GAMESTART:
		m_GameSceneStateContext.SetNextState(new SceneGame_StartState());
		break;
	case SceneGame::GAMESTATE::GAMEPLAY:
		m_GameSceneStateContext.SetNextState(new SceneGame_PlayState());
		break;
	case SceneGame::GAMESTATE::GAMEEND:
		m_GameSceneStateContext.SetNextState(new SceneGame_EndState());
		break;
	case SceneGame::GAMESTATE::GAMEDISCONNECTCONTROLLER:
		m_GameSceneStateContext.SetNextState(new SceneGame_DisConnectControllerState());
		break;
	}

	return m_GameSceneStateContext.GetNextState();
}

void SceneGame::ChangeNextState()
{
	if (m_GameSceneStateContext.GetNextState() != nullptr)
	{
		//終了処理
		m_GameSceneStateContext.StateUninit();

		//次のステートに変更
		m_GameSceneStateContext.ChangeNextState();

		//今のステートの各変数を設定
		SceneGame_BaseState* pState = static_cast<SceneGame_BaseState*>(m_GameSceneStateContext.GetNowState());
		pState->SetScene(this);
		pState->SetCharacters(&m_Characters);
		pState->SetStage(m_pStage);
		pState->SetGameCamera(m_pGameCamera);
		pState->SetBackGround(&m_BackGround);
		pState->SetStartCountUI(&m_GameStartCountUI);
		pState->SetEndTextUI(&m_GameEndTextUI);
		pState->SetStockCountUI(&m_StockCountUI);
		pState->SetEffect(&m_Effects);

		//初期化処理
		m_GameSceneStateContext.StateInit();
	}
}

void SceneGame::EffectUpdate()
{
	for (std::vector<EffectBase*>::iterator it = m_Effects.begin(); it != m_Effects.end();)
	{
		(*it)->Update();

		if ((*it)->GetisDestroy())
		{
			//削除
			delete (*it);
			it = m_Effects.erase(it);
			continue;
		}

		it++;
	}
}

void SceneGame::EffectDraw()
{
	for (EffectBase* pEffect : m_Effects)
	{
		pEffect->Draw();
	}
}

void SceneGame::EffectPause()
{
	for (EffectBase* pEffect : m_Effects)
	{
		pEffect->PausedEffect();
	}
}

void SceneGame::EffectRelease()
{
	for (EffectBase* pEffect : m_Effects)
	{
		delete pEffect;
	}

	m_Effects.clear();
}