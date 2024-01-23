#pragma once
#include "DirectX.h"
#include "FadeBase.h"
#include "TextureClass.h"
#include "Calculation.h"
#include "ConstantBuffer.h"

class FadeInWipe : public FadeBase
{
	// ========================================================
	// static 
	// ========================================================
private:
	static RenderTarget* m_pRenderTarget_WipeTexture;
	static DepthStencil* m_pDepthStencil_WipeTexture;

public:
	static void CreateRenderTarget_WipeTexture();
	static void SetRenderTargets_WipeTexture();
	static void ReleaseRenderTargets_WipeTexture();

	// ========================================================
	// dynamic
	// ========================================================
public:
	FadeInWipe();
	~FadeInWipe() override;
	void WipeSetting(float WipeTime, const CVector2& Direction);

private:

	void SetWipeTime(float time);
	void SetWipeDirection(const CVector2& WipeDirection);
	void SetWipeSize();
	void SetWipeTexture();
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
