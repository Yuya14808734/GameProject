#pragma once
#include "CameraBase.h"

class CameraNoMove : public CameraBase
{
public:
	CameraNoMove();
	~CameraNoMove();
	void Update() override;
	void ChangeInit() override;
	void ChangeUninit() override;
};
