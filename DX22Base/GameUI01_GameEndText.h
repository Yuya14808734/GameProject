#pragma once
#include "Image2D.h"
#include "Calculation.h"
#include "ConstantBuffer.h"

class GameEndText : public Image2D
{
	enum DRAWSTATE
	{
		SMALLER = 0,
		SHAKE,
		NORMAL,
		MAX
	};

private:
	const float m_LerpEndTime = 0.5f;
	const float m_ShakeEndTime = 0.3f;
	const float m_TextChangeColorTime = 1.0f;

public:
	GameEndText();
	~GameEndText() override;
	void Update() override;
	void PrevDraw() override;
	void SetStartSize(const CVector3& size);
	void SetEndSize(const CVector3& size);
	void StartAnimetion();

private:
	void SmallerUpdate();
	void ShakeUpdate();
	void NormalUpdate();
private:
	DRAWSTATE m_DrawState = DRAWSTATE::MAX;
	CVector2 m_StartSize;
	CVector2 m_EndSize;
	float m_TimeCount = 0.0f;
	ConstantBuffer* m_pConstantBuffer_ComparisonColor = nullptr;
	DirectX::XMFLOAT4 m_CamparisonColor = DirectX::XMFLOAT4(0.0f,0.0f,0.0f,0.0f);
};