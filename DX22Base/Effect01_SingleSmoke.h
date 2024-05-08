#pragma once
#include "EffectBase.h"
#include "Calculation.h"
#include "Image3D.h"

//==========================================================
// 
// 吹っ飛んだ時の雲のエフェクト(一つだけ)
// 
//==========================================================

class SingleSmoke : public EffectBase
{
public:
	SingleSmoke();
	~SingleSmoke() override;
	void Update() override;
	void Draw() override;
	void PausedEffect(bool paused = true) override;
	void SetPos(const CVector3& pos);
	void SetTime(float EndTime);
	void SetVelocity(const CVector3& velocity);
	void PlayEffect(const CVector3& pos,float endTime,const CVector3& velocity);

private:
	Image3D m_SmokeImage;								//雲の画像
	CVector3 m_Velocity;								//雲を動かすベクトル
	ConstantBuffer m_Buffer_DissolveParameter;			//定数バッファ
	float m_Time = 0.0f;								//今の時間
	float m_EndTime = 0.0f;								//エフェクト削除時間
	bool m_isUpdate = false;							//アップデートをするか
	ID3D11ShaderResourceView* m_pDissolveTexture;		//ディゾルブのテクスチャ
	float m_DissolveParameter[4];						//定数バッファに渡す内容
};