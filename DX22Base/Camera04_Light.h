#pragma once

#include "CameraBase.h"
#include "Light.h"
#include "ConstantBuffer.h"

class CameraLight : public CameraBase
{
public:
	CameraLight();
	~CameraLight() override;
	
	void Init() override;
	void Uninit() override;
	void Update() override;
	void ChangeInit() override;
	void ChangeUninit() override;

	void SetLight(LightObject* pLight);
	void WriteConstBuffer();

private:
	void SetParameter();

private:
	LightObject* m_pLight = nullptr;
	float m_LightPlane[4];

	ConstantBuffer* m_pConstBuffer;
};
