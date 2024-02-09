#include "CameraManager.h"

CameraManager& CameraManager::GetInstance()
{
	static CameraManager instance;

	return instance;
}

CameraManager::CameraManager()
	:m_pNowCamera(nullptr)
	, m_isUpdate(true)
{

}

CameraManager::~CameraManager()
{

}

void CameraManager::CameraUpdate()
{
	if (!m_isUpdate)
	{ return; }

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
	//カメラがあるかを探す
	std::map<std::string, CameraBase*>::iterator it = m_CameraList.find(CameraName);

	//カメラが無かったら変更なし
	if (it == m_CameraList.end())
	{
		return;
	}

	//今のカメラが設定していれば
	if (m_pNowCamera != nullptr)
	{
		m_pNowCamera->ChangeUninit();
	}

	//あれば設定
	m_pNowCamera = m_CameraList[CameraName];
	m_pNowCamera->ChangeInit();
}

CameraBase* CameraManager::GetCamera(std::string CameraName)
{
	//カメラがあるかを探す
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
	//カメラがあるかを探す
	std::map<std::string, CameraBase*>::iterator it = m_CameraList.find(CameraName);

	if (it == m_CameraList.end())
	{
		return;
	}

	//終了処理を行う
	(*it).second->Uninit();

	if (MemoryDelete)
	{
		//もし設定しているカメラの場合
		if ((*it).second == m_pNowCamera)
		{
			m_pNowCamera = nullptr;
		}

		delete (*it).second;
	}

	//配列から削除
	m_CameraList.erase(it);
}

void CameraManager::DestroyAllCamera(bool MemoryDelete)
{
	//すべてのカメラを削除
	if (MemoryDelete)
	{
		for (std::pair<std::string, CameraBase*> camera : m_CameraList)
		{
			camera.second->Uninit();
			delete camera.second;
		}
	}

	//消したらすべてクリア
	m_CameraList.clear();

	//設定していないと設定
	m_pNowCamera = nullptr;
}

void CameraManager::StopCamera()
{
	m_isUpdate = false;
}

void CameraManager::ReStartCamera()
{
	m_isUpdate = true;
}
