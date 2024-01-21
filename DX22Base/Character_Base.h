#pragma once
#include "Calculation.h"
#include "Collider.h"
#include "ModelDrawer.h"
#include <vector>
#include "GameUI03_CharacterDamageUI.h"
#include "XboxKeyboard.h"
#include "Player_Controller.h"
#include "Stage_Base.h"
#include "StatePattern.h"

class Character;
class Character_State;
class Character_Attack;

class Character
{
public:
	enum class LOOKDIR : int
	{
		RIGHT = 0,
		LEFT,
		UP,
		DOWN,
		FRONT,
		BACK,
		MAX,
	};

	enum class STATE : int
	{
		State_None = 0,
		State_AirMove,
		State_BlowAway,
		State_Dash,
		State_Dead,
		State_Down,
		State_FallDown,
		State_GameOver,
		State_HitStop,
		State_Idle,
		State_JumpIn,
		State_Jump,
		State_LeanBack,
		State_Respawn,
		State_StartAnime,
		State_WakeUp,
		State_Walk,
		State_Attack11,
		State_Attack12,
		State_Attack13,
		State_AttackAirN,
		State_AttackDS,
		State_AttackS2,
		State_Max,
	};

	struct ATTACKPARAM
	{
		bool m_Use = false;									//この攻撃の当たり判定を行うか
		BoxCollider m_BoxCollider;							//攻撃の当たり判定
		unsigned int m_HitCharacterBit = 0x00;				//前のフレームで当たったキャラクターのビット番号が入る
		unsigned int m_CanAttackCharacterBit = 0x00;		//当たることが出来るキャラクターのビット番号
		unsigned int m_haveHitCharacterBit = 0x00;			//今までで当たったことがあるキャラクタービット番号
		unsigned int m_HitTriggerCharacterBit = 0x00;		//前のフレームで初めて当たった事があるキャラクターのビット番号
	};

	struct CHARACTER_PARAMETER
	{
		//-------------------------------------------------------------------------------
		// 座標に関する変数
		//-------------------------------------------------------------------------------
		CVector3		Pos;						//座標
		CVector3		AddDrawPos;					//描画するときにずらす座標
		CVector3		OldPos;						//前の座標
		CVector3		Scale;						//大きさ
		CQuaternion		Rotate;						//回転量
		CVector3		Velocity;					//重力など
		CVector3		MoveVector;					//コントローラーの移動量
		CVector3		ShiftCenterPos;				//回転や拡縮をする中心位置をずらす

		//-------------------------------------------------------------------------------
		// ジャンプに関する変数
		//-------------------------------------------------------------------------------
		int				JumpCount = 0;				//今ジャンプした回数
		int				JumpCharageCount = 0;		//ジャンプをチャージする時のカウント

		//-------------------------------------------------------------------------------
		//ステージに当たったか
		//-------------------------------------------------------------------------------
		bool			HitGround = false;			//前のフレームで地面に当たったか
		bool			HitCeiling = false;			//前のフレームで天井に当たったか
		bool			HitWall = false;				//前のフレームで壁に当たったか
	};

	struct MOVEPARAMETER
	{
		float	WalkSpeed = 0.0f;		//歩くスピード
		float	DashSpeed = 0.0f;		//走るスピード
		float	AirSideMoveSpeed = 0.0f;		//落ちているときの横移動のスピード
		float	Friction = 0.0f;		//摩擦量
		float	AirDrag = 0.0f;		//空気抵抗
	};

	struct JUMPPARAMETER
	{
		int		MaxJumpCount = 0;				//ジャンプできる最大数
		int		MiniJumpPushButtonCount = 0;	//小ジャンプするときのフレーム
		int		JumpChargeCount = 0;			//ジャンプするまでのチャージ時間
		float	FirstMiniJumpPower = 0.0f;	//小ジャンプをするときの力
		float	FirstJumpPower = 0.0f;		//ジャンプするときの力
		float	SecondJumpPower = 0.0f;		//二回目のジャンプの力
		float	JumpUpReduction = 0.0f;		//ジャンプして上に上がるときの重力
		float	FallDownGravity = 0.0f;		//ジャンプし終わって下に下がるときの重力
		float	DefaultFallSpeed = 0.0f;		//最大落下速度
		float	SpeedUpFallSpeed = 0.0f;		//落下中に下を押した場合の落下量
		float	ChangeFallSpeed = 0.0f;		//落下に変わるときのスピード
	};

