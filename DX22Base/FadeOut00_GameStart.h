#pragma once
#include "DirectX.h"
#include "FadeBase.h"
#include "TextureClass.h"
#include "Calculation.h"
#include "ConstantBuffer.h"

class FadeOutWipe : public FadeBase
{
private:
	static RenderTarget* m_pGameEndRenderTarget;
	static DepthStencil* m_pGameEndDepthStencil;

public:
	static void CreateFadeOutRenderTarget();
	static void SetFadeOutRenderTarget();
	static void ReleaseRenderTarget();

public:
	FadeOutWipe();
	~FadeOutWipe() override;
	void SetWipeTime(float time);
	void SetDirection(DirectX::XMFLOAT2 Direction);
	void SetRenderTargetTexture();

private:
	void FadeStartInit() override;
	void FadeUpdate() override;
	void PrevDraw() override;

private:

private:
	CVector2		m_WipeDirection;
	float			m_WipeSize = 0.0f;
	float			m_WipeTime = 0.0f;
	float			m_CountTime = 0.0f;
	ConstantBuffer* m_pConstuntBuffer = nullptr;
};
