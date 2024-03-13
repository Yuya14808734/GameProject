#include "Character00_DashState.h"
#include "Scene00_Game.h"
#include "Effect03_Dash.h"

void Character00_DashState::Init()
{
	CharacterBase_DashState::Init();

	//�Q�[���V�[���̐ݒ�
	m_pGameScene = static_cast<SceneGame*>(CScene::GetScene());

	m_pModelDrawer->PlayAnime("Dash", true);
	m_AnimeTime = 0.0f;

	m_pRightFootStepSE = SoundManager::GetSE("FootSteps01_Run");
	m_pLeftFootStepSE = SoundManager::GetSE("FootSteps02_Run");

	//�L�����N�^�[���_�b�V�������Ƃ��̃G�t�F�N�g
	EffectDash* pEffectDash = new EffectDash();
	pEffectDash->PlayDashEffect(m_pCharacterParameter->Pos,
		(m_pCharacter->GetLook() == Character::LOOKDIR::LEFT));
	m_pGameScene->GetEffectVector()->push_back(pEffectDash);
}

void Character00_DashState::Uninit()
{
	CharacterBase_DashState::Uninit();
}

void Character00_DashState::Update()
{
	Character::LOOKDIR OldLook = m_pCharacter->GetLook();

	CharacterBase_DashState::Update();

	Character::LOOKDIR NowLook = m_pCharacter->GetLook();

	if (OldLook != NowLook)
	{
		//�L�����N�^�[���_�b�V�������Ƃ��̃G�t�F�N�g
		EffectDash* pEffectDash = new EffectDash();
		pEffectDash->PlayDashEffect(m_pCharacterParameter->Pos,
			(NowLook == Character::LOOKDIR::LEFT));
		m_pGameScene->GetEffectVector()->push_back(pEffectDash);
	}

	float BeforeAnimeTime = m_AnimeTime;

	m_AnimeTime += 0.015f;

	//�����n�ʂɕt�����A�j���[�V�������Ԃ��܂����ł�����
	const float RightFootTime = 0.350f;
	const float LeftFootTime = 0.765f;

	if (BeforeAnimeTime < RightFootTime && m_AnimeTime >= RightFootTime)
	{
		m_pRightFootStepSE->Play();
	}

	if (BeforeAnimeTime < LeftFootTime && m_AnimeTime >= LeftFootTime)
	{
		m_pLeftFootStepSE->Play();
	}

	if (m_AnimeTime >= 0.833f)
	{
		m_AnimeTime -= 0.833f;
	}

	m_pModelDrawer->SetAnimeTime(m_AnimeTime);
}