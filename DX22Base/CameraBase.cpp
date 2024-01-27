#include "CameraBase.h"
#include "Geometory.h"

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
	CVector3 lookVec = m_look - m_pos;
	return m_up.cross(lookVec).normalize();
}

CVector3 CameraBase::GetUpVector()
{
	return m_up;
}

void CameraBase::CreateViewingFrustum()
{
	CVector3 rightVec = GetRightVector();
	CVector3 upVec = GetUpVector();
	CVector3 fowardVec = m_look - m_pos;
	fowardVec = fowardVec.normalize();
	//�J�����̏c�̊p�x���o��
	float RotateRadianAxisX = DirectX::XMConvertToRadians(m_fovy * 0.5f);
	
	//=====<�c�Ɖ��s���ŏc�̎O�p�`�����>=====
	//�c�̊p�x�ɑ΂�������������
	float Height = sinf(RotateRadianAxisX);
	//�c�̊p�x�ɑ債�����s�̒������o��
	float DepthLength = cosf(RotateRadianAxisX);
	
	//=====<���ł̒������o���ĉ��ł��O�p�`���샊�p�x���o��>=====
	//�c�̒����Ɋ����������ĉ��̒������o��
	float Width = Height * m_aspect;
	//�c�̒����Ɖ��̒����Ŋp�x���o��
	float RotateRadianAxisY = atan2f(Width, DepthLength);

	//��̖�
	CVector3 TopPlaneVector = CQuaternion::RadianAxis(rightVec, -RotateRadianAxisX)
		.RotateVector(upVec * -1.0f);
	m_Planes[0].setplane(m_pos, TopPlaneVector);
	 
	//���̖�
	CVector3 BottomPlaneVector = CQuaternion::RadianAxis(rightVec, RotateRadianAxisX)
		.RotateVector(upVec);
	m_Planes[1].setplane(m_pos, BottomPlaneVector);

	//���̖�
	CVector3 LeftPlaneVector = CQuaternion::RadianAxis(upVec, -RotateRadianAxisY)
		.RotateVector(rightVec);
	m_Planes[2].setplane(m_pos, LeftPlaneVector);

	//�E�̖�
	CVector3 RightPlaneVector = CQuaternion::RadianAxis(upVec, RotateRadianAxisY)
		.RotateVector(rightVec * -1.0f);
	m_Planes[3].setplane(m_pos, RightPlaneVector);

	//��O�̖�
	m_Planes[4].setplane(m_pos + fowardVec * m_near, fowardVec);

	//���̖�
	m_Planes[5].setplane(m_pos + fowardVec * m_far, -fowardVec);
}

bool CameraBase::CheckInObject(const CVector3& Point, float Radius)
{
	for (int i = 0; i < 6; i++)
	{
		float Length = m_Planes[i].LengthPoint(Point);

		//���ʂƂ̋��������a�̃}�C�i�X��菬������Ό����Ȃ����ƂɂȂ�
		if (Length < -Radius)
		{
			return false;
		}
	}

	return true;
}
