#pragma once

#include "Character_Base.h"
#include "ModelDrawer.h"

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

protected:
	const int AttackColliderStartFrame = 0;				//攻撃当たり判定の計測開始フレーム
	const int AttackColliderEndFrame = 0;				//攻撃当たり判定の計測終了フレーム
	const int AttackEndFrame = 0;						//攻撃から違うステートに変更するフレーム

private:
	Character* m_pMyCharacter = nullptr;		//攻撃をしているキャラクター
	ModelDrawer* m_pCharacterModel = nullptr;	//キャラクターのモデル情報
	int m_FrameCount = 0;						//攻撃が始まってからのフレーム
	int m_HitPlayerBit = 0x00;					//当たったプレイヤー番号
	Character::STATE m_CharacterNextState;		//攻撃終了した後のキャラクターの状態

};