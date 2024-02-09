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

	m_pos = m_pLight->GetPos();
	m_look = m_pos + m_pLight->GetDirection();
	m_up = CVector3(0.0f, 1.0f, 0.0f);
}

void CameraLight::ChangeUninit()
{
}

void CameraLight::SetLight(LightObject* pLight)
{
	m_pLight = pLight;

	m_pos = m_pLight->GetPos();
	m_look = m_pos + m_pLight->GetDirection();
	m_up = CVector3(0.0f, 1.0f, 0.0f);
}
