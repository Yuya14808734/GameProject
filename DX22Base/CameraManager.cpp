#include "CameraManager.h"

CameraManager& CameraManager::GetInstance()
{
	static CameraManager instance;

	return instance;
}

CameraManager::CameraManager()
	:m_pNowCamera(nullptr)
{

}

CameraManager::~CameraManager()
{

}

void CameraManager::CameraUpdate()
{
	if (m_pNowCamera != nullptr)
	{
		m_pNowCamera->Update();
	}
}

CameraBase* CameraManager::GetSceneCamera() const
{
	return m_pNowCamera;
}

void CameraManager::SetSceneCamera(std::string CameraName)
{
	//�J���������邩��T��
	std::map<std::string, CameraBase*>::iterator it = m_CameraList.find(CameraName);

	if (it == m_CameraList.end())
	{
		return;
	}

	if (m_pNowCamera != nullptr)
	{
		m_pNowCamera->Uninit();
	}

	//����ΐݒ�
	m_pNowCamera = m_CameraList[CameraName];
	m_pNowCamera->Init();
}

CameraBase* CameraManager::GetCamera(std::string CameraName)
{
	//�J���������邩��T��
	const std::map<std::string, CameraBase*>::iterator it = m_CameraList.find(CameraName);

	if (it == m_CameraList.end())
	{
		return nullptr;
	}

	return (*it).second;
}

CameraBase ** CameraManager::GetCameraPointer()
{
	return &m_pNowCamera;
}

void CameraManager::DestroyCamera(std::string CameraName, bool MemoryDelete)
{
	//�J���������邩��T��
	std::map<std::string, CameraBase*>::iterator it = m_CameraList.find(CameraName);

	if (it == m_CameraList.end())
	{
		return;
	}

	if (MemoryDelete)
	{
		if ((*it).second == m_pNowCamera)
		{
			m_pNowCamera = nullptr;
		}

		delete (*it).second;
	}

	//����΍폜
	m_CameraList.erase(it);
}

void CameraManager::DestroyAllCamera(bool MemoryDelete)
{
	//���ׂẴJ�������폜
	if (MemoryDelete)
	{
		for (std::pair<std::string, CameraBase*> camera : m_CameraList)
		{
			delete camera.second;
		}
	}

	m_CameraList.clear();

	m_pNowCamera = nullptr;
}
