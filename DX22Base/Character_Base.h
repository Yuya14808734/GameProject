#pragma once
#include "Calculation.h"
#include "Collider.h"
#include "ModelDrawer.h"
#include <vector>

class Attack;

class Character
{
public:
	enum class STATE
	{
		IDLE = 0,	//待機
		WALK,		//歩く
		DASH,		//走る
		ATTACK,		//攻撃
		BLOWOFF,	//吹っ飛ばす

		MAX,
	};

public:
	static void InitPlayerBit();	//下の関数でもらえる番号を初期化する
protected:
	static int GetNewPlayerBit();	//新しいプレイヤーの番号(2進数)を受け取る
									//変なところで呼ぶと番号がずれてしまう
private:
	static int m_NewPlayerBit;		//新しいプレイヤーのビット番号


public:
	void Character_Init();		//キャラクターの初期化
	void Character_Uninit();	//キャラクターの終了処理
	void Character_Update();	//キャラクターの更新
	void Character_Draw();		//キャラクターの描画
	int GetPlayerBit();
	const Character::STATE& GetState() const;
	ModelDrawer* GetModel() const;
	const CVector3& GetPos() const;
	void SetPos(const CVector3& pos);
	const CVector3& GetScale() const;
	void SetScale(const CVector3& scale);
	const CQuaternion& GetRotate() const;
	void SetRotate(const CQuaternion& rotate);
	void SetRotate(const CVector3& rotate);
	void AddForce(const CVector3& force);
	void SetForce(const CVector3& force);
	float GetDamage() const;
	void AddDamage(float damage);
	std::vector<BoxCollider>* GetCollider() const;

protected:

	//======================================================
	//多分操作などがほぼ同じになるため上の関数を使うことになりそう

	virtual void Init();		//継承先の初期化
	virtual void Uninit();		//継承先の終了処理
	virtual void Update();		//継承先の更新
	virtual void Draw();		//継承先の描画


protected:
	//======================================================
	//パラメータ
	const float m_WalkSpeed = 0.0f;			//歩くスピード
	const float m_DashSpeed = 0.0f;			//走るスピード

protected:
	int m_PlayerNum = 0x00;					//このキャラクターが何番なのかを入れる
	Character::STATE m_State = STATE::MAX;	//キャラクターの状態
	ModelDrawer m_CharacterModel;			//キャラクターのモデル
	CVector3 m_pos;							//座標
	CVector3 m_scale;						//大きさ
	CQuaternion m_rotate;					//回転量
	CVector3 m_Velocity;					//重力など
	CVector3 m_MoveVector;					//コントローラーの移動量
	float m_DamagePercentage = 0.0f;		//ダメージの量
	Attack* m_pNowAttack = nullptr;			//攻撃情報
	std::vector<SphereCollider> m_Collider;	//プレイヤーの攻撃用コライダー(ステージとは点で行うので違います)
};