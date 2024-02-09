#pragma once

#include "CameraBase.h"
#include "Light.h"

class CameraLight : public CameraBase
{
public:
	CameraLight();
	~CameraLight();
	
	void Init() override;
	void Uninit() override;
	void Update() override;
	void ChangeInit() override;
	void ChangeUninit() override;

	void SetLight(LightObject* pLight);

private:
	LightObject* m_pLight = nullptr;
};
