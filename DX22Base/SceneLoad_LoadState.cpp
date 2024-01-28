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
	//“Ç‚İ‚İ‚ªI‚í‚èŸ‘æ‰º‚ÌŠÖ”‚ğŒÄ‚Ô(–¢À‘•)
	CScene::SetScene<SceneGame>();
}

void SceneLoad_LoadState::Draw()
{
	//===== < ‰æ–Ê•`‰æ>=====
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
