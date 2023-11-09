#include "Scene.h"

CScene* CScene::m_pNowScene = nullptr;
CScene* CScene::m_pNextScene = nullptr;

void CScene::Init()
{

}
void CScene::Uninit()
{

}
void CScene::Update()
{

}
void CScene::Draw()
{

}

CScene * CScene::GetScene()
{
	return m_pNowScene;
}

void CScene::SceneChange()
{
	//���̃V�[�����ݒ肳��Ă��Ȃ����
	if (m_pNextScene == nullptr)
	{
		//�ύX�Ȃ�
		return;
	}

	//���̃V�[���������
	if (m_pNowScene != nullptr)
	{
		m_pNowScene->Uninit();
		delete m_pNowScene;
	}

	m_pNowScene = m_pNextScene;
	m_pNowScene->Init();

	m_pNextScene = nullptr;
}

void CScene::DestroyScene()
{
	if (m_pNowScene == nullptr)
	{
		return;
	}

	delete m_pNowScene;
}