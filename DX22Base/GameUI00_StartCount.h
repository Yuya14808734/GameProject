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
	Number2D m_CountImage;								//3.2.1�ƃJ�E���g������
	Image2D m_GoTextImage;								//Go�̕�����`��
	CVector2 m_StartSize;								//�e��̕�����`�悷��Ƃ��̍ŏ��̃T�C�Y
	CVector2 m_AddSize;									//�ǂꂭ�炢�̑����ł��������Ȃ邩
	bool m_IsGoDraw = false;							//�����ł͂Ȃ�Go��`�悷�邩
	float m_PatternChangeCount = 0.0f;					//�͗l�̐؂�ւ��ŕb����ϐ�
	float m_PatternChangeTime = 0.0f;					//�͗l�̐؂�ւ��łǂ̎��ԂɕύX���邩���������ϐ�
	ID3D11ShaderResourceView* m_pPattern = nullptr;		//�e�����̖͗l
	ConstantBuffer* m_ConstantBuffer_SecondTextureUV;	//�͗l��UV
	DirectX::XMFLOAT4 m_UVParam = DirectX::XMFLOAT4(0.0f,0.0f,1.0f,1.0f);	//�͗l��UV���W
	PixelShader* m_pPS_MultiTexture = nullptr;			//�e�����摜�Ŏg��PixelShader
	VertexShader* m_pVS_MultiTexture = nullptr;			//�e�����摜�Ŏg��VertexShader

};