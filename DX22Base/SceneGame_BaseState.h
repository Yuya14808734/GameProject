#pragma once
#include "StatePattern.h"
#include "Scene00_Game.h"
#include <vector>
#include "Character_Base.h"
#include "Stage_Base.h"
#include "Camera01_Game.h"
#include "Select01_CharacterList.h"
#include "GameUI00_StartCount.h"
#include "GameUI01_GameEndText.h"
#include "GameUI02_StockCount.h"
#include "Image3D.h"

class SceneGame_BaseState : public State
{
public:
	SceneGame_BaseState() {};
	virtual ~SceneGame_BaseState() override {};
	virtual void Init() override {};
	virtual void Update() override {};
	virtual void Draw() override {};

public:
	void SetScene(SceneGame* pScene)
	{ m_pGameScene = pScene; }

	void SetCharacters(std::vector<Character*>* pCharacters)
	{ m_pCharacters = pCharacters; }
	
	void SetStage(Stage* pStage) 	
	{ m_pStage = pStage; }

	void SetGameCamera(CameraGame* pGameCamera) 
	{ m_pGameCamera = pGameCamera; }

	void SetBackGround(Image3D* pBackGround) 
	{ m_pBackGround = pBackGround; }

	void SetStartCountUI(GameStartCountUI* pStartCountUI)
	{ m_pGameStartCountUI = pStartCountUI; }

	void SetEndTextUI(GameEndText* pGameEndTextUI) 
	{ m_pGameEndTextUI = pGameEndTextUI; }

	void SetStockCountUI(StockCountUI* pStockCountUI) 
	{ m_pStockCountUI = pStockCountUI; }

protected:
	std::vector<Character*>* m_pCharacters = nullptr;	//キャラクターの情報
	SceneGame* m_pGameScene = nullptr;					//今のゲームシーン
	Stage* m_pStage = nullptr;							//ステージの情報
	CameraGame* m_pGameCamera = nullptr;				//ゲームのカメラ
	Image3D* m_pBackGround = nullptr;					//バックグラウンド
	GameStartCountUI* m_pGameStartCountUI = nullptr;	//最初のカウントUI
	GameEndText* m_pGameEndTextUI = nullptr;			//ゲームエンドUI
	StockCountUI* m_pStockCountUI = nullptr;			//ストックが減った時のUI
};