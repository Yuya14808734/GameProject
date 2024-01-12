#pragma once
#include "Calculation.h"
#include "Collider.h"
#include "ModelDrawer.h"
#include <vector>
#include "Character_DamageUI.h"
#include "XboxKeyboard.h"
#include "Player_Controller.h"
#include "Stage_Base.h"
#include "StatePattern.h"

class Character;
class Character_State;
class Character_AttackState;
class StateContext;
class State;

class Character
{
public:
	enum class LOOKDIR : int
	{
		RIGHT = 0,
		LEFT,
		UP,
		DOWN,
		MAX
	};

	enum class STATE
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
		State_WakeUp,
		State_Walk,
		State_Attack11,
		State_Attack12,
		State_Attack13,
		State_AttackAirN,
		State_AttackDS,
		State_AttackS2,
		State_Max
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

public:
	static void InitPlayerBit();	//下の関数でもらえる番号を初期化する
protected:
	static int GetNewPlayerBit();	//新しいプレイヤーの番号(2進数)を受け取る
									//変なところで呼ぶと番号がずれてしまうのでInit以外で呼ばないように
private:
	static int m_NewPlayerBit;		//新しいプレイヤーのビット番号(キャラクターを数えるために使う)

public:
	Character() {};
	virtual ~Character() {};

	//==========================================================================
	void Character_Init();								//キャラクターの初期化
	void Character_Uninit();							//キャラクターの終了処理
	void Character_Update();							//キャラクターの更新
	void Character_Draw();								//キャラクターの描画
	void Character_UIDraw();							//UIの描画
	//==========================================================================
	int GetCharacterBit();								//キャラクター番号を取得
	virtual State* SetNextState(STATE NextState) = 0;
	void ChangeNextState();
	StateContext* GetStateContext();					//今の状態の取得
	//==========================================================================
	const CVector3& GetPos() const;						//位置の取得
	void SetPos(const CVector3& pos);					//位置の設定
	const CVector3& GetOldPos() const;					//前の座標を取得
	void SetOldPos();									//前の座標を設定
	const CVector3& GetScale() const;					//サイズの取得
	void SetScale(const CVector3& scale);				//サイズの設定
	const CQuaternion& GetRotate() const;				//回転量の取得
	void SetRotate(const CQuaternion& rotate);			//回転量の設定(Quaternion)
	void SetRotate(const CVector3& rotate);				//回転量の設定(度数法)
	void SetLookRight();								//右を向かせる
	void SetLookLeft();									//左を向かせる
	void SetNowLook();									//m_NowLookで見ている方向を見る
	LOOKDIR GetLook();
	//==========================================================================
	void AddForce(const CVector3& force);				//力を足してやる
	void SetForce(const CVector3& force);				//力を設定
	float GetDamage() const;							//ダメージの取得
	void AddDamage(float damage);						//ダメージの加算
	void SetDamage(float damage);						//ダメージの設定
	void SetStock(int stock);
	int GetStock();
	//==========================================================================
	void SetInvincible(bool invincible);				//キャラクターを無敵にするか
	bool IsInvincible();								//キャラクターが無敵か否か
	BoxCollider* GetCharacterCollider() const;			//キャラクター、ステージ当たり判定の取得
	std::vector<Character::ATTACKPARAM>& GetAttackCollider();		//攻撃コライダーの取得
	void Character_ColliderInit();						//地面などに当たっていないことにする
	void Character_HitCeiling();						//天井に当たった	
	void Character_HitGround();							//地面に当たった
	void Character_HitWall();							//壁に当たった
	void DrawCollider();								//コライダーの描画
	//==========================================================================
	void SetCharacterController(PlayerController* pController);
	void SetStage(Stage* pStage);

protected:

	virtual void Init() {};			//継承先の初期化
	virtual void Uninit() {};		//継承先の終了処理
	virtual void Update() {};		//継承先の更新
	virtual void Draw() {};			//継承先の描画

public:

	virtual void SetDefaultCollider() = 0;	//最初の当たり判定に戻す(キャラクターの当たり判定をいじった場合

public:
	//===============================================================================
	// パラメータ一覧
	//===============================================================================

	//-------------------------------------------------------------------------------
	// 横移動に関するパラメータ
	//-------------------------------------------------------------------------------

	MOVEPARAMETER m_MoveParameter;

	void SetMoveParameter(const MOVEPARAMETER& MoveParameter)
	{
		m_MoveParameter = MoveParameter;
	}

	const MOVEPARAMETER& GetMoveParameter()
	{
		return m_MoveParameter;
	}

	//-------------------------------------------------------------------------------
	// ジャンプに関するパラメータ
	//-------------------------------------------------------------------------------

	JUMPPARAMETER m_JumpParameter;

	void SetjumpParameter(const JUMPPARAMETER& JumpParameter)
	{
		m_JumpParameter	= JumpParameter;
	}

	const JUMPPARAMETER& GetJumpParameter()
	{
		return m_JumpParameter;
	}

