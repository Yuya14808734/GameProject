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

	CameraBase* GetSceneCamera() const;									//今のシーンのカメラを取得
	void SetSceneCamera(std::string CameraName);						//名前でカメラを設定
	bool CreateCamera(CameraBase* pCamera, std::string CameraName);	//カメラ情報を作成
	CameraBase* GetCamera(std::string CameraName);						//名前でカメラを取得
	CameraBase** GetCameraPointer();									//今のカメラを持っているポインター変数のアドレスと取得
	void DestroyCamera(std::string CameraName,bool MemoryDelete);		//カメラの削除
	void DestroyAllCamera(bool MemoryDelete);							//全てのカメラの削除

private:
	CameraBase* m_pNowCamera = nullptr;
	std::map<std::string, CameraBase*> m_CameraList;

};