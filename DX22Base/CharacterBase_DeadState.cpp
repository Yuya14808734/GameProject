#include "CharacterBase_DeadState.h"
#include "Scene00_Game.h"
#include "SceneGame_GamePlayState.h"
#include "Effect00_Dead.h"
#include "SoundManager.h"

void CharacterBase_DeadState::Init()
{
	m_ChangeStateCount = 0;	//�X�e�[�^�X��ς���܂ł̎��Ԃ��J�E���g����
	m_pCharacter->SetStock(m_pCharacter->GetStock() - 1);
	m_pCharacterParameter->MoveVector =
		m_pCharacterParameter->Velocity = CVector3::GetZero();

	SoundManager::PlaySE("Kill01");
	SoundManager::PlaySE("ShoutOfWay");

	//�Q�[���I�[�o�[��`�悷��̂ŃX�g�b�N�͕`�悵�Ȃ�
	if (m_pCharacter->GetStock() == 0)
	{
		return;
	}

	//�L�����N�^�[�̃X�g�b�N��`�悷��
	SceneGame* pGameScene = dynamic_cast<SceneGame*>(CScene::GetScene());
	
	if (pGameScene == nullptr) { return; }

	SceneGame_PlayState* pGamePlayState = 
		dynamic_cast<SceneGame_PlayState*>
		(pGameScene->GetStateContext()->GetNowState());

	if (pGamePlayState == nullptr) { return; }

	pGamePlayState->DrawCharacterStock();
}

void CharacterBase_DeadState::Uninit()
{
	m_ChangeStateCount = 0;

	//�L�����N�^�[�ŏ��������Ȃ��Ƃ����Ȃ����̂�������
	m_pCharacter->SetDamage(0.0f);

}

void CharacterBase_DeadState::Update()
{
	m_ChangeStateCount++;

	if (m_ChangeStateCount > 30)
	{
		if (m_pCharacter->GetStock() > 0)
		{
			//�܂��X�g�b�N������ꍇ
			m_pCharacter->SetNextState(Character::STATE::State_Respawn);
			m_pCharacter->SetCheckDead(true);
		}
		else
		{
			//�X�g�b�N���Ȃ��ꍇ
			m_pCharacter->SetNextState(Character::STATE::State_GameOver);
		}
	}
}