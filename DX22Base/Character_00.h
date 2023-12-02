#pragma once
#include "Character_Base.h"

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
	void Attack11_Init() {};
	void Attack11_Update() {};
	void Attack11_Uninit() {};
	//=====================================================
	void Attack12_Init() {};
	void Attack12_Update() {};
	void Attack12_Uninit() {};
	//=====================================================
	void Attack13_Init() {};
	void Attack13_Update() {};
	void Attack13_Uninit() {};
	//=====================================================
	void AttackS2_Init();
	void AttackS2_Update();
	void AttackS2_Uninit();
	//=====================================================
	void AttackS4_Init() {};
	void AttackS4_Update() {};
	void AttackS4_Uninit() {};
	//=====================================================
	void AttackAirN_Init() {};
	void AttackAirN_Update() {};
	void AttackAirN_Uninit() {};
	//=====================================================
	void SpecialN_Init() {};
	void SpecialN_Update() {};
	void SpecialN_Uninit() {};
	//=====================================================
	void SpecialAirN_Init() {};
	void SpecialAirN_Update() {};
	void SpecialAirN_Uninit() {};


	void HitGround() override;
private:

	int m_AttackTime = 0;
	float m_AnimeTime = 0.0f;
};