#pragma once

// ================================
// インクルード
// ================================
#include "Image2D.h"
#include "TextureClass.h"

class FadeBase : public Image2D
{
public:
	FadeBase();
	virtual ~FadeBase() override;
	void Update() override;

protected:
	virtual void FadeStartInit();
	virtual void FadeUpdate();
	void PrevDraw() override;
	
protected:
	bool m_FadeStart = false;
	bool m_FadeStop = false;
	bool m_FadeEnd = false;

public:
	// ================================
	// Get/Set関数
	// ================================

	void SetFadeStart(bool start) 
	{
		m_FadeStart = start; 
		if (m_FadeStart) { FadeStartInit(); }
	}

	void SetFadeStop(bool stop) 
	{ m_FadeStop = stop; }

	bool GetFadeEnd() 
	{ return m_FadeEnd; }
};