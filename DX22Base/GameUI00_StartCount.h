#pragma once
#include "Image2D.h"
#include "Number2D.h"
#include "ConstantBuffer.h"
#include "DirectX.h"
#include "Shader.h"

class GameStartCountUI
{
private:
	static const CVector2 m_CountTextStartSize;
	static const CVector2 m_GoTextStartSize;

public:
	GameStartCountUI();
	~GameStartCountUI();
	void Update();
	void Draw();
	void SetNumDraw(int Num);
	void SetGoDraw(bool draw);
private:
	Number2D m_CountImage;								//3.2.1とカウントをする
	Image2D m_GoTextImage;								//Goの文字を描画
	CVector2 m_StartSize;								//各上の文字を描画するときの最初のサイズ
	CVector2 m_AddSize;									//どれくらいの速さでおおきくなるか
	bool m_IsGoDraw = false;							//数字ではなくGoを描画するか
	float m_PatternChangeCount = 0.0f;					//模様の切り替えで秒数を変数
	float m_PatternChangeTime = 0.0f;					//模様の切り替えでどの時間に変更するかを持たす変数
	ID3D11ShaderResourceView* m_pPattern = nullptr;		//各文字の模様
	ConstantBuffer* m_ConstantBuffer_SecondTextureUV;	//模様のUV
	DirectX::XMFLOAT4 m_UVParam = DirectX::XMFLOAT4(0.0f,0.0f,1.0f,1.0f);	//模様のUV座標
	PixelShader* m_pPS_MultiTexture = nullptr;			//各文字画像で使うPixelShader
	VertexShader* m_pVS_MultiTexture = nullptr;			//各文字画像で使うVertexShader

};