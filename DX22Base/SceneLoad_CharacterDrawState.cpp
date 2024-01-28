#include "SceneLoad_CharacterDrawState.h"
#include "Main.h"
#include "Scene01_Select.h"
#include "Scene01_Select.h"

void SceneLoad_CharacterDrawState::Init()
{
	CVector2 WindowSize(
		static_cast<float>(GetAppWidth()),
		static_cast<float>(GetAppHeight()));

	m_FrameCount = 0;

	(*m_pCharacterImages)[0]->SetAnimeTime(1.0f);
	(*m_pCharacterImages)[0]->SetLerpPos(
		CVector2(WindowSize.x * 1.5f, WindowSize.y * 0.6f),
		CVector2(WindowSize.x * 0.25f, WindowSize.y * 0.6f));
	(*m_pCharacterImages)[0]->StartAnimation();
	(*m_pCharacterImages)[0]->SetCharacterImage(SceneSelect::GetFirstPlayerCharacter());

	(*m_pCharacterImages)[1]->SetAnimeTime(1.0f);
	(*m_pCharacterImages)[1]->SetLerpPos(
		CVector2(WindowSize.x * -0.5f, WindowSize.y * 0.6f),
		CVector2(WindowSize.x * 0.75f, WindowSize.y * 0.6f));
	(*m_pCharacterImages)[1]->StartAnimation();
	(*m_pCharacterImages)[1]->SetCharacterImage(SceneSelect::GetSecondPlayerCharacter());

	m_pVersusIconImage->SetLerpSize(2.0f, 1.3f);
	m_pVersusIconImage->SetLerpTime(1.0f);
}

void SceneLoad_CharacterDrawState::Uninit()
{
}

void SceneLoad_CharacterDrawState::Update()
{
	m_FrameCount++;

	if (m_FrameCount < 30)
	{
		float Percent = 1.0f - (static_cast<float>(m_FrameCount) / 30.0f);
		m_pHideImage->m_color.w = (0.5f * Percent);
	}

	if (m_FrameCount == 60)
	{
		m_pVersusIconImage->StartFadeIn();
	}

	if (m_FrameCount == 150)
	{
		m_pScene->SetNextState(SceneLoad::LOADSTATE::LOAD);
	}

	for (VersusCharacterImageMove* copy : (*m_pCharacterImages))
	{
		copy->Update();
	}

	m_pVersusIconImage->Update();
}

void SceneLoad_CharacterDrawState::Draw()
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
