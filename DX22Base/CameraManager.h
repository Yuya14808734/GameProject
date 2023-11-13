#pragma once
#include "CameraBase.h"
#include <map>

class CameraManger
{
public:
	static CameraManger* GetInstance();
	
public:
	static CameraManger* Instance;
private:
	CameraManger();
	~CameraManger();

public:
	void CameraInit();
	void CameraUpdate();

	CameraBase* GetSceneCamera();
	void SetSceneCamera(CameraBase* pCamera);
	void AddCamera(CameraBase* pCamera,std::string& CameraName);
	CameraBase* GetCamera(std::string& CameraName);
	CameraBase** GetCameraPointer();
	void DestroyCamera(std::string& CameraName);
	void DestroyAllCamera();

private:
	CameraBase* m_pNowCamera = nullptr;
	std::map<std::string, CameraBase*> m_CameraList;

};