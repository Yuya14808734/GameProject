
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

void FadeInWipe::FadeStartInit()
{
	
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

	//=====<�ǂꂭ�炢�̊������B����>=====
	m_WipeSize = m_CountTime / m_WipeTime;

	//=====<���ׂČ�����悤�ɂȂ�����true�ɂ���>=====
	if (m_CountTime > m_WipeTime)
	{
		m_CountTime = m_WipeTime;
		m_FadeEnd = true;
	}
}

void FadeInWipe::PrevDraw()
{
	//=====<�萔�o�b�t�@�œn��float4�̒l�ݒ�>=====
	DirectX::XMFLOAT4 CB =
	{ m_WipeDirection.x,m_WipeDirection.y,m_WipeSize,0.0f };
	m_pConstuntBuffer->Write(&CB);
	m_pConstuntBuffer->BindPS(0);
}

void FadeInWipe::SetWipeTime(float time)
{
	m_WipeTime = time;
}

void FadeInWipe::SetDirection(DirectX::XMFLOAT2 Direction)
{
	m_WipeDirection = Direction;
	m_WipeDirection = m_WipeDirection.normalize();
}

void FadeInWipe::SetWipeTexture()
{
	SetTexture(m_pRenderTarget_WipeTexture->GetResource());
}
