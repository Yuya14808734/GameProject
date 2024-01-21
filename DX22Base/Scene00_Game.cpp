#include "Scene00_Game.h"
#include "CameraManager.h"
#include "Camera00_Debug.h"
#include "Camera01_Game.h"
#include "Camera03_GameStart.h"
#include "ModelDrawer.h"
#include "Geometory.h"
#include "Input.h"
#include "Stage_00.h"
#include "Character_00.h"
#include "Select00_Character.h"
#include "Scene01_Select.h"
#include "Character_State.h"
#include "Character_Attack.h"

#include "SceneGame_StartState.h"
#include "SceneGame_GamePlayState.h"
#include "SceneGame_EndState.h"


bool ColliderDraw = false;

void SceneGame::Init()
{
	//=====<�J�����̐���>=====
	CameraManager::GetInstance().CreateCamera<CameraGame>("GameCamera");
	CameraManager::GetInstance().CreateCamera<CameraGameStart>("GameStartCamera");
	CameraManager::GetInstance().SetSceneCamera("GameStartCamera");
	m_pGameCamera = static_cast<CameraGame*>(CameraManager::GetInstance().GetCamera("GameCamera"));
	CameraGameStart* pCameraGameStart = 
		static_cast<CameraGameStart*>(CameraManager::GetInstance().GetCamera("GameStartCamera"));

	//=====<�X�e�[�W�̍쐬>=====
	m_pStage = new Stage00();
	m_pStage->Stage_Init();

	//=====<�L�����N�^�[�̐���>=====
	Character::InitPlayerBit();
	
	//=====<�Z���N�g�V�[���őI�񂾃L�����N�^�[�̐���>=====
	//===<��l��>===
	Character* FirstCharacter = CreateCharacter(SceneSelect::GetFirstPlayerCharacter());
	m_pFirstController = SceneSelect::GetFirstPlayerController();
	m_pFirstController = m_pFirstController == nullptr ?
		&PlayerController::GetPlayerControllers()[0] : m_pFirstController;
	FirstCharacter->SetCharacterController(m_pFirstController);
	FirstCharacter->Character_Init();
	//===<��l��>===
	Character* SecondCharacter = CreateCharacter(SceneSelect::GetSecondPlayerCharacter());
	SecondCharacter->Character_Init();
	m_pSecondController = SceneSelect::GetSecondPlayerController();
	m_pSecondController = m_pSecondController == nullptr ?
		&PlayerController::GetPlayerControllers()[1] : m_pSecondController;
	SecondCharacter->SetCharacterController(m_pSecondController);
	
	//=====<UI�̃p�����[�^�̐ݒ�>=====
	m_GameStartCountUI.SetNumDraw(3);

	//=====<�w�i�摜�̐ݒ�>=====
	m_BackGround.SetTexture("Assets/BackGroundImage/BackGround00.png");
	m_BackGround.SetPos(CVector3(0.0f, 0.0f, 50.0f));
	m_BackGround.SetSize(CVector2(1200.0f,800.0f));
	m_BackGround.SetScale(CVector3::GetOne() * 0.2f);

	//=====<�e�I�u�W�F�N�g�ɓn�������I�u�W�F�N�g�|�C���^������Ȃ炱���ł���>=====
	for (Character* pCharacter : m_Characters)
	{
		pCharacter->SetStage(m_pStage);
	}

	m_pGameCamera->SetCharacter(&m_Characters);
	m_pGameCamera->SetStage(m_pStage);
	pCameraGameStart->SetCharacter(m_Characters);

	//=====<�Q�[���J�n�ɐݒ�>=====
	SetNextState(SceneGame::GAMESTATE::GAMESTART);
	ChangeNextState();
}

void SceneGame::Uninit()
{
	//=====<�X�e�[�g�̂̍폜>=====
	m_GameSceneStateContext.ReleaseAllState();

	//=====<�L�����N�^�[�̍폜>=====
	for (auto it = m_Characters.begin(); it != m_Characters.end();)
	{
		(*it)->Character_Uninit();
		delete (*it);
		it = m_Characters.erase(it);
	}

	//=====<�X�e�[�W�̍폜>=====
	m_pStage->Stage_Uninit();
	delete m_pStage;

	//=====<�J�����̍폜>=====
	CameraManager::GetInstance().DestroyCamera("GameStartCamera", true);
	CameraManager::GetInstance().DestroyCamera("GameCamera", true);
}

