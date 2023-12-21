#pragma once
#include "Calculation.h"
#include "XboxKeyboard.h"
#include "Input.h"

//=========================================================
// キャラクターを動かすコントローラーの情報を持たせる
//=========================================================

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
	static void InitXPadNum();
private:
	static int m_XPadNum;		//つないであるコントローラーを数えるための変数

public:
	//===============================================================
	// コントローラーの設定
	//===============================================================
	void SetController(PLAYCONTROLLERTYPE type, int PlayerNum);

	//===============================================================
	// コントローラーの取得
	//===============================================================
	InputXPad* GetController();	//コントローラーがつないでいない場合nullptrが帰ってきます。
	PLAYCONTROLLERTYPE GetControllerType();	//コントローラーのタイプを取得

	//===============================================================
	// キャラクターの入力に関する関数
	//===============================================================
	const CVector2& GetMoveInput();
	bool GetLeftSmash();
	bool GetJumpTrigger();
	bool GetJumpPress();
	bool GetAttack();
	const CVector2& GetLeftInputVector();

private:
	PLAYCONTROLLERTYPE m_ControllerType = PLAYCONTROLLERTYPE::MAX;	//コントローラーの種類
	InputXPad* m_pXPad = nullptr;									//ゲームパッドがある場合、パッドの情報が入ります。
	int m_PlayerNum = 0;											//このコントローラーを使うキャラクター番号
};