#pragma once
#include "Character_Base.h"
#include "Effect_Manager.h"

class Character_00 : public Character
{
private:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;


	void IdleInit() override;
	void IdleUpdate() override;

	void WalkInit() override;
	void WalkUpdate() override;

	void DashInit() override;
	void DashUpdate() override;

	void JumpInInit() override;
	void JumpInUpdate() override;

	void JumpInit() override;
	void JumpUpdate() override;

	void AirMoveInit() override;
	void AirMoveUpdate() override;


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

	int m_AttackTime = 0;
	float m_AnimeTime = 0.0f;


	//エフェクトの変数
	Effekseer::Handle m_SwordHandle;
	Effekseer::Handle m_AirNEffect;
};