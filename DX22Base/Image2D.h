//#pragma once
#ifndef UI_BASE_H
#define UI_BASE_H

#include "DirectX.h"
#include <DirectXMath.h>
#include "Sprite.h"
#include "DirectXTex/Texture.h"

class Image2D
{
public:
	Image2D();
	virtual ~Image2D();
	virtual void Update();
	void Draw();
	void SetPos(DirectX::XMFLOAT3 pos);
	void SetSize(DirectX::XMFLOAT2 size);

protected:
	ID3D11ShaderResourceView* m_pTexture;
	DirectX::XMFLOAT3 m_pos;
	DirectX::XMFLOAT2 m_size;
	DirectX::XMFLOAT2 m_UVpos;
	DirectX::XMFLOAT2 m_UVsize;
};
#endif