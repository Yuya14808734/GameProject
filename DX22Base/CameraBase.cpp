#include "CameraBase.h"
#include "Geometory.h"
#include "Main.h"

CameraBase::CameraBase()
	:m_pos(0.0f, 0.0f, 0.0f), m_look(0.0f, 0.0f, 1.0f), m_up(0.0f, 1.0f, 0.0f),
	m_fovy(60.0f), m_aspect(16.0f / 9.0f),
	m_isOrtho(false), m_ViewWidth(10.0f), m_ViewHeight(10.0f),
	m_near(0.2f), m_far(100.0f)
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

	DirectX::XMStoreFloat4x4(&mat, 
		DirectX::XMMatrixTranspose(GetViewMatrix_TypeXMMAXRIX()));//最適化

	return mat;
}

DirectX::XMFLOAT4X4 CameraBase::GetProjectionMatrix()
{
	DirectX::XMFLOAT4X4 mat;
	
	DirectX::XMStoreFloat4x4(&mat, 
		DirectX::XMMatrixTranspose(GetProjectionMatrix_TypeXMMAXRIX()));//最適化	

	return mat;
}

DirectX::XMMATRIX CameraBase::GetViewMatrix_TypeXMMAXRIX()
{
	DirectX::XMMATRIX view;
	/*メンバ変数を元にプロジェクション行列を作成し、転置済みの行列として戻り値を返す*/
	view = DirectX::XMMatrixLookAtLH(
		DirectX::XMVectorSet(m_pos.x, m_pos.y, m_pos.z, 0.0f), 
		DirectX::XMVectorSet(m_look.x, m_look.y, m_look.z, 0.0f), 
		DirectX::XMVectorSet(m_up.x, m_up.y, m_up.z, 0.0f));

	return view;
}

DirectX::XMMATRIX CameraBase::GetProjectionMatrix_TypeXMMAXRIX()
{
	DirectX::XMMATRIX proj;

	if (!m_isOrtho)
	{
		//========================================================================
		// 透視投影を行う
		//========================================================================

		/*メンバー変数を元にプロジェクション行列を作成し、転置済みの行列として戻り値を返す*/
		float FovAngleY = DirectX::XMConvertToRadians(m_fovy);//カメラ縦方向の画角
		proj = DirectX::XMMatrixPerspectiveFovLH(FovAngleY, m_aspect, m_near, m_far);//プロジェクション座標系行列の作成
	}
	else
	{
		//========================================================================
		// 平行投影を行う
		//========================================================================

		proj = DirectX::XMMatrixOrthographicLH(m_ViewHeight, m_ViewWidth, m_near, m_far);
	}

	return proj;
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

	//カメラの右、上、前ベクトルを取得
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

CVector2 CameraBase::ChangeScreenPos(const CVector3& Pos3D)
{
	CVector2 ScreenSize(
	static_cast<float>(GetAppWidth()),
	static_cast<float>(GetAppHeight()));

	//変数を作成する
	DirectX::XMVECTOR XMVEC_WorldPos = DirectX::XMLoadFloat3(&Pos3D.f);

	//ビューマトリクスルの作成
	DirectX::XMVECTOR XMVEC_CamPos	= DirectX::XMLoadFloat3(&m_pos.f);
	DirectX::XMVECTOR XMVEC_CamLook = DirectX::XMLoadFloat3(&m_look.f);
	DirectX::XMVECTOR XMVEC_ComUp	= DirectX::XMLoadFloat3(&m_up.f);

	DirectX::XMMATRIX XMMAT_View = DirectX::XMMatrixLookAtLH(
		XMVEC_CamPos,
		XMVEC_CamLook,
		XMVEC_ComUp
	);

	DirectX::XMMATRIX XMMAT_Projection =
		DirectX::XMMatrixPerspectiveFovLH(
		DirectX::XMConvertToRadians(m_fovy),
			ScreenSize.x / ScreenSize.y,
			m_near,m_far);

	XMVEC_WorldPos = DirectX::XMVector3Transform(XMVEC_WorldPos, XMMAT_View);
	XMVEC_WorldPos = DirectX::XMVector3Transform(XMVEC_WorldPos, XMMAT_Projection);

	float w = ScreenSize.x * 0.5f;
	float h = ScreenSize.y * 0.5f;

	DirectX::XMMATRIX XMMAT_ViewPort = {
		w,		0.0f,	0.0f,	0.0f,
		0.0f,	-h,		0.0f,	0.0f,
		0.0f,	0.0f,	1.0f,	0.0f,
		w,		h,		0.0f,	1.0f
	};

	DirectX::XMFLOAT3 XMF3_WorldPos;
	DirectX::XMStoreFloat3(&XMF3_WorldPos, XMVEC_WorldPos);

	//zで割って-1～1の範囲に収める
	//スクリーン変換
	DirectX::XMVECTOR XMVECTOR_2DPos = DirectX::XMVectorSet(
		XMF3_WorldPos.x / XMF3_WorldPos.z,
		XMF3_WorldPos.y / XMF3_WorldPos.z,
		1.0f, 1.0f);

	XMVECTOR_2DPos =
		DirectX::XMVector3Transform(XMVECTOR_2DPos, XMMAT_ViewPort);

	DirectX::XMFLOAT3 XMF3_2DPos;
	DirectX::XMStoreFloat3(&XMF3_2DPos, XMVECTOR_2DPos);

	return CVector2(XMF3_2DPos.x,XMF3_2DPos.y);
}

void CameraBase::SetOrtho(bool ortho)
{
	m_isOrtho = ortho;
}
