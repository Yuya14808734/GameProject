//#pragma once
#ifndef UI_BASE_H
#define UI_BASE_H

#include "DirectX.h"
#include <DirectXMath.h>
#include "Sprite.h"
#include "DirectXTex/Texture.h"
#include "Calculation.h"
#include "Shader.h"


class Image2D
{
public:
	Image2D();
	virtual ~Image2D();
	virtual void Update();
	virtual void PrevDraw();
	void Draw();
	void SetTexture(const char* FilePath);
	void SetPos(DirectX::XMFLOAT3& pos);
	void SetPos(CVector2& pos);
	void SetSize(DirectX::XMFLOAT2& size);
	void SetSize(CVector2& size);
	void SetUVPos(DirectX::XMFLOAT2& uvpos);
	void SetUVPos(CVector2& uvpos);
	void SetUVSize(DirectX::XMFLOAT2& uvsize);
	void SetUVSize(CVector2& uvsize);
	void SetVertexShader(VertexShader* pVS);
	void SetPixelShader(PixelShader* pPS);

private:
	ID3D11ShaderResourceView* m_pTexture = nullptr;
	VertexShader* m_pVertexShader = nullptr;
	PixelShader* m_pPixelShader = nullptr;
protected:
	CVector3 m_pos;
	CVector2 m_size;
	CVector2 m_UVpos;
	CVector2 m_UVsize;
	DirectX::XMFLOAT4 m_color;
};
#endif