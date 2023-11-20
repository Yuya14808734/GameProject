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
	bool CreateCamera(CameraBase* pCamera, std::string CameraName);	//�J���������쐬
	CameraBase* GetCamera(std::string CameraName);						//���O�ŃJ�������擾
	CameraBase** GetCameraPointer();									//���̃J�����������Ă���|�C���^�[�ϐ��̃A�h���X�Ǝ擾
	void DestroyCamera(std::string CameraName,bool MemoryDelete);		//�J�����̍폜
	void DestroyAllCamera(bool MemoryDelete);							//�S�ẴJ�����̍폜

private:
	CameraBase* m_pNowCamera = nullptr;
	std::map<std::string, CameraBase*> m_CameraList;

};