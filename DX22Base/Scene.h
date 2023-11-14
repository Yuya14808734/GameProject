//#pragma once
#ifndef SCENE_H
#define SCENE_H
#include "CameraBase.h"

class CScene
{
public:
	static CScene* GetScene();	//�V�[���̎擾
	template<typename T>				
	static T* SetScene();				//���̃V�[���̐ݒ�
	static void SceneChange();			//���̃V�[���̐؂�ւ�
	static void DestroyScene();			//�V�[���̍폜

private:
	static CScene* m_pNowScene;			//���̃V�[���̏��
	static CScene* m_pNextScene;		//���̃V�[���̏��

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

	//���̃V�[�����ݒ肳��Ă��Ȃ����
	if (m_pNowScene == nullptr)
	{
		SceneChange();
	}

	return returnValue;
}

#endif // !SCENE_H