#pragma once
#include <vector>
#include "Collider.h"
#include "Calculation.h"
#include "ModelDrawer.h"

class Stage
{
public:
	void Stage_Init();		//キャラクターの初期化
	void Stage_Uninit();	//キャラクターの終了処理
	void Stage_Update();	//キャラクターの更新
	void Stage_Draw();		//キャラクターの描画
	std::vector<BoxCollider>* GetStageCollider() const;

protected:

	//======================================================
	//多分操作はほぼ同じになるため上の関数を使うことになりそう

	virtual void Init() {};		//継承先の初期化
	virtual void Uninit() {};	//継承先の終了処理
	virtual void Update() {}; 	//継承先の更新
	virtual void Draw() {};		//継承先の描画


protected:
	std::vector<BoxCollider> m_StageCollider;
	ModelDrawer m_ModelDrawer;

};