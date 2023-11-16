#pragma once

#include "Character_Base.h"
#include "ModelDrawer.h"
#include "Collider.h"
#include <vector>

//======================================================
//class Attack
//攻撃をまとめるクラス
//攻撃初めから最後までの以下の事を管理する
//・当たったプレイヤー
//・当たり判定
//・モデルのアニメーション
//・キャラクターの移動

class Attack
{
public:
	Attack() {};
	~Attack() {};

	void Attack_Init();
	void Attack_Uninit();
	void Attack_Update();
	void Attack_Draw();

	void SetCharacter(Character* character);			//キャラクターの設定

protected:

	virtual void Init() {};
	virtual void Uninit() {};
	virtual void Update() {};
	virtual void Draw() {};

protected:
	const int AttackEndFrame = 0;				//攻撃から違うステートに変更するフレーム

private:
	Character* m_pMyCharacter = nullptr;		//攻撃をしているキャラクター
	ModelDrawer* m_pCharacterModel = nullptr;	//キャラクターのモデル情報
	int m_FrameCount = 0;						//攻撃が始まってからのフレーム
	int m_HitPlayerBit = 0x00;					//当たったプレイヤー番号
	Character::STATE m_CharacterNextState;		//攻撃終了した後のキャラクターの状態
	std::vector<SphereCollider> m_AttackCollider;	//攻撃のコライダー(一応複数の当たり判定を持てるように)
													//飛び道具などはアイテムなどを作ってそこで当たり判定を行う
};