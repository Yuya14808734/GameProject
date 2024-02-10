//#pragma once
#ifndef CAMERABASE
#define CAMERABASE
#include <DirectXMath.h>
#include "Calculation.h"
#include "Collider.h"

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
	DirectX::XMMATRIX GetViewMatrix_TypeXMMAXRIX();
	DirectX::XMMATRIX GetProjectionMatrix_TypeXMMAXRIX();
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


	CVector3 GetRightVector();
	CVector3 GetUpVector();

	void CreateViewingFrustum();
	bool CheckInObject(const CVector3& Point, float Radius);

	CVector2 ChangeScreenPos(const CVector3& Pos3D);
	void SetOrtho(bool ortho);							//���s���e

protected:
	CVector3 m_pos;
	CVector3 m_look;
	CVector3 m_up;					//�r���[�s��̐ݒ�ɕK�v�ȕϐ�


	//============================================================
	// �������e���s���ꍇ�̕ϐ�
	//============================================================
	float m_fovy	= 0.0f;					//�J�����c�����̉�p
	float m_aspect	= 0.0f;					//�c��1�Ƃ������̔䗦
	
	//============================================================
	// ���s���e���s���ꍇ�̕ϐ�
	//============================================================
	bool m_isOrtho		= false;		//���s���e���s����
	float m_ViewWidth	= 0.0f;
	float m_ViewHeight	= 0.0f; 
	
	//============================================================
	// ���ʂŎg���ϐ�
	//============================================================
	float m_near = 0.0f;					//�ǂ�����f����
	float m_far = 0.0f;					//�ǂ��܂ŉf����
	
private:
	PlaneCollider m_Planes[6];		//���쐍��Ŏg����
};


#endif //CAMERABASE