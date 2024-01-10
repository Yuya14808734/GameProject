#pragma once

#include "DirectX.h"
#include <DirectXMath.h>
#include "Sprite.h"
#include "DirectXTex/Texture.h"
#include "Calculation.h"
#include "Shader.h"

class Image3D
{
public:
	Image3D();
	~Image3D();
	virtual void Update();
	void Draw();
	void SetTexture(const char* FilePath);
	void ReleaseTexture();
	void SetPos(const DirectX::XMFLOAT3& pos);
	void SetPos(const CVector3& pos);
	void SetPos(const CVector2& pos);
	const CVector3& GetPos() const;
	void SetSize(const DirectX::XMFLOAT2& size);
	void SetSize(const CVector2& size);
	const CVector2& GetSize() const;
	void SetScale(const DirectX::XMFLOAT3& Scale);
	void SetScale(const CVector3& size);
	const CVector3& GetScale() const;
	void SetRotate(CVector3 rotate);
	void SetRotate(CQuaternion quaternion);
	void SetUVPos(const DirectX::XMFLOAT2& uvpos);
	void SetUVPos(const CVector2& uvpos);
	const CVector2& GetUVPos() const;
	void SetUVSize(const DirectX::XMFLOAT2& uvsize);
	void SetUVSize(const CVector2& uvsize);
	const CVector2& GetUVSize() const;
	void SetVertexShader(VertexShader* pVS);
	void SetPixelShader(PixelShader* pPS);
	void SetBillboard(bool billboard);

protected:
	virtual void PrevDraw() {};

private:
	ID3D11ShaderResourceView* m_pTexture = nullptr;
	VertexShader* m_pVertexShader = nullptr;
	PixelShader* m_pPixelShader = nullptr;
public:
	CVector3 m_BasePos;				//位置の原点となる座標
	CVector3 m_pos;					//位置
	CVector2 m_size;				//画像のサイズ
	CVector3 m_scale;				//スケール
	CQuaternion m_rotate;			//回転量
	CVector2 m_UVpos;				//UV位置
	CVector2 m_UVsize;				//UVサイズ
	DirectX::XMFLOAT4 m_color;		//色
	bool m_Billboard = false;		//ビルボードをするか
};