#include "SceneLoad_PanelMoveState.h"
#include "Main.h"
#include "Scene01_Select.h"

void SceneLoad_PanelMoveState::Init()
{
	CVector2 WindowSize(
		static_cast<float>(GetAppWidth()),
		static_cast<float>(GetAppHeight())
	);

	//=====<キャラクターの画像を設定>=====
	(*m_pCharacterMovePanels)[0]->SetCharacter(SceneSelect::GetFirstPlayerCharacter());
	(*m_pCharacterMovePanels)[0]->SetPlayerNum(1);
	(*m_pCharacterMovePanels)[1]->SetCharacter(SceneSelect::GetSecondPlayerCharacter());
	(*m_pCharacterMovePanels)[1]->SetPlayerNum(2);

	float XPos[2] = { 0.25f, 0.75f,};
	float YPos[2][4] = {
		{0.2f,0.4f,0.6f,0.8f},
		{0.8f,0.6f,0.4f,0.2f},
	};

	for (int i = 0; i < 2; i++)
	{
		(*m_pCharacterMovePanels)[i]->SetFadePos(
			CVector3(WindowSize.x * XPos[i % 2], WindowSize.y * YPos[i % 2][0], 0.0f),
			CVector3(WindowSize.x * XPos[i % 2], WindowSize.y * YPos[i % 2][1], 0.0f),
			CVector3(WindowSize.x * XPos[i % 2], WindowSize.y * YPos[i % 2][2], 0.0f),
			CVector3(WindowSize.x * XPos[i % 2], WindowSize.y * YPos[i % 2][3], 0.0f)
		);

		(*m_pCharacterMovePanels)[i]->SetFadeTime(0.5f, 1.0f, 0.5f);
	}

	m_pVersusTextAnime->m_pos = WindowSize * 0.5f;
	m_pVersusTextAnime->SetLerpSize(CVector2::GetZero(), CVector2(400.0f, 105.0f));
	m_pVersusTextAnime->SetLerpTime(0.5f);
	m_pVersusTextAnime->StartFadeIn();

	m_FrameCount = 0;
	m_DrawPanelNum = 0;
}

void SceneLoad_PanelMoveState::Uninit()
{
}

void SceneLoad_PanelMoveState::Update()
{
	m_FrameCount++;

	if (m_FrameCount < 30)
	{
		float Percent = static_cast<float>(m_FrameCount) / 30.0f;
		m_pHideImage->m_color.w = 1.0f - (0.5f * Percent);
	}

	//30フレームごとにキャラクターのパネルを描画
	if (m_FrameCount % 30 == 0)
	{
		if (static_cast<int>((*m_pCharacterMovePanels).size()) > m_DrawPanelNum)
		{
			(*m_pCharacterMovePanels)[m_DrawPanelNum]->SetStartFade();
			m_DrawPanelNum++;
		}
	}

	//文字を小さくする
	if (m_FrameCount == 120)
	{
		m_pVersusTextAnime->StartFadeOut();
	}

	if (m_FrameCount == 180)
	{
		m_pScene->SetNextState(SceneLoad::LOADSTATE::CHARACTERDRAW);
	}

	for (VersusCharacterPanelMove* copy : (*m_pCharacterMovePanels))
	{
		copy->Update();
	}

	m_pVersusTextAnime->Update();
}

void SceneLoad_PanelMoveState::Draw()
{
	//===== < 画面描画>=====
	EnableDepth(false);

	m_pBackGround->Draw();

	m_pHideImage->Draw();

	for (VersusCharacterPanelMove* copy : (*m_pCharacterMovePanels))
	{
		copy->Draw();
	}

	m_pVersusTextAnime->Draw();

	EnableDepth(true);
}
