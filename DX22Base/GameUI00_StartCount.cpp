#include "GameUI00_StartCount.h"
#include "Main.h"
#include "ShaderManager.h"

const CVector2 GameStartCountUI::m_CountTextStartSize = CVector2(100.0f, 100.0f);
const CVector2 GameStartCountUI::m_GoTextStartSize = CVector2(640.0f, 246.0f);


GameStartCountUI::GameStartCountUI()
{
	//�萔�o�b�t�@�[�̍쐬
	m_ConstantBuffer_SecondTextureUV = new ConstantBuffer();
	m_ConstantBuffer_SecondTextureUV->Create(sizeof(m_UVParam));

	//�V�F�[�_�[�̍쐬
	m_pVS_MultiTexture =
	ShaderManager::CreateVertexShader("MultiplyTextureVS", CreateShaderPath("MultiplyTextureVS"));
	m_pPS_MultiTexture =
	ShaderManager::CreatePixelShader("MultiplyTexturePS", CreateShaderPath("MultiplyTexturePS"));

	//���_�V�F�[�_�[�̐ݒ�
	m_CountImage.SetVertexShader(m_pVS_MultiTexture);
	m_GoTextImage.SetVertexShader(m_pVS_MultiTexture);
	//�s�N�Z���V�F�[�_�[�̐ݒ�
	m_CountImage.SetPixelShader(m_pPS_MultiTexture);
	m_GoTextImage.SetPixelShader(m_pPS_MultiTexture);

	//�e�摜�̃e�N�X�`���[�̐ݒ�
	m_CountImage.SetNumberTexture("Assets/NumberImage/NumberImage02.png",4,3);
	m_CountImage.m_size = m_CountTextStartSize;
	m_GoTextImage.SetTexture("Assets/NumberImage/GoTextImage02.png");
	m_GoTextImage.m_size = m_GoTextStartSize;
	
	//�e�摜�̈ʒu��ݒ�
	m_GoTextImage.m_pos = m_CountImage.m_pos = CVector3(
		static_cast<float>(GetAppWidth()) * 0.5f
		, static_cast<float>(GetAppHeight()) * 0.4f
		, 0.0f);
	m_AddSize = CVector2(1.0f, 1.0f);

	//��̕����ɉf���͗l�����[�h
	LoadTextureFromFile("Assets/Texture/Fire.png", &m_pPattern);

	m_PatternChangeCount = 0.0f;													//���Ԃ𐔂���
	m_PatternChangeTime = static_cast<float>((rand() % 10) + 1) / 100.0f;	//�͗l��؂�ւ���b��
}

GameStartCountUI::~GameStartCountUI()
{
	if (m_pPattern != nullptr)
	{
		m_pPattern->Release();
		m_pPattern = nullptr;
	}

	delete m_ConstantBuffer_SecondTextureUV;
}

void GameStartCountUI::Update()
{
	m_PatternChangeCount += 1.0f / 60.0f;

	if (m_PatternChangeTime < m_PatternChangeCount)
	{
		m_PatternChangeTime = static_cast<float>((rand() % 10) + 1) / 100.0f;
		m_PatternChangeCount = 0.0f;

		//�T�C�Y��ݒ�
		//				(0�`100) - (�Œ�UV�T�C�Y)
		int RandPosNumX = (rand() % 100) + 1 - 30;
		int RandPosNumY = (rand() % 100) + 1 - 30;
		int MinaNum = RandPosNumX > RandPosNumY ? 100 - RandPosNumY : 100 - RandPosNumX;
		int RandSizeNum = MinaNum == 0 ? 0 : rand() % MinaNum + 1;

		m_UVParam.x = static_cast<float>(RandPosNumX) / 100.0f;
		m_UVParam.y = static_cast<float>(RandPosNumY) / 100.0f;
		m_UVParam.w = m_UVParam.z = static_cast<float>(RandSizeNum) / 100.0f;
	}

	if (m_IsGoDraw)
	{
		m_GoTextImage.m_size += m_AddSize;
	}
	else
	{
		m_CountImage.m_size += m_AddSize;
	}
}

void GameStartCountUI::Draw()
{
	SetTexturePS(m_pPattern,1);

	m_ConstantBuffer_SecondTextureUV->Write(&m_UVParam);
	m_ConstantBuffer_SecondTextureUV->BindVS(2);

	if (m_IsGoDraw)
	{
		m_GoTextImage.Draw();
	}
	else
	{
		m_CountImage.Draw();
	}
}

void GameStartCountUI::SetNumDraw(int Num)
{
	m_CountImage.SetNumber(Num);
	m_CountImage.m_size = m_CountTextStartSize;
	m_AddSize = m_CountTextStartSize * 0.01f;
}

void GameStartCountUI::SetGoDraw(bool draw)
{
	m_IsGoDraw = draw;

	if (draw)
	{
		m_GoTextImage.m_size = m_GoTextStartSize;
		m_AddSize = m_GoTextStartSize * 0.01f;
	}
	else
	{
		m_AddSize = m_CountTextStartSize * 0.01f;
	}
}
