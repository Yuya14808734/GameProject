
#include "FadeOut00_GameStart.h"
#include "Main.h"
#include "ShaderManager.h"

//================================================
// static
//================================================

RenderTarget* FadeOutWipe::m_pGameEndRenderTarget = nullptr;
DepthStencil* FadeOutWipe::m_pGameEndDepthStencil = nullptr;

void FadeOutWipe::CreateFadeOutRenderTarget()
{
	//�����_�[�^�[�Q�b�g�̍쐬
	if (m_pGameEndRenderTarget == nullptr)
	{
		m_pGameEndRenderTarget = new RenderTarget();
		m_pGameEndRenderTarget->Create(DXGI_FORMAT_R32_FLOAT,
			//DXGI_FORMAT_R8G8B8A8_UNORM,
			GetAppWidth(), GetAppHeight());
	}

	//�[�x�X�e���V���̍쐬
	if (m_pGameEndDepthStencil == nullptr)
	{
		m_pGameEndDepthStencil = new DepthStencil();
		m_pGameEndDepthStencil->Create(
			static_cast<float>(GetAppWidth()),
			static_cast<float>(GetAppHeight()), false);
	}
}

void FadeOutWipe::SetFadeOutRenderTarget()
{
	CreateFadeOutRenderTarget();

	m_pGameEndRenderTarget->Clear();
	m_pGameEndDepthStencil->Clear();

	SetRenderTargets(1, &m_pGameEndRenderTarget, m_pGameEndDepthStencil);
}

void FadeOutWipe::ReleaseRenderTarget()
{
	//�����_�[�^�[�Q�b�g�̍폜
	if (m_pGameEndRenderTarget != nullptr)
	{
		delete m_pGameEndRenderTarget;
		m_pGameEndRenderTarget = nullptr;
	}

	//�[�x�X�e���V���̍폜
	if (m_pGameEndDepthStencil != nullptr)
	{
		delete m_pGameEndDepthStencil;
		m_pGameEndDepthStencil = nullptr;
	}
}

//================================================
// �N���X�̎���
//================================================

FadeOutWipe::FadeOutWipe()
	:m_WipeTime(0.0f),
	m_CountTime(0.0f),
	m_pConstuntBuffer(nullptr)
{
	m_pConstuntBuffer = new ConstantBuffer();
	m_pConstuntBuffer->Create(sizeof(DirectX::XMFLOAT4));

	SetPixelShader(
		ShaderManager::CreatePixelShader
		("DirectWipePS", CreateShaderPath("DirectWipePS"))
		,false);
}

FadeOutWipe::~FadeOutWipe()
{
	delete m_pConstuntBuffer;
}

void FadeOutWipe::FadeStartInit()
{
	
}

void FadeOutWipe::FadeUpdate()
{
	if (m_WipeTime == 0.0f)
	{
		return;
	}

	//���ォ�瓧���ɂ��Ă������ߐ��l���グ�Ă���
	m_CountTime += (1.0f / 60.0f);

	m_WipeSize = m_CountTime / m_WipeTime;
}

void FadeOutWipe::PrevDraw()
{
	DirectX::XMFLOAT4 CB =
	{m_WipeDirection.x,m_WipeDirection.y,m_WipeSize,0.0f};

	m_pConstuntBuffer->Write(&CB);
	m_pConstuntBuffer->BindPS(0);
}

void FadeOutWipe::SetWipeTime(float time)
{
	m_WipeTime = time;
}

void FadeOutWipe::SetDirection(DirectX::XMFLOAT2 Direction)
{
	m_WipeDirection = Direction;
	m_WipeDirection = m_WipeDirection.normalize();
}

void FadeOutWipe::SetRenderTargetTexture()
{
	SetTexture(m_pGameEndRenderTarget->GetResource());
}