	struct BLOWAWAYPARAMETER
	{
		float SmashMitigation = 0.0f;			//吹っ飛ばされた時にどれくらい弱くしていくか
		float VectorChangePower = 0.0f;		//吹っ飛ばされた時にベクトル変更する割合
		float MinimumSmashLength = 0.0f;		//吹っ飛んでいると判定する最低距離速度
	};


	//===============================================================================
	//static関数・変数
	//===============================================================================
public:
	static void InitPlayerBit();	//下の関数でもらえる番号を初期化する
protected:
	static int GetNewPlayerBit();	//新しいプレイヤーの番号(2進数)を受け取る
									//変なところで呼ぶと番号がずれてしまうのでInit以外で呼ばないように
private:
	static int m_NewPlayerBit;		//新しいプレイヤーのビット番号(キャラクターを数えるために使う)

	//===============================================================================
	//関数
	//===============================================================================
public:
	Character() {};
	virtual ~Character() {};

	void Character_Init();								//キャラクターの初期化
	void Character_Uninit();							//キャラクターの終了処理
	void Character_Update();							//キャラクターの更新
	void Character_Draw();								//キャラクターの描画
	void Character_UIDraw();							//UIの描画
	void DrawCollider();								//コライダーの描画
	void ChangeNextState();								//次のステートへ変更
	void CheckDeadLineOver();								//ゲームオーバーをしているか確認

	//===============================================================================
	//継承先で実装する関数
	//===============================================================================
protected:
	virtual void Init() {};			//継承先の初期化
	virtual void Uninit() {};		//継承先の終了処理
	virtual void Update() {};		//継承先の更新
	virtual void Draw() {};			//継承先の描画

public:
	//===============================================================================
	//純粋仮想関数
	//===============================================================================
	virtual State* SetNextState(STATE NextState) = 0;
	virtual void SetDefaultCollider() = 0;	//最初の当たり判定に戻す(キャラクターの当たり判定をいじった場合

	
protected:
	//===============================================================================
	//変数一覧
	//===============================================================================
	int						 m_PlayerBit = 0x00;			//このキャラクターが何番なのかを入れる
	PlayerController*		 m_Controller = nullptr;		//キャラクターのコントローラー
	CHARACTER_PARAMETER		 m_Parameter;					//キャラクターの位置などの変数をまとめた変数
	StateContext			 m_CharacterStateContext;		//ステートコンテクスト
	Character::LOOKDIR		 m_NowLookDir = LOOKDIR::MAX;	//プレイヤーが見ている方向
	ModelDrawer				 m_CharacterModel;				//キャラクターのモデル
	int						 m_CharacterStock = 0;			//ストック
	float					 m_DamagePercentage = 0.0f;		//ダメージの量
	bool					 m_Invincible = false;			//無敵か否か
	bool					 m_GameOver = false;			//ゲームオーバーしているか
	bool					 m_IsCheckDead = false;			//死ぬ判定を連続でしないようにする
	BoxCollider				 m_CharacterCollider;			//プレイヤーの当たり判定
	std::vector<ATTACKPARAM> m_AttackCollider;				//攻撃したときの当たり判定
	Character_DamageUI		 m_DamageUI;					//ダメージUI
	MOVEPARAMETER			 m_MoveParameter;				//歩く速さなどの動きのパラメータ
	JUMPPARAMETER			 m_JumpParameter;				//ジャンプ力などのパラメータ
	BLOWAWAYPARAMETER		 m_BlowAwayParameter;			//吹っ飛ばし力などのパラメータ
	Stage*					 m_pStage = nullptr;			//ステージの情報が入る

public:
	//===============================================================================
	// Set、Get関数(ここから下は全部)
	//===============================================================================
	
	int GetCharacterBit()										//キャラクター番号を取得
	{ return m_PlayerBit; }

	//------------------------------------------------------------------------------
	StateContext* GetStateContext()								//ステートコンテクストを取得
	{ return &m_CharacterStateContext; }

