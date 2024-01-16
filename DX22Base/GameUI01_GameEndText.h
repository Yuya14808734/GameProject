#pragma once
#include "Image2D.h"
#include "Calculation.h"
#include "ConstantBuffer.h"

class GameEndText : public Image2D
{
private:
	const float m_SmallEndTime = 0.3f;
	const float m_ShakeEndTime = 0.3f;
	const float m_TextFlashEndTime = 1.0f;
	const float m_FadeEndTime = 0.3f;

public:
	GameEndText();
	~GameEndText() override;
	void Update() override;
	void PrevDraw() override;
	void SetStartSize(const CVector2& size);
	void SetEndSize(const CVector2& size);
	void StartAnimetion();
	void EndAnimetion();

private:
	void SmallerUpdate();
	void ShakeUpdate();
	void FlashUpdate();
	void FadeInUpdate();
	void StartSmaller();
	void StartShake();
	void StartFlash();
	void StartFade();
	void EndSmaller();
	void EndShake();
	void EndFlash();
	void EndFade();

private:
	bool m_Small = false;
	float m_SmallTimeCount = 0.0f;
	CVector2 m_StartSize;
	CVector2 m_EndSize;
	bool m_Shake = false;
	float m_ShakeTimeCount = 0.0f;
	bool m_Flash = false;
	float m_FlashTimeCount = 0.0f;
	bool m_Fade = false;
	float m_FadeTimeCount = 0.0f;
	
	ConstantBuffer* m_pConstantBuffer_ComparisonColor = nullptr;
	DirectX::XMFLOAT4 m_CamparisonColor = DirectX::XMFLOAT4(0.0f,0.0f,0.0f,0.0f);
};