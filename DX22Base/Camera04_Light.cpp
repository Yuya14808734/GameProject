#include "Camera04_Light.h"


CameraLight::CameraLight()
	:m_pLight(nullptr),
	m_pConstBuffer(nullptr)
{
}

CameraLight::~CameraLight()
{
}

void CameraLight::Init()
{
	m_isOrtho = true;

	m_pConstBuffer = new ConstantBuffer();
	m_pConstBuffer->Create(sizeof(float) * 4);
}

void CameraLight::Uninit()
{

}

void CameraLight::Update()
{

}

void CameraLight::ChangeInit()
{
	if (m_pLight == nullptr)
	{
		return;
	}

	SetParameter();
}

void CameraLight::ChangeUninit()
{
}

void CameraLight::SetLight(LightObject* pLight)
{
	m_pLight = pLight;

	if (m_pLight == nullptr)
	{
		return;
	}

	SetParameter();
}

void CameraLight::WriteConstBuffer()
{
	SetParameter();

	m_pConstBuffer->Write(m_LightPlane);
	m_pConstBuffer->BindPS(0);
}

void CameraLight::SetParameter()
{
	m_pos = m_pLight->GetPos();
	m_look = m_pos + m_pLight->GetDirection();
	m_up = CVector3(0.0f, 1.0f, 0.0f);

	CVector3 NormalDirect = m_pLight->GetDirection().normalize();

	float ax = NormalDirect.x * m_pos.x;
	float by = NormalDirect.y * m_pos.y;
	float cz = NormalDirect.z * m_pos.z;

	m_LightPlane[0] = NormalDirect.x;
	m_LightPlane[1] = NormalDirect.y;
	m_LightPlane[2] = NormalDirect.z;
	m_LightPlane[3] = (ax + by + cz) * -1.0f;
}
