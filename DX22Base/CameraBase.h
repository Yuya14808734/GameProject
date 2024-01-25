//#pragma once
#ifndef CAMERABASE
#define CAMERABASE
#include <DirectXMath.h>
#include "Calculation.h"

class CameraBase 
{
public :
	CameraBase();
	virtual ~CameraBase();
	virtual void Init();
	virtual void Uninit();
	virtual void Update() = 0;
	virtual void ChangeInit();
	virtual void ChangeUninit();
	DirectX::XMFLOAT4X4 GetViewMatrix();
	DirectX::XMFLOAT4X4 GetProjectionMatrix();
	void SetPos(const CVector3& pos);
	void SetPos(const DirectX::XMFLOAT3& pos);
	void SetLookPos(const CVector3& pos);
	void SetLookPos(const DirectX::XMFLOAT3& pos);
	const CVector3& GetPos();
	const CVector3& GetLookPos();
	DirectX::XMFLOAT3 GetPos_xmfloat();
	DirectX::XMFLOAT3 GetLook_xmfloat();
	float GetFovAngle();
	float GetAspect();
	float GetNearLength();
	float GetFarLength();

protected:
	CVector3 m_pos;
	CVector3 m_look;
	CVector3 m_up;	//ビュー行列の設定に必要な変数
	float m_fovy;
	float m_aspect;
	float m_near;
	float m_far;	//プロジェクション行列の設定に必要な変数
};


#endif //CAMERABASE