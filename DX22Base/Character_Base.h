#pragma once

#include <DirectXMath.h>
class Attack;

class Character
{
public:
	void Character_Init();		//キャラクターの初期化
	void Character_Uninit();	//キャラクターの終了処理
	void Character_Update();	//キャラクターの更新
	void Character_Draw();		//キャラクターの描画

protected:

	//======================================================
	//多分操作はほぼ同じになるため上の関数を使うことになりそう

	virtual void Init();		//継承先の初期化
	virtual void Uninit();		//継承先の終了処理
	virtual void Update();		//継承先の更新
	virtual void Draw();		//継承先の描画


protected:
	DirectX::XMFLOAT3 m_pos;
	DirectX::XMFLOAT3 m_size;



	Attack* m_pNowAttack = nullptr;	//今行っている攻撃
	

};