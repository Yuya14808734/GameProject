
#include "FadeIn00_GameEnd.h"
#include "Main.h"
#include "ShaderManager.h"

//================================================
// static
//================================================

RenderTarget* FadeInWipe::m_pRenderTarget_WipeTexture = nullptr;
DepthStencil* FadeInWipe::m_pDepthStencil_WipeTexture = nullptr;

void FadeInWipe::CreateRenderTarget_WipeTexture()
{
	// =====<�O�̂��ߏ����Ă���>=====
	ReleaseRenderTargets_WipeTexture();

	// =====<�����_�[�^�[�Q�b�g�̍쐬>=====
	if (m_pRenderTarget_WipeTexture == nullptr)
	{
		m_pRenderTarget_WipeTexture = new RenderTarget();
		m_pRenderTarget_WipeTexture->Create(DXGI_FORMAT_R8G8B8A8_UNORM,
			GetAppWidth(), GetAppHeight());
	}

	//=====<�[�x�X�e���V���̍쐬>=====
	if (m_pDepthStencil_WipeTexture == nullptr)
	{
		m_pDepthStencil_WipeTexture = new DepthStencil();
		m_pDepthStencil_WipeTexture->Create(
			static_cast<float>(GetAppWidth()),
			static_cast<float>(GetAppHeight()), false);
	}
}

void FadeInWipe::SetRenderTargets_WipeTexture()
{
	//=====<�����_�[�^�[�Q�b�g���쐬����>=====
	CreateRenderTarget_WipeTexture();

	//=====<�����_�[�^�[�Q�b�g�̒��������Ă��>=====
	m_pRenderTarget_WipeTexture->Clear();
	m_pDepthStencil_WipeTexture->Clear();

	//=====<�����_�[�^�[�Q�b�g��ݒ肷��>=====
	SetRenderTargets(1, &m_pRenderTarget_WipeTexture, m_pDepthStencil_WipeTexture);
}

void FadeInWipe::ReleaseRenderTargets_WipeTexture()
{
	//=====<�����_�[�^�[�Q�b�g�̍폜>=====
	if (m_pRenderTarget_WipeTexture != nullptr)
	{
		delete m_pRenderTarget_WipeTexture;
		m_pRenderTarget_WipeTexture = nullptr;
	}

	//=====<�[�x�X�e���V���̍폜>=====
	if (m_pDepthStencil_WipeTexture != nullptr)
	{
		delete m_pDepthStencil_WipeTexture;
		m_pDepthStencil_WipeTexture = nullptr;
	}
}

// ================================================
// �N���X�̎���
// ================================================

FadeInWipe::FadeInWipe()
	:m_WipeTime(0.0f),
	m_CountTime(0.0f),
	m_pConstuntBuffer(nullptr)
{
	//=====<�萔�o�b�t�@�̍쐬>=====
	m_pConstuntBuffer = new ConstantBuffer();
	m_pConstuntBuffer->Create(sizeof(DirectX::XMFLOAT4));

	//=====<Wipe�p�̃V�F�[�_�[���쐬�E�ݒ�>=====
	SetPixelShader(
		ShaderManager::CreatePixelShader
		("DirectWipePS", CreateShaderPath("DirectWipePS"))
		,false);

	//=====<�e�N�X�`���̐ݒ�>=====
	SetWipeTexture();
}

FadeInWipe::~FadeInWipe()
{
	//=====<�������̍폜����>=====
	delete m_pConstuntBuffer;
}

void FadeInWipe::FadeUpdate()
{
	//=====<WipeTime���ݒ肵�Ă��Ȃ���Ώo��>=====
	if (m_WipeTime == 0.0f)
	{
		return;
	}

	//=====<���ォ�瓧���ɂ��Ă������ߐ��l���グ�Ă���>=====
	m_CountTime += (1.0f / 60.0f);

	////=====<���ׂČ�����悤�ɂȂ�����true�ɂ���>=====
	if (m_CountTime > m_WipeTime)
	{
		m_FadeEnd = true;
	}
}

void FadeInWipe::PrevDraw()
{
	//=====<�萔�o�b�t�@�œn��float4�̒l�ݒ�>=====
	float NowSize = (m_CountTime / m_WipeTime) * m_WipeSize;

	DirectX::XMFLOAT4 CB =
	{ m_WipeDirection.x,m_WipeDirection.y,NowSize,0.0f };
	m_pConstuntBuffer->Write(&CB);
	m_pConstuntBuffer->BindPS(0);
}

void FadeInWipe::WipeSetting(float WipeTime, const CVector2& WipeDirection)
{
	SetWipeTime(WipeTime);
	SetWipeDirection(WipeDirection);
	SetWipeTexture();
}

void FadeInWipe::SetWipeTime(float time)
{
	m_WipeTime = time;
}

void FadeInWipe::SetWipeDirection(const CVector2& Direction)
{
	m_WipeDirection = Direction;
	m_WipeDirection = m_WipeDirection.normalize();
	SetWipeSize();
}

void FadeInWipe::SetWipeSize()
{
	//=====<�E�B���h�E�̑傫����ݒ�>=====
	CVector2 WindowSize = 
		CVector2(
			static_cast<float>(GetAppWidth()),
			static_cast<float>(GetAppHeight()));

	//=====<����Direction�łǂ�����������ʂ̒[�ɂ��̂��𒲂ׂ�>=====
	//���Ŏg���ϐ��̍쐬
	float Width_Percent		= m_WipeDirection.x / WindowSize.x;
	float Height_Percent	= m_WipeDirection.y / WindowSize.y;
	CVector2 WindowWipeVector;
	float WindowPercent = 0.0f;

	//�����������̑傫������ʃT�C�Y�ɂ����Ƃ��̒����𒲂ׂ�
	if (Width_Percent > Height_Percent)
	{
		//���̕������������ꍇ�A�c�̑傫�����g���Đ����`�ɂ���
		WindowPercent = m_WipeDirection.y * (WindowSize.y / m_WipeDirection.y);
	}
	else
	{
		//�c�̕������������ꍇ�A���̑傫�����g���Đ����`�ɂ���
		WindowPercent = m_WipeDirection.x * (WindowSize.x / m_WipeDirection.x);
	}

	//=====<�΂߂̒����𒲂ׂă��C�v���钷���Ƃ���>=====
	WindowWipeVector = m_WipeDirection * WindowPercent;
	m_WipeSize = WindowWipeVector.length();
}

void FadeInWipe::SetWipeTexture()
{
	if (m_pRenderTarget_WipeTexture == nullptr)
	{
		SetTexture("Assets/Texture/Fire.png");
	}
	else
	{
		SetTexture(m_pRenderTarget_WipeTexture->GetResource());
	}

}
