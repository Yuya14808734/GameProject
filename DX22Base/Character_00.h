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


	//UÌAbvf[g
	//=====================================================
	void Attack11_Init() {};								//ã1
	void Attack11_Update() {};
	void Attack11_Uninit() {};
	void Attack11_Hit(Character* HitCharacter) {};			
	//=====================================================
	void Attack12_Init() {};								//ã2
	void Attack12_Update() {};
	void Attack12_Uninit() {};
	void Attack12_Hit(Character* HitCharacter) {};			
	//=====================================================
	void Attack13_Init() {};								//ã3
	void Attack13_Update() {};
	void Attack13_Uninit() {};
	void Attack13_Hit(Character* HitCharacter) {};			
	//=====================================================
	void AttackS2_Init();									//¡­
	void AttackS2_Update();
	void AttackS2_Uninit();
	void AttackS2_Hit(Character* HitCharacter);			
	//=====================================================
	void AttackS4_Init() {};								//¡X}bV
	void AttackS4_Update() {};
	void AttackS4_Uninit() {};
	void AttackS4_Hit(Character* HitCharacter) {};			
	//=====================================================
	void AttackAirN_Init() {};								//óN
	void AttackAirN_Update() {};
	void AttackAirN_Uninit() {};
	void AttackAirN_Hit(Character* HitCharacter) {};		
	//=====================================================
	void SpecialN_Init() {};								//ÊíKEZ
	void SpecialN_Update() {};
	void SpecialN_Uninit() {};
	void SpecialN_Hit(Character* HitCharacter) {};			
	//=====================================================
	void SpecialAirN_Init() {};								//ÊíKEZ(ó)
	void SpecialAirN_Update() {};
	void SpecialAirN_Uninit() {};
	void SpecialAirN_Hit(Character* HitCharacter) {};		


	void HitGround() override;
private:

	int m_AttackTime = 0;
	float m_AnimeTime = 0.0f;


	//GtFNgÌÏ
	Effekseer::Handle m_SwordHandle;
};