#include "Camera04_Light.h"


CameraLight::CameraLight()
	:m_pLight(nullptr)
{
}

CameraLight::~CameraLight()
{
}

void CameraLight::Init()
{
	m_isOrtho = true;

	m_ViewWidth = m_ViewHeight = 25.0f;
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

void CameraLight::SetParameter()
{
	m_pos = m_pLight->GetPos();
	m_look = m_pos + m_pLight->GetDirection();
	m_up = CVector3(0.0f, 1.0f, 0.0f);
}
