#pragma once
#include "Effect_Manager.h"

class EffectBase
{
public:
	EffectBase();									//初期化
	virtual ~EffectBase();							//終了処理
	virtual void Update();							//更新
	virtual void Draw();							//描画
	virtual void PausedEffect(bool Paused = true);	//エフェクトを止めるときの処理

	void SetDestroy(bool destroy = true);
	bool GetisDestroy();

protected:
	bool m_isDestroy = false;
};