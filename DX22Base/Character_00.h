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
	//void AttackInit() override;		//攻撃するときの初期化
	//void AttackUninit() override;	//攻撃するときの終了処理
	//void AttackUpdate() override;	//攻撃するときのアップデート
	//==========================================================================
	void BlowAwayInit() override;		//吹っ飛ばされる時の初期化
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
	//攻撃のアップデート
	//=====================================================
	void Attack11_Init();								//弱1
	void Attack11_Update();
	void Attack11_Uninit();
	void Attack11_Hit(Character* HitCharacter);			
	//=====================================================
	void Attack12_Init();								//弱2
	void Attack12_Update();
	void Attack12_Uninit();
	void Attack12_Hit(Character* HitCharacter);			
	//=====================================================
	void Attack13_Init();								//弱3
	void Attack13_Update();
	void Attack13_Uninit();
	void Attack13_Hit(Character* HitCharacter);			
	//=====================================================
	void AttackS2_Init();									//横強
	void AttackS2_Update();
	void AttackS2_Uninit();
	void AttackS2_Hit(Character* HitCharacter);			
	//=====================================================
	void AttackS4_Init() {};								//横スマッシュ
	void AttackS4_Update() {};
	void AttackS4_Uninit() {};
	void AttackS4_Hit(Character* HitCharacter) {};
	//=====================================================
	void AttackAirN_Init();								//空N
	void AttackAirN_Update();
	void AttackAirN_Uninit();
	void AttackAirN_Hit(Character* HitCharacter);		
	//=====================================================
	void SpecialN_Init() {};								//通常必殺技
	void SpecialN_Update() {};
	void SpecialN_Uninit() {};
	void SpecialN_Hit(Character* HitCharacter) {};
	//=====================================================
	void SpecialAirN_Init() {};								//通常必殺技(空中)
	void SpecialAirN_Update() {};
	void SpecialAirN_Uninit() {};
	void SpecialAirN_Hit(Character* HitCharacter) {};		


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