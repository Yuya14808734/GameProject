#pragma once
#include "CameraBase.h"
#include <string>
#include <map>

class CameraManager
{
public:
	static CameraManager& GetInstance();
	
private:
	CameraManager();
	~CameraManager();

public:
	void CameraUpdate();

	CameraBase* GetSceneCamera() const;									//���̃V�[���̃J�������擾
	void SetSceneCamera(std::string CameraName);						//���O�ŃJ������ݒ�
	template<typename T>
	T* CreateCamera(std::string CameraName);	//�J���������쐬
	CameraBase* GetCamera(std::string CameraName);						//���O�ŃJ�������擾
	CameraBase** GetCameraPointer();									//���̃J�����������Ă���|�C���^�[�ϐ��̃A�h���X�Ǝ擾
	void DestroyCamera(std::string CameraName,bool MemoryDelete);		//�J�����̍폜
	void DestroyAllCamera(bool MemoryDelete);							//�S�ẴJ�����̍폜
	void StopCamera();
	void ReStartCamera();

private:
	CameraBase* m_pNowCamera = nullptr;
	std::map<std::string, CameraBase*> m_CameraList;
	bool m_isUpdate = false;
};

//�J�����̍쐬
template<typename T>
T* CameraManager::CreateCamera(std::string CameraName)
{
	//�������O�̃J���������邩��T��
	std::map<std::string, CameraBase*>::iterator it = m_CameraList.find(CameraName);

	if (it != m_CameraList.end())
	{
		return nullptr;
	}

	T* returnValue = new T();

	//�Ȃ���Βǉ�����
	m_CameraList.insert(std::make_pair(CameraName, returnValue));

	//�J�����̏�����
	static_cast<CameraBase*>(returnValue)->Init();

	return returnValue;
}
