#pragma once

#include "DirectX.h"
#include <DirectXMath.h>
#include "Sprite.h"
#include "DirectXTex/Texture.h"
#include "Calculation.h"
#include "Shader.h"

//==========================================================
//�摜�Ɋւ��Ă͏ォ��E�ɂ����Đ���������ł���悤��
//�e�N�X�`���ł͂Ȃ��Ƃ��������Ȃ�܂��B
//�܂�0�͈�ԍ���ɒu���Ă��������B
//��)
//0 1 2 3
//4 5 6 7
//8 9
//==========================================================

class Number2D
{
public:
	Number2D();
	virtual ~Number2D();
	virtual void Update();
	virtual void PrevDraw();
	void Draw();
	void SetPos(const DirectX::XMFLOAT3& pos);
	void SetPos(const CVector2& pos);
	const CVector2& GetPos();
	void SetSize(const DirectX::XMFLOAT2& size);
	void SetSize(const CVector2& size);
	const CVector2& GetSize();
	void SetNumberTexture(const char* FilePath, int SplitX, int SplitY);
	void SetNumber(int Num);
	void SetUseDistance(bool useDistance);
	void SetDistance(float distance);
	void SetVertexShader(VertexShader* pVS);
	void SetPixelShader(PixelShader* pPS);

private:
	ID3D11ShaderResourceView* m_pTexture = nullptr;
	VertexShader* m_pVertexShader = nullptr;
	PixelShader* m_pPixelShader = nullptr;
public:
	CVector3 m_BasePos;
	CVector3 m_pos;
	CVector2 m_size;
	CVector2 m_UVpos;
	CVector2 m_UVsize;
	DirectX::XMFLOAT4 m_color;
	bool m_UseDistance = false;
	float m_NumDistance = 0.0f;
protected:
	int m_Number = 0;
private:
	int m_SplitX = 0;
	int m_SplitY = 0;
};