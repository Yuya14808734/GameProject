#include "CameraManager.h"

CameraManger& CameraManger::GetInstance()
{
	static CameraManger instance;

	return instance;
}

CameraManger::CameraManger()
	:m_pNowCamera(nullptr)
{

}

CameraManger::~CameraManger()
{

}

void CameraManger::CameraUpdate()
{
	if (m_pNowCamera != nullptr)
	{
		m_pNowCamera->Update();
	}
}

CameraBase* CameraManger::GetSceneCamera() const
{
	return m_pNowCamera;
}

void CameraManger::SetSceneCamera(std::string& CameraName)
{
	//ƒJƒƒ‰‚ª‚ ‚é‚©‚ğ’T‚·
	std::map<std::string, CameraBase*>::iterator it = m_CameraList.find(CameraName);

	if (it == m_CameraList.end())
	{
		return;
	}

	//‚ ‚ê‚Îİ’è
	m_pNowCamera = m_CameraList[CameraName];
}

bool CameraManger::AddCamera(CameraBase* pCamera, std::string& CameraName)
{
	//ƒJƒƒ‰‚ª‚ ‚é‚©‚ğ’T‚·
	std::map<std::string, CameraBase*>::iterator it = m_CameraList.find(CameraName);

	if (it != m_CameraList.end())
	{
		if (pCamera != nullptr)
		{
			delete pCamera;
		}

		return false;
	}

	//‚È‚¯‚ê‚Î’Ç‰Á‚·‚é
	m_CameraList.insert(std::make_pair(CameraName, pCamera));

	return true;
}

CameraBase* CameraManger::GetCamera(std::string& CameraName)
{
	//ƒJƒƒ‰‚ª‚ ‚é‚©‚ğ’T‚·
	const std::map<std::string, CameraBase*>::iterator it = m_CameraList.find(CameraName);

	if (it == m_CameraList.end())
	{
		return nullptr;
	}

	return (*it).second;
}

CameraBase ** CameraManger::GetCameraPointer()
{
	return &m_pNowCamera;
}

void CameraManger::DestroyCamera(std::string& CameraName, bool MemoryDelete)
{
	//ƒJƒƒ‰‚ª‚ ‚é‚©‚ğ’T‚·
	std::map<std::string, CameraBase*>::iterator it = m_CameraList.find(CameraName);

	if (it == m_CameraList.end())
	{
		return;
	}

	if (MemoryDelete)
	{
		delete (*it).second;
	}

	//‚ ‚ê‚Îíœ
	m_CameraList.erase(it);
}

void CameraManger::DestroyAllCamera(bool MemoryDelete)
{
	//‚·‚×‚Ä‚ÌƒJƒƒ‰‚ğíœ
	if (MemoryDelete)
	{
		for (std::pair<std::string, CameraBase*> camera : m_CameraList)
		{
			delete camera.second;
		}
	}

	m_CameraList.clear();
}