	//------------------------------------------------------------------------------
	const CVector3& GetPos() const								//位置の取得
	{ return m_Parameter.Pos; }

	//------------------------------------------------------------------------------
	void SetPos(const CVector3& pos)							//位置の設定
	{ m_Parameter.Pos = pos;
		m_CharacterCollider.SetBasePos(pos); }
	
	//------------------------------------------------------------------------------
	const CVector3& GetOldPos() const							//前の座標を取得
	{ return m_Parameter.OldPos; }

	//------------------------------------------------------------------------------
	void SetOldPos()											//前の座標を設定
	{ m_Parameter.OldPos = m_Parameter.Pos; }

	//------------------------------------------------------------------------------
	const CVector3& GetScale() const							//スケールの取得
	{ return m_Parameter.Scale; }

	//------------------------------------------------------------------------------
	void SetScale(const CVector3& scale)						//スケールの設定
	{ m_Parameter.Scale = scale; }

	//------------------------------------------------------------------------------
	const CQuaternion& GetRotate() const						//回転の取得
	{ return m_Parameter.Rotate; }

	//------------------------------------------------------------------------------
	void SetRotate(const CQuaternion& rotate)					//回転の設定(クォータニオン)
	{ m_Parameter.Rotate = rotate; }

	//------------------------------------------------------------------------------
	void SetRotate(const CVector3& rotate)						//回転の設定(度数法)
	{ m_Parameter.Rotate.SetQuaternion(
			DirectX::XMConvertToRadians(rotate.x),
			DirectX::XMConvertToRadians(rotate.y),
			DirectX::XMConvertToRadians(rotate.z)); }

	//------------------------------------------------------------------------------
	void SetLookRight() 										//右を向かせる
	{ m_NowLookDir = Character::LOOKDIR::RIGHT;
		m_Parameter.Rotate =
			CQuaternion::AngleAxis(CVector3::GetUp(), 90.0f); }

	//------------------------------------------------------------------------------
	void SetLookLeft()											//左を向かせる
	{ m_NowLookDir = Character::LOOKDIR::LEFT;
		m_Parameter.Rotate =
			CQuaternion::AngleAxis(CVector3::GetUp(), -90.0f); }

	//------------------------------------------------------------------------------
	void SetLookFront()											//前を向かせる
	{
		m_NowLookDir = Character::LOOKDIR::FRONT;
		m_Parameter.Rotate =
			CQuaternion::AngleAxis(CVector3::GetUp(), 180.0f);}

	//------------------------------------------------------------------------------
	void SetLookBack()											//後ろを向かせる
	{
		m_NowLookDir = Character::LOOKDIR::BACK;
		m_Parameter.Rotate =
			CQuaternion::AngleAxis(CVector3::GetUp(), 0.0f);
	}

	//------------------------------------------------------------------------------
	void SetNowLook() 											//今設定している方向へ向かせる
	{ switch (m_NowLookDir) {
		case Character::LOOKDIR::LEFT:
			SetLookLeft();
			break;
		case Character::LOOKDIR::RIGHT:
			SetLookRight();
			break;
		}}

	//------------------------------------------------------------------------------
	LOOKDIR GetLook()											//今向いている方を取得
	{ return m_NowLookDir; };

	//------------------------------------------------------------------------------
	void AddForce(const CVector3& force)						//重力などを足してやる
	{ m_Parameter.Velocity += force; }

	//------------------------------------------------------------------------------
	void SetForce(const CVector3& force)						//重力を設定してやる
	{ m_Parameter.Velocity = force; }
		
	//------------------------------------------------------------------------------
	float GetDamage() const										//ダメージを取得
	{ return m_DamagePercentage; }
	
	//------------------------------------------------------------------------------
	void AddDamage(float damage)								//ダメージを加算
	{ m_DamagePercentage += damage; }

	//------------------------------------------------------------------------------
	void SetDamage(float damage)								//ダメージを設定
	{ m_DamagePercentage = damage; }

	//------------------------------------------------------------------------------
	void SetStock(int stock) 									//ストックを設定
	{ m_CharacterStock = stock;
		m_DamageUI.SetStockNum(stock); }
	
	//------------------------------------------------------------------------------
	int GetStock()												//ストックを取得
	{ return m_CharacterStock; }

