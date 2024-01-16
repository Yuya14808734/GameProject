#include "GameUI01_GameEndText.h"
#include "Main.h"
#include "ShaderManager.h"
#include "Input.h"

GameEndText::GameEndText()
{
	//�V�F�[�_�[�̍쐬
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
	m_size = CVector2(640.0f, 304.0f);

	//�ŏ��͕`�悵�Ȃ�
	m_IsVisible = false;

	m_CamparisonColor = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);

	m_Shake = m_Flash = m_Small = false;
}

GameEndText::~GameEndText()
{

}

void GameEndText::Update()
{
	SmallerUpdate();
	ShakeUpdate();
	FlashUpdate();
	FadeInUpdate();
}

void GameEndText::PrevDraw()
{
	m_pConstantBuffer_ComparisonColor->Write(&m_CamparisonColor);
	m_pConstantBuffer_ComparisonColor->BindPS(0);
}

void GameEndText::SetStartSize(const CVector2 & size)
{
	m_StartSize = size;
}

void GameEndText::SetEndSize(const CVector2 & size)
{
	m_EndSize = size;
}

void GameEndText::StartAnimetion()
{
	StartSmaller();
	StartFade();
	m_IsVisible = true;
}

void GameEndText::EndAnimetion()
{
	EndSmaller();
	EndShake();
	EndFlash();
	EndFade();
}


void GameEndText::SmallerUpdate()
{
	if (!m_Small)
	{
		return;
	}

	m_SmallTimeCount += 1.0f / 60.0f;
	
	//���������鎞�Ԃ𒴂��Ă�����
	if (m_SmallTimeCount > m_SmallEndTime)
	{
		m_size = m_EndSize;
		EndSmaller();
		EndFade();
		StartShake();
		StartFlash();
		return;
	}

	float LerpPercent = m_SmallTimeCount / m_SmallEndTime;
	//��Ԃ��g���ăT�C�Y��ύX
	m_size = (m_StartSize * (1.0f - LerpPercent)) + (m_EndSize * LerpPercent);

	//�T�C�Y�����܂�Ƃ��ɃA���t�@��1�ɂȂ�悤�ɂ���
	m_color.w = LerpPercent;
}


void GameEndText::ShakeUpdate()
{
	if (!m_Shake)
	{
		return;
	}

	m_ShakeTimeCount += 1.0f / 60.0f;
	
	//�h�炷���Ԃ𒴂��Ă�����
	if (m_ShakeTimeCount > m_SmallEndTime)
	{
		m_pos = CVector2::GetZero();
		EndShake();
		return;
	}

	//�h�炷����
	//�c��-500~500�̊Ԃ̐��l�Ń����_���ɗh�炵�Ă��
	m_pos = CVector2(
		static_cast<float>((rand() % 10) + 1) - 5.0f,
		static_cast<float>((rand() % 10) + 1) - 5.0f
	);
}


void GameEndText::FlashUpdate()
{
	if (!m_Flash)
	{
		return;
	}

	//�ŏ��̈�b�̂ݔ������Ă��
	m_FlashTimeCount += 1.0f / 60.0f;

	m_CamparisonColor = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);

	float ChangeColorPercent = m_FlashTimeCount / m_TextFlashEndTime;

	if (m_FlashTimeCount >= m_TextFlashEndTime)
	{
		ChangeColorPercent = 1.0f;
		EndFlash();
	}

	m_CamparisonColor.x =
	m_CamparisonColor.y =
	m_CamparisonColor.z = sinf(ChangeColorPercent * DirectX::XM_PI);

}

void GameEndText::FadeInUpdate()
{
	if (!m_Fade)
	{
		return;
	}

	//�ŏ��̈�b�̂ݔ������Ă��
	m_FadeTimeCount += 1.0f / 60.0f;

	m_CamparisonColor = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);

	float ChangeColorPercent = m_FadeTimeCount / m_FadeEndTime;
	
	if (m_FadeTimeCount >= m_FadeEndTime)
	{
		ChangeColorPercent = 1.0f;
		EndFade();
	}

	float Radian = (ChangeColorPercent * DirectX::XM_PI) + (DirectX::XM_PI * 0.5f);
	
	m_CamparisonColor.x =
		m_CamparisonColor.y =
		m_CamparisonColor.z = (sinf(Radian) * 0.5f) + 0.5f;
}

void GameEndText::StartSmaller()
{
	m_Small = true;
	m_SmallTimeCount = 0.0f;
}

void GameEndText::StartShake()
{
	m_Shake = true;
	m_ShakeTimeCount = 0.0f;
}

void GameEndText::StartFlash()
{
	m_Flash = true;
	m_FlashTimeCount = 0.0f;
}

void GameEndText::StartFade()
{
	m_Fade = true;
	m_FadeTimeCount = 0.0f;
}

void GameEndText::EndSmaller()
{
	m_Small = false;
	m_SmallTimeCount = m_SmallEndTime;
}

void GameEndText::EndShake()
{
	m_Shake = false;
	m_ShakeTimeCount = m_ShakeEndTime;
}

void GameEndText::EndFlash()
{
	m_Flash = false;
	m_FlashTimeCount = m_TextFlashEndTime;
}

void GameEndText::EndFade()
{
	m_Fade = false;
	m_FadeTimeCount = m_FadeEndTime;
}
