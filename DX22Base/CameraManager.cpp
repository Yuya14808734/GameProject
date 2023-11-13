#include "CameraManager.h"

CameraManger* CameraManger::Instance = nullptr;

CameraManger* CameraManger::GetInstance()
{
	if (Instance == nullptr)
	{
		Instance = new CameraManger();
	}

	return Instance;
}

CameraManger::CameraManger()
{

}
CameraManger::~CameraManger()
{

}

CameraBase* CameraManger::GetSceneCamera()
{
	return m_pNowCamera;
}

void CameraManger::SetSceneCamera(CameraBase * pCamera)
{

}

void CameraManger::AddCamera(CameraBase * pCamera)
{
}

CameraBase ** CameraManger::GetCameraPointer()
{
	return &m_pNowCamera;
}
