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
	/*メンバ変数を元にプロジェクション行列を作成し、転置済みの行列として戻り値を返す*/
	DirectX::XMVECTOR EyePos = DirectX::XMVectorSet(m_pos.x, m_pos.y, m_pos.z, 0.0f);//カメラ位置
	DirectX::XMVECTOR FocusPos = DirectX::XMVectorSet(m_look.x, m_look.y, m_look.z, 0.0f);//カメラ注点
	DirectX::XMVECTOR UpDirection = DirectX::XMVectorSet(m_up.x, m_up.y, m_up.z, 0.0f);//カメラ上方向
	view = DirectX::XMMatrixLookAtLH(EyePos, FocusPos, UpDirection);//ビュー座標系行列の作成
	view = XMMatrixTranspose(view);//転置

	DirectX::XMStoreFloat4x4(&mat, view);//最適化

	return mat;
}

DirectX::XMFLOAT4X4 CameraBase::GetProjectionMatrix()
{
	DirectX::XMFLOAT4X4 mat;
	DirectX::XMMATRIX proj;
	/*メンバー変数を元にプロジェクション行列を作成し、転置済みの行列として戻り値を返す*/
	float FovAngleY = DirectX::XMConvertToRadians(m_fovy);//カメラ縦方向の画角
	float AspectRatio = m_aspect;//縦を1とした横の比率
	float NearZ = m_near;//どこから映すか
	float FarZ = m_far;//どこまで映すか
	proj = DirectX::XMMatrixPerspectiveFovLH(FovAngleY, AspectRatio, NearZ, FarZ);//プロジェクション座標系行列の作成
	proj = XMMatrixTranspose(proj);//転置
	DirectX::XMStoreFloat4x4(&mat, proj);//最適化

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
	//カメラの縦の角度を出す
	float RotateRadianAxisX = DirectX::XMConvertToRadians(m_fovy * 0.5f);
	
	//=====<縦と奥行きで縦の三角形を作る>=====
	//縦の角度に対した高さをだす
	float Height = sinf(RotateRadianAxisX);
	//縦の角度に大した奥行の長さを出す
	float DepthLength = cosf(RotateRadianAxisX);
	
	//=====<横での長さを出して横でも三角形を作リ角度を出す>=====
	//縦の長さに割合をかけて横の長さを出す
	float Width = Height * m_aspect;
	//縦の長さと横の長さで角度を出す
	float RotateRadianAxisY = atan2f(Width, DepthLength);

	//上の面
	CVector3 TopPlaneVector = CQuaternion::RadianAxis(rightVec, -RotateRadianAxisX)
		.RotateVector(upVec * -1.0f);
	m_Planes[0].setplane(m_pos, TopPlaneVector);
	 
	//下の面
	CVector3 BottomPlaneVector = CQuaternion::RadianAxis(rightVec, RotateRadianAxisX)
		.RotateVector(upVec);
	m_Planes[1].setplane(m_pos, BottomPlaneVector);

	//左の面
	CVector3 LeftPlaneVector = CQuaternion::RadianAxis(upVec, -RotateRadianAxisY)
		.RotateVector(rightVec);
	m_Planes[2].setplane(m_pos, LeftPlaneVector);

	//右の面
	CVector3 RightPlaneVector = CQuaternion::RadianAxis(upVec, RotateRadianAxisY)
		.RotateVector(rightVec * -1.0f);
	m_Planes[3].setplane(m_pos, RightPlaneVector);

	//手前の面
	m_Planes[4].setplane(m_pos + fowardVec * m_near, fowardVec);

	//後ろの面
	m_Planes[5].setplane(m_pos + fowardVec * m_far, -fowardVec);
}

bool CameraBase::CheckInObject(const CVector3& Point, float Radius)
{
	for (int i = 0; i < 6; i++)
	{
		float Length = m_Planes[i].LengthPoint(Point);

		//平面との距離が半径のマイナスより小さければ見えないことになる
		if (Length < -Radius)
		{
			return false;
		}
	}

	return true;
}
