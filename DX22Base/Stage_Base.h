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
	void StageColliderDraw();	//ステージのコライダーの描画
	std::vector<BoxCollider>* GetStageCollider() const;
	std::vector<CVector3>* GetCharacterStartPos() const;
	float GetDeadLineRightX();
	float GetDeadLineLeftX();
	float GetDeadLineTopY();
	float GetDeadLineBottomY();
	CVector3 AddRespawn();			//リスポーンしている数を増やす。戻り値は新しいリスポーン位置
	void MinaRespawn();

protected:

	//======================================================
	//多分操作はほぼ同じになるため上の関数を使うことになりそう

	virtual void Init() {};		//継承先の初期化
	virtual void Uninit() {};	//継承先の終了処理
	virtual void Update() {}; 	//継承先の更新
	virtual void Draw() {};		//継承先の描画


protected:
	std::vector<BoxCollider> m_StageCollider;
	std::vector<CVector3> m_CharacterStartPos;
	std::vector<ModelDrawer> m_ModelDrawer;
	float m_CameraNearZ = 0.0f;
	float m_CameraFarZ	= 0.0f;

	//プレイヤーがこの位置を超えると死ぬ
	float m_DeadLineRightX	= 0.0f;
	float m_DeadLineLeftX	= 0.0f;
	float m_DeadLineTopY	= 0.0f;
	float m_DeadLineBottomY = 0.0f;

	//プレイヤーのリスポーン位置
	CVector3 m_BaseRespawnPos;
	float m_RespawnDistance;
	int m_UseRespawnNum = 0;




};