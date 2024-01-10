#pragma once
#include "Character_Base.h"
#include "Effect_Manager.h"
#include "CharacterStateWindow.h"
#include "Timer.h"

class Character_00 : public Character
{
private:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetDefaultCollider() override;

	//==========================================================================
	void IdleInit() override;		//止まっているときの初期化
	void IdleUninit() override;		//止まっているときの終了処理
	void IdleUpdate() override;		//止まっているときのアップデート
	//==========================================================================
	void WalkInit() override;		//歩く時の初期化
	void WalkUninit() override;		//歩く時の終了処理
	void WalkUpdate() override;		//歩く時のアップデート
	//==========================================================================
	void DashInit() override;		//走るときの初期化
	void DashUninit() override;		//走るときの終了処理
	void DashUpdate() override;		//走るときのアップデート
	//==========================================================================
	void BlowAwayInit() override;	//吹っ飛ばされる時の初期化
	void BlowAwayUninit() override;	//吹っ飛ばしの終了処理
	void BlowAwayUpdate() override;	//吹っ飛ばしのアップデート
	//==========================================================================
	void JumpInInit() override;		//ジャンプ始めの初期化
	void JumpInUpdate() override;	//ジャンプ始めのアップデート
	void JumpInUninit() override;	//ジャンプ始めの終了処理
	//==========================================================================
	void JumpInit() override;		//ジャンプしたときの初期化
	void JumpUninit() override;		//ジャンプしたときの終了処理
	void JumpUpdate() override;		//ジャンプしたときのアップデート
	//==========================================================================
	void AirMoveInit() override;	//空中にいるときの初期化
	void AirMoveUninit() override;	//空中にいるときの終了処理
	void AirMoveUpdate() override;	//落ちているときのアップデート
	//==========================================================================
	void FallDownInit() override;
	void FallDownUninit() override;
	void FallDownUpdate() override;
	//==========================================================================
	void DownInit() override;		//倒れた時の初期化
	void DownUninit() override;		//倒れた時の終了処理
	void DownUpdate() override;		//倒れている状態のアップデート
	//==========================================================================
	void WakeUpInit() override;
	void WakeUpUninit() override;
	void WakeUpUpdate() override;
	//==========================================================================
	void LeanBackInit() override;
	void LeanBackUninit() override;
	void LeanBackUpdate() override;
	//==========================================================================	
	void HitStopInit() override;	//ヒットストップの初期化
	void HitStopUninit() override;	//ヒットストップの終了処理
	void HitStopUpdate() override;	//ヒットストップ状態のアップデート
	//==========================================================================	
	void DeadInit() override;		//死んだときの初期化
	void DeadUninit() override;		//死んだときの終了処理
	void DeadUpdate() override;		//死んだときのアップデート
	//====================================================================
	void RespawnInit() override;	//リスポーンしたときの初期化
	void RespawnUninit() override;	//リスポーンしたときの終了処理
	void RespawnUpdate() override;	//リスポーンしたときのアップデート
	//====================================================================
	void GameOverInit() override;	//リスポーンしたときの初期化
	void GameOverUninit() override;	//リスポーンしたときの終了処理
	void GameOverUpdate() override;	//リスポーンしたときのアップデート
	//====================================================================

	//==========================================================================
	//攻撃のアップデート
	//=====================================================
	void Attack11_Init() override;									//弱1
	void Attack11_Update() override;
	void Attack11_Uninit() override;
	void Attack11_Hit(Character* HitCharacter) override;			
	//=====================================================
	void Attack12_Init() override;									//弱2
	void Attack12_Update() override;
	void Attack12_Uninit() override;
	void Attack12_Hit(Character* HitCharacter) override;
	//=====================================================
	void Attack13_Init() override;									//弱3
	void Attack13_Update() override;
	void Attack13_Uninit() override;
	void Attack13_Hit(Character* HitCharacter) override;
	//=====================================================
	void AttackS2_Init() override;									//横強
	void AttackS2_Update() override;
	void AttackS2_Uninit() override;
	void AttackS2_Hit(Character* HitCharacter) override;
	//=====================================================
	void AttackSD_Init() override;								//横スマッシュ
	void AttackSD_Update() override;
	void AttackSD_Uninit() override;
	void AttackSD_Hit(Character* HitCharacter) override;
	//=====================================================
	void AttackAirN_Init() override;									//空N
	void AttackAirN_Update() override;
	void AttackAirN_Uninit() override;
	void AttackAirN_Hit(Character* HitCharacter) override;		
	//=====================================================


	void HitGround() override;
private:

	int m_FrameCount = 0;					//アタックをしているときに使うカウント
	float m_AnimeTime = 0.0f;				//アニメーションのタイム
	CharacterStateWindow m_stateWindow;		//キャラクターのデバッグウィンドウ
	//unsigned int m_FrameCount = 0;
	int m_HitAttackStopCount = 0;			//ヒットストップのカウント
	bool m_PushButton = false;

	//エフェクトの変数
	Effekseer::Handle m_SwordHandle;
	Effekseer::Handle m_AirNEffect;
};