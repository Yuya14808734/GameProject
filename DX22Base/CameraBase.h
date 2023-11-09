//#pragma once
#ifndef CAMERABASE
#define CAMERABASE
#include <DirectXMath.h>

//�}�N��
#define PI (3.141592f)
#define Angle_To_Radion(Angle) (Angle * PI / 180.0f)


class CameraBase {
public :
	CameraBase()
		:m_pos(0.0f, 0.0f, -3.0f), m_look(0.0f, 0.0f, 0.0f), m_up(0.0f, 1.0f, 0.0f),
		m_fovy(80.0f), m_aspect(16.0f / 9.0f), m_near(0.2f), m_far(1000.0f)
	{};

	virtual ~CameraBase() {}
	virtual void Update() = 0;
	DirectX::XMFLOAT4X4 GetViewMatrix()
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

	DirectX::XMFLOAT4X4 GetProjectionMatrix()
	{
		DirectX::XMFLOAT4X4 mat;
		DirectX::XMMATRIX proj;
		/*�����o�[�ϐ������Ƀv���W�F�N�V�����s����쐬���A�]�u�ς݂̍s��Ƃ��Ė߂�l��Ԃ�*/
		float FovAngleY = Angle_To_Radion(m_fovy);//�J�����c�����̉�p
		float AspectRatio = m_aspect;//�c��1�Ƃ������̔䗦
		float NearZ = m_near;//�ǂ�����f����
		float FarZ = m_far;//�ǂ��܂ŉf����
		proj = DirectX::XMMatrixPerspectiveFovLH(FovAngleY, AspectRatio, NearZ, FarZ);//�v���W�F�N�V�������W�n�s��̍쐬
		proj = XMMatrixTranspose(proj);//�]�u
		DirectX::XMStoreFloat4x4(&mat, proj);//�œK��

		return mat;
	}

	DirectX::XMFLOAT3 GetPos()
	{
		return m_pos;
	}

	DirectX::XMFLOAT3 GetLook()
	{
		return m_look;
	}

private:

protected:
	DirectX::XMFLOAT3 m_pos, m_look, m_up;	//�r���[�s��̐ݒ�ɕK�v�ȕϐ�
	float m_fovy, m_aspect, m_near, m_far;	//�v���W�F�N�V�����s��̐ݒ�ɕK�v�ȕϐ�
};


#endif //CAMERABASE