	//------------------------------------------------------------------------------
	void SetInvincible(bool invincible)							//無敵か否かを設定
	{ m_Invincible = invincible; }
	
	//------------------------------------------------------------------------------
	bool IsInvincible()											//無敵か否か取得
	{ return m_Invincible; }

	//------------------------------------------------------------------------------
	void SetGameOver(bool GameOver)								//ゲームオーバーを設定
	{ m_GameOver = GameOver; }
	
	//------------------------------------------------------------------------------
	bool GetGameOver()											//ゲームオーバーを取得
	{ return m_GameOver; }

	//------------------------------------------------------------------------------
	void SetCheckDead(bool dead)								//死んだ判定をするか
	{ m_IsCheckDead = dead; }
	//------------------------------------------------------------------------------
	bool IsCheckDead()											//死んだ判定をするか取得
	{ return m_GameOver; }

	//------------------------------------------------------------------------------
	BoxCollider* GetCharacterCollider() const					//キャラクターの当たり判定を取得
	{ return const_cast<BoxCollider*>(&m_CharacterCollider); }

	//------------------------------------------------------------------------------
	std::vector<Character::ATTACKPARAM>& GetAttackCollider()	//攻撃の当たり判定を取得
	{ return m_AttackCollider; }

	//------------------------------------------------------------------------------
	void Character_ColliderInit() 								//ステージとの当たり判定で使う変数を初期化
	{ m_Parameter.HitCeiling =
			m_Parameter.HitGround =
			m_Parameter.HitWall = false; }

	//------------------------------------------------------------------------------
	void Character_HitCeiling()									//天井に当たったことを設定
	{
		m_Parameter.Velocity.y = 0.0f;
		m_Parameter.HitCeiling = true;	}

	//------------------------------------------------------------------------------
	bool GetHitCeling()											//前のフレームで天井に当たったか取得
	{ return m_Parameter.HitCeiling; }

	//------------------------------------------------------------------------------
	void Character_HitGround() 									//地面に当たった時の処理
	{ m_Parameter.Velocity.y = 0.0f;
		m_Parameter.JumpCount = 0;
		m_Parameter.HitGround = true; }

	//------------------------------------------------------------------------------
	bool GetHitGround()											//前のフレームで地面に当たったか取得
	{ return m_Parameter.HitGround; }
	
	//------------------------------------------------------------------------------
	void Character_HitWall()									//壁に当たった事を設定
	{ m_Parameter.HitWall = true; }

	//------------------------------------------------------------------------------
	bool GetHitWall()											//前のフレームで壁に当たったか取得
	{ return m_Parameter.HitWall; }

	//------------------------------------------------------------------------------
	void SetCharacterController(PlayerController* pController); 	//コントローラーを設定
	/*Cppに実装しています*/

	//------------------------------------------------------------------------------
	void SetStage(Stage* pStage);								//ステージを設定
	/*Cppに実装しています*/

	//------------------------------------------------------------------------------
	void SetMoveParameter(const MOVEPARAMETER& MoveParameter)	//動きに関するパラメータを設定
	{ m_MoveParameter = MoveParameter; }

	//------------------------------------------------------------------------------
	const MOVEPARAMETER& GetMoveParameter()						//動きに関するパラメータを取得
	{ return m_MoveParameter; }

	//------------------------------------------------------------------------------
	void SetjumpParameter(const JUMPPARAMETER& JumpParameter)	//ジャンプに関するパラメータを設定
	{ m_JumpParameter = JumpParameter; }

	//------------------------------------------------------------------------------
	const JUMPPARAMETER& GetJumpParameter()						//ジャンプに関するパラメータを取得
	{ return m_JumpParameter; }

	//------------------------------------------------------------------------------
	void SetBlowAwayParameter(const BLOWAWAYPARAMETER& BlowAwayParameter)	//吹っ飛ばしに関するパラメータを設定
	{ m_BlowAwayParameter = BlowAwayParameter; }

	//------------------------------------------------------------------------------
	const BLOWAWAYPARAMETER& GetBlowAwayParameter()							//吹っ飛ばしに関するパラメータを取得
	{ return m_BlowAwayParameter; }
};