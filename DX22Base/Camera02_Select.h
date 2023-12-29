#pragma once
#include "CameraBase.h"

class CameraSelect : public CameraBase
{
public:
	CameraSelect();
	~CameraSelect();
	void Update() override;
	void ChangeInit() override;
	void ChangeUninit() override;


};
