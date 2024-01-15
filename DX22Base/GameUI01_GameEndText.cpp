#include "GameUI01_GameEndText.h"
#include "Main.h"
#include "ShaderManager.h"

GameEndText::GameEndText()
{
	//�V�F�[�_�[�̍쐬
	SetVertexShader(
		ShaderManager::CreateVertexShader("ComparisonColorPS", CreateShaderPath("ComparisonColorPS")));
	SetPixelShader(
		ShaderManager::CreatePixelShader("ComparisonColorPS", CreateShaderPath("ComparisonColorPS")));

	m_pConstantBuffer_ComparisonColor = new ConstantBuffer();
	m_pConstantBuffer_ComparisonColor->Create(sizeof(m_CamparisonColor));

	//�e�N�X�`���̓ǂݍ���
	SetTexture("Assets/UI/GameText.png");

	//�ʒu�̐ݒ�
	//�X�N���[���̐^�񒆂ɒu��
	m_BasePos = CVector2(
		static_cast<float>(GetAppWidth() * 0.5f), 
		static_cast<float>(GetAppHeight()) * 0.5f);

	//�ŏ��͕`�悵�Ȃ�
	m_IsVisible = false;
}

GameEndText::~GameEndText()
{

}

void GameEndText::Update()
{
	switch (m_DrawState)
	{
	case GameEndText::SMALLER:
		SmallerUpdate();
		break;
	case GameEndText::SHAKE:
		ShakeUpdate();
		break;
	case GameEndText::NORMAL:
		NormalUpdate();
		break;
	}
}

void GameEndText::PrevDraw()
{
	m_pConstantBuffer_ComparisonColor->Write(&m_CamparisonColor);
	m_pConstantBuffer_ComparisonColor->BindVS(0);
}

void GameEndText::SetStartSize(const CVector3 & size)
{
	m_StartSize = size;
}

void GameEndText::SetEndSize(const CVector3 & size)
{
	m_EndSize = size;
}

void GameEndText::StartAnimetion()
{
	m_DrawState = GameEndText::DRAWSTATE::SMALLER;
	m_TimeCount = 0.0f;
	m_IsVisible = true;
}

void GameEndText::SmallerUpdate()
{
	m_TimeCount += 1.0f / 60.0f;
	
	//���������鎞�Ԃ𒴂��Ă�����
	if (m_TimeCount > m_LerpEndTime)
	{
		m_DrawState = DRAWSTATE::SHAKE;
		m_size = m_EndSize;
		m_TimeCount = 0.0f;
		return;
	}

	float LerpPercent = m_TimeCount / m_LerpEndTime;
	//��Ԃ��g���ăT�C�Y��ύX
	m_size = (m_StartSize * (1.0f - LerpPercent)) + (m_EndSize * LerpPercent);

	//�T�C�Y�����܂�Ƃ��ɃA���t�@��1�ɂȂ�悤�ɂ���
	m_color.w = LerpPercent;
}

void GameEndText::ShakeUpdate()
{
	m_TimeCount += 1.0f / 60.0f;
	
	//�h�炷���Ԃ𒴂��Ă�����
	if (m_TimeCount > m_LerpEndTime)
	{
		m_DrawState = DRAWSTATE::NORMAL;
		m_TimeCount = 0.0f;
		m_pos = CVector2::GetZero();
		return;
	}

	//�h�炷����
	//�c��-500~500�̊Ԃ̐��l�Ń����_���ɗh�炵�Ă��
	m_pos = CVector2(
		static_cast<float>((rand() % 1000) + 1) - 500.0f,
		static_cast<float>((rand() % 1000) + 1) - 500.0f
	);
}

void GameEndText::NormalUpdate()
{
	//�ŏ��̈�b�̂ݔ������Ă��
	m_TimeCount += 1.0f / 60.0f;

	float ChangeColorPercent = m_TimeCount / m_TextChangeColorTime;

	//shader�ɏ�̐��l��n��
}
