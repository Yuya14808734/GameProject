#pragma once
#include "Calculation.h"
#include "XboxKeyboard.h"
#include "Input.h"
#include <array>

//=========================================================
//コントローラーの情報を持たせる
//=========================================================

//目的：コントローラーが接続されたらキーボードだろうがパッドだろうが両方同じこのクラスで
//		処理をする(決定ボタンを押す時にキーボードならEnter、パッドならBを押した時にTrueなど)
//		これにより違うコントローラーでも外から見たら同じように見ることができる

class PlayerController
{
public:
	enum class PLAYCONTROLLERTYPE : int
	{
		GAMEPAD = 0,	//コントローラー
		KEYBOARD,		//キーボード
		MAX,
	};

public:
	static void PlayerController_Init();
	static void PlayerController_Update();
	static std::array<PlayerController, 5>& GetPlayerControllers();
	static void InitXPadNum();

private:
	static std::array<PlayerController,5> m_PlayerControllers;				//接続されたコントローラーたち
	static int m_XPadNum;											//つないであるコントローラーを数えるための変数

public:
	//===============================================================
	// コンストラクタ・デストラクタ
	//===============================================================
	PlayerController() {};
	~PlayerController() {};

	//===============================================================
	// コントローラーの更新
	//===============================================================
	void Update();						//コントローラーの情報を更新(Trigger情報)
	void UnTriggerNowFrame();			//このフレームでTrigger判定できないようにする

	//===============================================================
	// コントローラーの設定
	//===============================================================
	void SetController(PLAYCONTROLLERTYPE type, int PlayerNum);

	//===============================================================
	// コントローラーの取得
	//===============================================================
	int GetPlayerNum();
	bool IsConnect();
	InputXPad* GetController();				//コントローラーがつないでいない場合nullptrが帰ってきます。
	PLAYCONTROLLERTYPE GetControllerType();	//コントローラーのタイプを取得

	//===============================================================
	//入力に関する関数
	//===============================================================
	bool IsPushAnyBotton();					//なんか作れない
	bool IsPressReturn();
	bool IsTriggerReturn();
	bool IsPressBack();
	bool IsTriggerBack();
	bool GetPressRightArrow();
	bool GetTriggerRightArrow();
	bool GetPressUpArrow();
	bool GetTriggerUpArrow();
	bool GetPressDownArrow();
	bool GetTriggerDownArrow();
	bool GetPressLeftArrow();
	bool GetTriggerLeftArrow();
	const CVector2& GetMoveInput();
	bool GetLeftSmash();
	bool GetJumpTrigger();
	bool GetJumpPress();
	bool GetAttack();
	const CVector2& GetLeftInputVector();
	bool GetWakeUp();

private:
	PLAYCONTROLLERTYPE m_ControllerType = PLAYCONTROLLERTYPE::MAX;	//コントローラーの種類
	InputXPad* m_pXPad = nullptr;									//ゲームパッドがある場合、パッドの情報が入ります。
	int m_PlayerNum = 0;											//このコントローラーを使うキャラクター番号(0～)


private:
	enum class TRIGGERBIT : unsigned int
	{
		NONE		= 0x00000000,
		ALL			= 0xffffffff,
		RIGHTARROW	= 0x00000001,
		LEFTARROW	= 0x00000002,
		UPARROW		= 0x00000004,
		DOWNARROW	= 0x00000008,
		RETURN		= 0x00000010,
		BACK		= 0x00000020,
	};

private:
	bool GetBitTrigger(TRIGGERBIT Bit);

	int m_NowTriggerBit = 0x00;
	int m_OldTriggerBit = 0x00;
};