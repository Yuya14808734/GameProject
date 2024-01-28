#include "SceneLoad_LoadState.h"
#include "Scene00_Game.h"

void SceneLoad_LoadState::Init()
{
}

void SceneLoad_LoadState::Uninit()
{
}

void SceneLoad_LoadState::Update()
{
	//�ǂݍ��݂��I��莟�扺�̊֐����Ă�(������)
	CScene::SetScene<SceneGame>();
}

void SceneLoad_LoadState::Draw()
{
	//===== < ��ʕ`��>=====
	EnableDepth(false);

	m_pBackGround->Draw();

	m_pHideImage->Draw();

	for (VersusCharacterImageMove* copy : (*m_pCharacterImages))
	{
		copy->Draw();
	}

	m_pVersusIconImage->Draw();

	EnableDepth(true);
}
