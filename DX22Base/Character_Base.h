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
		JUMP,		//ジャンプ
		FALL,		//落下
		DOWN,		//倒れる

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
	Character() {};
	~Character() {};
	void Character_Init();								//キャラクターの初期化
	void Character_Uninit();							//キャラクターの終了処理
	void Character_Update();							//キャラクターの更新
	void Character_Draw();								//キャラクターの描画
	int GetPlayerBit();									//キャラクター番号の取得
	const Character::STATE& GetState() const;			//今の状態の取得
	ModelDrawer* GetModel() const;						//モデル情報の取得
	const CVector3& GetPos() const;						//位置の取得
	void SetPos(const CVector3& pos);					//位置の設定
	const CVector3& GetOldPos() const;					//前の座標を取得
	void SetOldPos();									//前の座標を設定
	const CVector3& GetScale() const;					//サイズの取得
	void SetScale(const CVector3& scale);				//サイズの設定
	const CQuaternion& GetRotate() const;				//回転量の取得
	void SetRotate(const CQuaternion& rotate);			//回転量の設定(Quaternion)
	void SetRotate(const CVector3& rotate);				//回転量の設定(度数法)
	void AddForce(const CVector3& force);				//力を足してやる
	void SetForce(const CVector3& force);				//力を設定
	float GetDamage() const;							//ダメージの取得
	void AddDamage(float damage);						//ダメージの加算
	void SetDamage(float damage);						//ダメージの設定
	BoxCollider* GetCharacterCollider() const;			//キャラクター、ステージ当たり判定の取得
	void Character_HitGround();							//地面に当たった時
	void DrawCollider();								//コライダーの描画

protected:

	/*引数(歩くスピード, 走るスピード, 落ちているときの横に動くスピード, 
	ジャンプできる回数, ジャンプする力, 重力, 落ちる速さ, 摩擦量, 空気抵抗)*/
	void SetParameter(
	float WalkSpeed,float DashSpeed,float  FallSideMoveSpeed,
		int MaxJumpCount,float JumpPower,float GravityScale,
		float MaxFallSpeed,float Friction,	float AirResistance);
	void SetAttack(Attack* pAttack);

protected:

	//======================================================
	//多分操作などがほぼ同じになるため上の関数を使うことになりそう

	virtual void Init() {};			//継承先の初期化
	virtual void Uninit() {};		//継承先の終了処理
	virtual void Update() {};		//継承先の更新
	virtual void Draw() {};			//継承先の描画

	virtual void IdleUpdate();		//止まっているときのアップデート
	virtual void WalkUpdate();		//歩く時のアップデート
	virtual void DashUpdate();		//走るときのアップデート
	virtual void AttackUpdate();	//攻撃のアップデート
	virtual void BlowOffUpdate();	//吹っ飛ばしのアップデート
	virtual void JumpUpdate();		//浮かんでいるときのアップデート
	virtual void FallUpdate();		//落ちているときのアップデート
	virtual void DownUpdate();		//倒れている状態のアップデート
	
	virtual void HitGround();		//地面に当たった時に呼ばれる

protected:
	//攻撃の基底関数
	//virtual void 


private:
	//======================================================
	//最初に設定するパラメータ
	int		m_PlayerBit = 0x00;				//このキャラクターが何番なのかを入れる
	float	m_WalkSpeed			= 0.0f;		//歩くスピード
	float	m_DashSpeed			= 0.0f;		//走るスピード
	float	m_FallSideMoveSpeed = 0.0f;		//落ちているときの横移動のスピード
	int		m_MaxJumpCount		= 0;		//ジャンプできる最大数
	float	m_JumpPower			= 0.0f;		//ジャンプするときの力
	float	m_Gravity			= 0.0f;		//重力
	float	m_MaxFallSpeed		= 0.0f;		//最大落下速度
	float	m_Friction			= 0.0f;		//摩擦量
	float	m_AirResistance		= 0.0f;		//空気抵抗

protected:
	Character::STATE m_State = STATE::MAX;	//キャラクターの状態
	ModelDrawer m_CharacterModel;			//キャラクターのモデル
	CVector3 m_pos;							//座標
	CVector3 m_oldPos;						//前の座標
	CVector3 m_scale;						//大きさ
	CQuaternion m_rotate;					//回転量
	CVector3 m_Velocity;					//重力など
	CVector3 m_MoveVector;					//コントローラーの移動量
	float m_DamagePercentage = 0.0f;		//ダメージの量
	Attack* m_pNowAttack = nullptr;			//攻撃情報
	BoxCollider m_CharacterCollider;		//プレイヤーの当たり判定
	int m_JumpCount = 0;
};