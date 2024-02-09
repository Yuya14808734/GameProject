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
	//�J���������邩��T��
	std::map<std::string, CameraBase*>::iterator it = m_CameraList.find(CameraName);

	//�J����������������ύX�Ȃ�
	if (it == m_CameraList.end())
	{
		return;
	}

	//���̃J�������ݒ肵�Ă����
	if (m_pNowCamera != nullptr)
	{
		m_pNowCamera->ChangeUninit();
	}

	//����ΐݒ�
	m_pNowCamera = m_CameraList[CameraName];
	m_pNowCamera->ChangeInit();
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

	//�I���������s��
	(*it).second->Uninit();

	if (MemoryDelete)
	{
		//�����ݒ肵�Ă���J�����̏ꍇ
		if ((*it).second == m_pNowCamera)
		{
			m_pNowCamera = nullptr;
		}

		delete (*it).second;
	}

	//�z�񂩂�폜
	m_CameraList.erase(it);
}

void CameraManager::DestroyAllCamera(bool MemoryDelete)
{
	//���ׂẴJ�������폜
	if (MemoryDelete)
	{
		for (std::pair<std::string, CameraBase*> camera : m_CameraList)
		{
			camera.second->Uninit();
			delete camera.second;
		}
	}

	//�������炷�ׂăN���A
	m_CameraList.clear();

	//�ݒ肵�Ă��Ȃ��Ɛݒ�
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