void SceneGame::Update()
{
	//�R���g���[���[�������ꂽ��Q�[�����I������
	if (!m_pFirstController->IsConnect() && !m_pSecondController->IsConnect())
	{
		//�R���g���[���[�������ꂽ
	}

	m_GameSceneStateContext.StateUpdate();

	ChangeNextState();
}

void SceneGame::Draw()
{
	m_BackGround.Draw();

	//=====<�����蔻��̕`��>=====
	if (IsKeyTrigger(VK_RETURN))
	{
		ColliderDraw = !ColliderDraw;
	}

	if (ColliderDraw)
	{
		m_pStage->StageColliderDraw();
		for (Character* CharacterCopy : m_Characters)
		{
			CharacterCopy->DrawCollider();

			//�L�����N�^�[���U�����Ă��Ȃ���Ύ��̃L�����N�^�[��
			if (static_cast<Character_State*>(CharacterCopy->GetStateContext()->GetNowState())
				->GetType() != Character_State::TYPE::ATTACK)
			{
				continue;
			}

			std::vector<Character::ATTACKPARAM>& attackVector
				= CharacterCopy->GetAttackCollider();

			for (Character::ATTACKPARAM& AttackCopy : attackVector)
			{
				if (!AttackCopy.m_Use)
				{
					continue;
				}
				AttackCopy.m_BoxCollider.DrawCollider();
			}

		}
	}

	m_GameSceneStateContext.StateDraw();

	
}

Character* SceneGame::CreateCharacter(int Num)
{
	return CreateCharacter(static_cast<SelectCharacterList::CHARACTER>(Num));
}

Character* SceneGame::CreateCharacter(SelectCharacterList::CHARACTER CharacterNum)
{
	switch (CharacterNum)
	{
	case SelectCharacterList::CHARACTER::UNITYCHAN:
		m_Characters.push_back(new Character_00());
		break;
	case SelectCharacterList::CHARACTER::NONE:
	case SelectCharacterList::CHARACTER::MAX:
		m_Characters.push_back(new Character_00());
		break;
	}

	auto it = m_Characters.end();
	it--;
	return (*it);
}

State* SceneGame::SetNextState(GAMESTATE NextState)
{
	switch (NextState)
	{
	case SceneGame::GAMESTATE::GAMESTART:
		m_GameSceneStateContext.SetNextState(new SceneGame_StartState());
		break;
	case SceneGame::GAMESTATE::GAMEPLAY:
		m_GameSceneStateContext.SetNextState(new SceneGame_PlayState());
		break;
	case SceneGame::GAMESTATE::GAMEEND:
		m_GameSceneStateContext.SetNextState(new SceneGame_EndState());
		break;
	}

	return m_GameSceneStateContext.GetNextState();
}

void SceneGame::ChangeNextState()
{
	if (m_GameSceneStateContext.GetNextState() != nullptr)
	{
		//�I������
		m_GameSceneStateContext.StateUninit();

		//���̃X�e�[�g�ɕύX
		m_GameSceneStateContext.ChangeNextState();

		//���̃X�e�[�g�̊e�ϐ���ݒ�
		SceneGame_BaseState* pState = static_cast<SceneGame_BaseState*>(m_GameSceneStateContext.GetNowState());
		pState->SetScene(this);
		pState->SetCharacters(&m_Characters);
		pState->SetStage(m_pStage);
		pState->SetGameCamera(m_pGameCamera);
		pState->SetBackGround(&m_BackGround);
		pState->SetStartCountUI(&m_GameStartCountUI);
		pState->SetEndTextUI(&m_GameEndTextUI);
		pState->SetStockCountUI(&m_StockCountUI);

		//����������
		m_GameSceneStateContext.StateInit();
	}
}