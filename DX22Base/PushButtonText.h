#pragma once
#include "Image2D.h"

class PushEnterButtonText : public Image2D
{
public:
	PushEnterButtonText();
	~PushEnterButtonText();
private:
};

class PushAButtonText : public Image2D
{
public:
	PushAButtonText();
	~PushAButtonText();
private:
};

class PushButtonText
{
private:
	const float m_FadeInOutTime = 2.0f;

public:
	PushButtonText();
	~PushButtonText();
	void Update();
	void Draw();
	void SetPos(const CVector3& pos);
	void SetScale(float scale);

private:
	PushEnterButtonText m_PushEnterButtonText;
	PushAButtonText		m_PushAButtonText;
	float m_Time = 0.0f;
};