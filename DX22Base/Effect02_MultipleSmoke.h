#pragma once

#include "EffectBase.h"
#include "Calculation.h"
#include "Image3D.h"
#include <vector>
#include "Shader.h"

//==========================================================
// 
// 吹っ飛んだ時の雲のエフェクト(複数)
// 
//==========================================================

class MultipleSmoke : public EffectBase
{
private:
	struct SingleSmokeParameter
	{
		int texNum = 0;
		float time = 0.0f;
		CVector3 pos;
		CVector3 basePos;
		CVector2 size;
		CVector3 velocity;
	};

public:
	MultipleSmoke();
	~MultipleSmoke() override;
	void Update() override;
	void Draw() override;
	void PausedEffect(bool paused = true) override;
	void AddPlayEffect(const CVector3& pos, const CVector3& velocity);
	void SetSingleSmokeEndTime(float time);
	void SetEffectAddEnd(bool end);

private:
	Image3D m_SmokeImages[4];								//雲の画像
	std::vector<SingleSmokeParameter> m_SingleSmokeParams;	//単一の雲のパラメータ
	PixelShader* m_pDissovleShader = nullptr;				//ピクセルシェーダ
	bool m_EffectAddEnd = false;							//エフェクトがもう足されない事を設定
	ConstantBuffer m_Buffer_DissolveParameter;				//定数バッファ
	float m_EndTime = 0.0f;									//エフェクト削除時間
	bool m_isUpdate = false;								//アップデートをするか
	ID3D11ShaderResourceView* m_pDissolveTexture = nullptr;	//ディゾルブのテクスチャ
	float m_DissolveParameter[4];							//定数バッファに渡す内容

};