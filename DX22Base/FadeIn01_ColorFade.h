#pragma once
#include "DirectX.h"
#include "FadeBase.h"
#include "TextureClass.h"
#include "Calculation.h"
#include "ConstantBuffer.h"

class FadeInColorFade : public FadeBase
{
public:
	FadeInColorFade();
	~FadeInColorFade() override;
	void SetFadeTime(float time);
private:
	void FadeUpdate() override;
private:
	float m_CountTime = 0.0f;
	float m_FadeTime = 0.0f;
};
