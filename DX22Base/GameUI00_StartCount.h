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
	float m_Count = 0.0f;
	float m_ChangeTime = 0.0f;
	Number2D m_CountImage;
	Image2D m_GoTextImage;
	CVector2 m_StartSize;
	CVector2 m_AddSize;
	bool m_IsGoDraw = false;
	ID3D11ShaderResourceView* m_pPattern = nullptr;
	ConstantBuffer* m_ConstantBuffer_SecondTextureUV;
	DirectX::XMFLOAT4 m_UVParam = DirectX::XMFLOAT4(0.0f,0.0f,1.0f,1.0f);
	PixelShader* m_pPS_MultiTexture = nullptr;
	VertexShader* m_pVS_MultiTexture = nullptr;

};