	//-------------------------------------------------------------------------------
	// 吹っ飛ばされた時に関するパラメータ
	//-------------------------------------------------------------------------------
	
	BLOWAWAYPARAMETER m_BlowAwayParameter;

	void SetBlowAwayParameter(const BLOWAWAYPARAMETER& BlowAwayParameter)
	{
		m_BlowAwayParameter = BlowAwayParameter;
	}

	const BLOWAWAYPARAMETER& GetBlowAwayParameter()
	{
		return m_BlowAwayParameter;
	}

protected:
	//===============================================================================
	// 変数一覧
	//===============================================================================
	int		m_PlayerBit = 0x00;						//このキャラクターが何番なのかを入れる
	PlayerController* m_Controller = nullptr;		//キャラクターのコントローラー

	//===============================================================================
	// 位置などをまとめた変数
	//===============================================================================
	CHARACTER_PARAMETER m_Parameter;

	//-------------------------------------------------------------------------------
	// プレイヤーステートに関する変数
	//-------------------------------------------------------------------------------
	StateContext m_CharacterStateContext;

	Character::LOOKDIR	m_NowLookDir		= LOOKDIR::MAX;	//プレイヤーが見ている方向
	
	//-------------------------------------------------------------------------------
	// モデル描画に関する変数
	//-------------------------------------------------------------------------------
	ModelDrawer		m_CharacterModel;				//キャラクターのモデル
	
	//-------------------------------------------------------------------------------
	// キャラクターの状態に関する変数
	//-------------------------------------------------------------------------------
	int		m_CharacterStock		= 0;		//ストック
	float	m_DamagePercentage		= 0.0f;		//ダメージの量

	//-------------------------------------------------------------------------------
	// 当たり判定に関する変数
	//-------------------------------------------------------------------------------
	bool						m_Invincible			= false;	//無敵か否か
	BoxCollider					m_CharacterCollider;				//プレイヤーの当たり判定
	std::vector<ATTACKPARAM>	m_AttackCollider;					//攻撃したときの当たり判定

	//-------------------------------------------------------------------------------
	//ステージに当たった判定に使う変数
	//-------------------------------------------------------------------------------
	Character_DamageUI m_DamageUI;

	//-------------------------------------------------------------------------------
	// 外部のオブジェクトを保持する変数
	//-------------------------------------------------------------------------------
	Stage*			m_pStage = nullptr;				//ステージの情報が入る
};

class Character_State : public State
{
public:
	enum class TYPE
	{
		DEFAULT = 0,
		ATTACK,
		MAX
	};

public:
	Character_State(TYPE type) : m_StateType(type) {};
	Character_State() : Character_State(Character_State::TYPE::DEFAULT) {};
	virtual ~Character_State() {};

	Character_State::TYPE GetType();
	void SetCharacter(Character* pCharacter);
	void SetController(PlayerController* pController);
	void SetCharacterParameter(Character::CHARACTER_PARAMETER* pCharacterParameter);
	void SetStage(Stage* pStage);
	void SetModelDrawer(ModelDrawer* pModelDrawer);
	void SetCharacterCollider(BoxCollider* pCollider);
	void SetAttackCollider(std::vector<Character::ATTACKPARAM>* pAttackCollider);
	void SetMoveParameter(Character::MOVEPARAMETER* pMoveParameter);
	void SetJumpParameter(Character::JUMPPARAMETER* pJumpParameter);
	void SetBlowAwayParameter(Character::BLOWAWAYPARAMETER* pBlowAwayParameter);

public:
	virtual void Init() {};
	virtual void Uninit() {};
	virtual void Update() {};

private:
	Character_State::TYPE m_StateType = Character_State::TYPE::MAX;

protected:
	Character* m_pCharacter = nullptr;
	PlayerController* m_pController = nullptr;
	Character::CHARACTER_PARAMETER* m_pCharacterParameter = nullptr;
	Stage* m_pStage = nullptr;
	ModelDrawer* m_pModelDrawer = nullptr;
	BoxCollider* m_pCharacterCollider = nullptr;
	std::vector<Character::ATTACKPARAM>* m_pAttackCollider = nullptr;
	Character::MOVEPARAMETER* m_pMoveParameter = nullptr;
	Character::JUMPPARAMETER* m_pJumpParameter = nullptr;
	Character::BLOWAWAYPARAMETER* m_pBlowAwayParameter = nullptr;
};

//==========================================================================
//スマブラと同じような名前にしています
//https://www.youtube.com/watch?v=V40sMUAE5ek
//==========================================================================

class Character_AttackState : public Character_State
{
public:
	Character_AttackState() :Character_State(Character_State::TYPE::ATTACK) {};
	virtual ~Character_AttackState() {};
	virtual void HitCharacter(Character* pHitCharacter) {};

protected:
	virtual void Init() override {};
	virtual void Uninit() override {};
	virtual void Update() override {};
};