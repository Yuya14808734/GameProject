#pragma once
#include "CameraBase.h"
#include <string>
#include <map>

class CameraManger
{
public:
	static CameraManger& GetInstance();
	
private:
	CameraManger();
	~CameraManger();

public:
	void CameraUpdate();

	CameraBase* GetSceneCamera() const;
	void SetSceneCamera(std::string& CameraName);
	bool AddCamera(CameraBase* pCamera, std::string& CameraName);
	CameraBase* GetCamera(std::string& CameraName);
	CameraBase** GetCameraPointer();
	void DestroyCamera(std::string& CameraName,bool MemoryDelete);
	void DestroyAllCamera(bool MemoryDelete);

private:
	CameraBase* m_pNowCamera = nullptr;
	std::map<std::string, CameraBase*> m_CameraList;

};