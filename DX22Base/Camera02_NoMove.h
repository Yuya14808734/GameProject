#pragma once
#include "CameraBase.h"

class CameraNoMove : public CameraBase
{
public:
	CameraNoMove();
	~CameraNoMove();
	void Init() override;
	void Uninit() override;
	void Update() override;
};