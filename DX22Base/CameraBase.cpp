#include "CameraBase.h"

CameraBase::CameraBase()
	:m_pos(0.0f, 0.0f, 0.0f), m_look(0.0f, 0.0f, 1.0f), m_up(0.0f, 1.0f, 0.0f),
	m_fovy(60.0f), m_aspect(16.0f / 9.0f), m_near(0.2f), m_far(100.0f)
{

};

CameraBase::~CameraBase()
{

}

void CameraBase::Init()
{
}

void CameraBase::Uninit()
{
}

void CameraBase::ChangeInit()
{

}

void CameraBase::ChangeUninit()
{

};

DirectX::XMFLOAT4X4 CameraBase::GetViewMatrix()
{
	DirectX::XMFLOAT4X4 mat;
	DirectX::XMMATRIX view;
	/*�����o�ϐ������Ƀv���W�F�N�V�����s����쐬���A�]�u�ς݂̍s��Ƃ��Ė߂�l��Ԃ�*/
	DirectX::XMVECTOR EyePos = DirectX::XMVectorSet(m_pos.x, m_pos.y, m_pos.z, 0.0f);//�J�����ʒu
	DirectX::XMVECTOR FocusPos = DirectX::XMVectorSet(m_look.x, m_look.y, m_look.z, 0.0f);//�J�������_
	DirectX::XMVECTOR UpDirection = DirectX::XMVectorSet(m_up.x, m_up.y, m_up.z, 0.0f);//�J���������
	view = DirectX::XMMatrixLookAtLH(EyePos, FocusPos, UpDirection);//�r���[���W�n�s��̍쐬
	view = XMMatrixTranspose(view);//�]�u

	DirectX::XMStoreFloat4x4(&mat, view);//�œK��

	return mat;
}

DirectX::XMFLOAT4X4 CameraBase::GetProjectionMatrix()
{
	DirectX::XMFLOAT4X4 mat;
	DirectX::XMMATRIX proj;
	/*�����o�[�ϐ������Ƀv���W�F�N�V�����s����쐬���A�]�u�ς݂̍s��Ƃ��Ė߂�l��Ԃ�*/
	float FovAngleY = DirectX::XMConvertToRadians(m_fovy);//�J�����c�����̉�p
	float AspectRatio = m_aspect;//�c��1�Ƃ������̔䗦
	float NearZ = m_near;//�ǂ�����f����
	float FarZ = m_far;//�ǂ��܂ŉf����
	proj = DirectX::XMMatrixPerspectiveFovLH(FovAngleY, AspectRatio, NearZ, FarZ);//�v���W�F�N�V�������W�n�s��̍쐬
	proj = XMMatrixTranspose(proj);//�]�u
	DirectX::XMStoreFloat4x4(&mat, proj);//�œK��

	return mat;
}

void CameraBase::SetPos(const CVector3 & pos)
{
	m_pos = pos;
}

void CameraBase::SetPos(const DirectX::XMFLOAT3 & pos)
{
	m_pos.f = pos;
}

void CameraBase::SetLookPos(const CVector3 & pos)
{
	m_look = pos;
}

void CameraBase::SetLookPos(const DirectX::XMFLOAT3 & pos)
{
	m_look.f = pos;
}

const CVector3& CameraBase::GetPos()
{
	return m_pos;
}

const CVector3& CameraBase::GetLookPos()
{
	return m_look;
}

DirectX::XMFLOAT3 CameraBase::GetPos_xmfloat()
{
	return m_pos.f;
}


DirectX::XMFLOAT3 CameraBase::GetLook_xmfloat()
{
	return m_look.f;
}

float CameraBase::GetFovAngle()
{
	return m_fovy;
}

float CameraBase::GetAspect()
{
	return m_aspect;
}


float CameraBase::GetNearLength()
{
	return m_near;
}


float CameraBase::GetFarLength()
{
	return m_far;
}

CVector3 CameraBase::GetRightVector()
{
	return m_up.cross(m_look).normalize();
}

CVector3 CameraBase::GetUpVector()
{
	return m_up;
}

void CameraBase::CreateEnclosingPlane()
{
	CVector3 rightVec = GetRightVector();
	CVector3 upVec = GetUpVector();
	float RotateRadianX = DirectX::XMConvertToRadians(m_fovy * 0.5f * m_aspect);
	float RotateRadianY = DirectX::XMConvertToRadians(m_fovy * 0.5f);

	//��̖�
	CVector3 TopPlaneVector = CQuaternion::RadianAxis(rightVec, -RotateRadianX).RotateVector(upVec * -1.0f);

	//���̖�
	CVector3 BottomPlaneVector = CQuaternion::RadianAxis(rightVec, RotateRadianX).RotateVector(upVec);

	//���̖�
	CVector3 LeftPlaneVector = CQuaternion::RadianAxis(upVec, -RotateRadianY).RotateVector(rightVec);

	//�E�̖�
	CVector3 RightPlaneVector = CQuaternion::RadianAxis(upVec, RotateRadianX).RotateVector(rightVec * -1.0f);

}
