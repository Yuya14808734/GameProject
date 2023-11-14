//#pragma once
#ifndef SCENE_H
#define SCENE_H
#include "CameraBase.h"

class CScene
{
public:
	static CScene* GetScene();	//シーンの取得
	template<typename T>				
	static T* SetScene();				//次のシーンの設定
	static void SceneChange();			//次のシーンの切り替え
	static void DestroyScene();			//シーンの削除

private:
	static CScene* m_pNowScene;			//今のシーンの情報
	static CScene* m_pNextScene;		//次のシーンの情報

public :
	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();
};

template<typename T>
T* CScene::SetScene()
{
	T* returnValue = m_pNextScene = new T();

	//今のシーンが設定されていなければ
	if (m_pNowScene == nullptr)
	{
		SceneChange();
	}

	return returnValue;
}

#endif // !SCENE_H