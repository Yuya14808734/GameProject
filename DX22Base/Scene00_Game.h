#pragma once
#include "Scene.h"
#include <vector>
#include "Character_Base.h"
#include "Stage_Base.h"
#include "Camera01_Game.h"
#include "Select01_CharacterList.h"
#include "GameUI00_StartCount.h"
#include "GameUI01_GameEndText.h"
#include "GameUI02_StockCount.h"
#include "Image3D.h"
#include "StatePattern.h"
#include "Player_Controller.h"
#include "EffectBase.h"

class SceneGame : public CScene
{
public:
	enum class GAMESTATE : int
	{
		GAMELOAD = 0,
		GAMESTART,
		GAMEPLAY,
		GAMEEND,
		GAMEDISCONNECTCONTROLLER,
		MAX,
	};

public:
	SceneGame() {};
	~SceneGame() override {};

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	State* SetNextState(GAMESTATE State);		//ステートの設定
	void ChangeNextState();						//ステートの取得
private:
	Character* CreateCharacter(int Num);										//キャラクターの作成(番号で)	
	Character* CreateCharacter(SelectCharacterList::CHARACTER CharacterNum);	//キャラクターの作成(ENUMで)
	void EffectUpdate();
	void EffectDraw();
	void EffectRelease();
public:
	void EffectPause();

private:
	GAMESTATE m_GameState = GAMESTATE::MAX;		//今のステート
	StateContext m_GameSceneStateContext;		//ステートコンテクスト
	std::vector<Character*> m_Characters;		//キャラクターの情報
	Stage* m_pStage;							//ステージの情報
	CameraGame* m_pGameCamera = nullptr;		//ゲームのカメラ
	std::vector<EffectBase*> m_Effects;			//エフェクトの種類
	Image3D m_BackGround;

	GameStartCountUI m_GameStartCountUI;
	GameEndText m_GameEndTextUI;
	StockCountUI m_StockCountUI;

	PlayerController* m_pFirstController = nullptr;
	PlayerController* m_pSecondController = nullptr;

	bool m_isDisConnectController = false;

public:
	StateContext* GetStateContext()		
	{return &m_GameSceneStateContext;}

	std::vector<Character*>& GetCharacter()
	{ return m_Characters;}

	Stage* GetStage()
	{ return m_pStage;}

	std::vector<EffectBase*>* GetEffectVector() 
	{ return &m_Effects; }

};