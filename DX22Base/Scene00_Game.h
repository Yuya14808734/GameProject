#pragma once
#include "Scene.h"
#include <vector>
#include "Character_Base.h"
#include "Stage_Base.h"
#include "Camera01_Game.h"
#include "Select01_CharacterList.h"
#include "GameUI00_StartCount.h"


class SceneGame : public CScene
{
private:
	enum class GAMESTATE : int
	{
		GAMESTART = 0,
		GAMEPLAY,
		GAMEEND,
		MAX,
	};

public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	std::vector<Character*>& GetCharacter();
	Stage* GetStage();

private:
	Character* CreateCharacter(int Num);										//キャラクターの作成(番号で)	
	Character* CreateCharacter(SelectCharacterList::CHARACTER CharacterNum);	//キャラクターの作成(ENUMで)

	void UpdateGameStart();														//ゲーム開始時のアップデート
	void UpdateGamePlay();														//ゲーム中のアップデート
	void UpdateGameEnd();														//ゲーム終了時のアップデート
	void DrawGameStart();														//ゲーム開始時のアップデート
	void DrawGamePlay();														//ゲーム中のアップデート
	void DrawGameEnd();															//ゲーム終了時のアップデート

	void Collision_Player_Player();												//当たり判定(プレイヤーとプレイヤー)
	void Collision_Player_Stage();												//当たり判定(プレイヤーとステージ)
	void Collision_Attack_Player();												//当たり判定(プレイヤー攻撃)
	

private:
	GAMESTATE m_GameState = GAMESTATE::MAX;
	std::vector<Character*> m_Characters;	//キャラクターの情報
	Stage* m_pStage;						//ステージの情報
	CameraGame* m_pGameCamera = nullptr;		//ゲームのカメラ

	GameStartCountUI m_GameStartCountUI;
	int m_GameStartFrameCount = 0;

};