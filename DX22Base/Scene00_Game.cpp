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
#include "Player_Controller.h"
#include "Select00_Character.h"
#include "Scene01_Select.h"

bool ColliderDraw = false;

void SceneGame::Init()
{
	//=====<�Q�[���J�n�ɐݒ�>=====
	m_GameState = GAMESTATE::GAMESTART;

	//=====<�J�����̐���>=====
	CameraManager::GetInstance().CreateCamera(new CameraGame(), "GameCamera");
	CameraGameStart* pCameraGameStart = new CameraGameStart();
	CameraManager::GetInstance().CreateCamera(pCameraGameStart, "GameStartCamera");
	CameraManager::GetInstance().SetSceneCamera("GameStartCamera");
	m_pGameCamera = static_cast<CameraGame*>(CameraManager::GetInstance().GetCamera("GameCamera"));

	//=====<�X�e�[�W�̍쐬>=====
	m_pStage = new Stage00();
	m_pStage->Stage_Init();

	//=====<�L�����N�^�[�̐���>=====
	Character::InitPlayerBit();
	
	//=====<�I�񂾃L�����N�^�[�̐���>=====
	Character* FirstCharacter = CreateCharacter(SceneSelect::GetFirstPlayerCharacter());
	PlayerController* pController = SceneSelect::GetFirstPlayerController();
	pController = pController == nullptr ? 
		&PlayerController::GetPlayerControllers()[0] : pController;
	FirstCharacter->SetCharacterController(pController);
	FirstCharacter->Character_Init();

	Character* SecondCharacter = CreateCharacter(SceneSelect::GetSecondPlayerCharacter());
	SecondCharacter->Character_Init();
	pController = SceneSelect::GetSecondPlayerController();
	pController = pController == nullptr ? 
		&PlayerController::GetPlayerControllers()[1] : pController;
	SecondCharacter->SetCharacterController(pController);
	
	//=====<�e�I�u�W�F�N�g�ɐݒ肷��I�u�W�F�N�g������Ȃ炱���ł���>=====
	for (Character* pCharacter : m_Characters)
	{
		pCharacter->SetStage(m_pStage);
	}

	m_pGameCamera->SetCharacter(&m_Characters);
	m_pGameCamera->SetStage(m_pStage);
	pCameraGameStart->SetCharacter(m_Characters);

	m_GameStartCountUI.SetNumDraw(3);
}

void SceneGame::Uninit()
{
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
	CameraManager::GetInstance().DestroyCamera("DebugCamera", true);
}

void SceneGame::Update()
{
	switch (m_GameState)
	{
	case SceneGame::GAMESTATE::GAMESTART:
		UpdateGameStart();
		break;
	case SceneGame::GAMESTATE::GAMEPLAY:
		UpdateGamePlay();
		break;
	case SceneGame::GAMESTATE::GAMEEND:
		UpdateGameEnd();
		break;
	}
}

void SceneGame::Draw()
{
	switch (m_GameState)
	{
	case SceneGame::GAMESTATE::GAMESTART:
		DrawGameStart();
		break;
	case SceneGame::GAMESTATE::GAMEPLAY:
		DrawGamePlay();
		break;
	case SceneGame::GAMESTATE::GAMEEND:
		DrawGameEnd();
		break;
	}
}

std::vector<Character*>& SceneGame::GetCharacter()
{
	return m_Characters;
}

Stage* SceneGame::GetStage()
{
	return m_pStage;
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
	case SelectCharacterList::CHARACTER::MAX:
		break;
	default:
		break;
	}

	auto it = m_Characters.end();
	it--;
	return (*it);
}

void SceneGame::UpdateGameStart()
{
	m_GameStartCountUI.Update();

	m_GameStartFrameCount++;

	if (m_GameStartFrameCount == 1 * 60)
	{
		m_GameStartCountUI.SetNumDraw(2);
	}

	if (m_GameStartFrameCount == 2 * 60)
	{
		m_GameStartCountUI.SetNumDraw(1);
	}

	if (m_GameStartFrameCount == 3 * 60)
	{
		m_GameStartCountUI.SetGoDraw(true);
		m_GameState = GAMESTATE::GAMEPLAY;
	}
}

void SceneGame::UpdateGamePlay()
{
	if (m_GameStartFrameCount < static_cast<int>(4.0f * 60.0f))
	{
		m_GameStartFrameCount++;
		m_GameStartCountUI.Update();
	}

	//=====<�L�����N�^�[�̃A�b�v�f�[�g>=====
	//�����ōU����ړ��Ȃǂ̃A�b�v�f�[�g���s��
	for (std::vector<Character*>::iterator it = m_Characters.begin();
		it != m_Characters.end(); it++)
	{
		(*it)->Character_Update();				//�L�����N�^�[�̃A�b�v�f�[�g���s��
		(*it)->Character_ColliderInit();		//�R���C�_�[�̏������������Ă��
												//(�����蔻����s���Ă��Ȃ��̂œ������Ă��Ȃ����Ƃɂ��鏈��)
	}

	//=====<�L�����N�^�[���m�̓����蔻��>=====
	Collision_Player_Player();

	//=====<�L�����N�^�[�̍U���̓����蔻��>=====
	Collision_Attack_Player();

	//=====<�L�����N�^�[�ƃX�e�[�W�̓����蔻��>=====
	Collision_Player_Stage();
}


void SceneGame::UpdateGameEnd()
{

}


void SceneGame::DrawGameStart()
{
	//=====<�X�e�[�W�̕`��>=====
	m_pStage->Stage_Draw();

	//=====<�L�����N�^�[�̕`��>=====
	for (Character* copy : m_Characters)
	{
		copy->Character_Draw();
	}

	//=====<UI�̕`��>=====
	EnableDepth(false);

	for (Character* copy : m_Characters)
	{
		copy->Character_UIDraw();
	}

	m_GameStartCountUI.Draw();

	EnableDepth(true);
}

void SceneGame::DrawGamePlay()
{
	//=====<�X�e�[�W�̕`��>=====
	m_pStage->Stage_Draw();

	//=====<�L�����N�^�[�̕`��>=====
	for (Character* copy : m_Characters)
	{
		copy->Character_Draw();
	}

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

			if (CharacterCopy->GetState() != Character::STATE::ATTACK)
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

	//=====<UI�̕`��>=====
	EnableDepth(false);

	for (Character* copy : m_Characters)
	{
		copy->Character_UIDraw();
	}

	if (m_GameStartFrameCount < static_cast<int>(4.0f * 60.0f))
	{
		m_GameStartCountUI.Draw();
	}

	EnableDepth(true);
}

void SceneGame::DrawGameEnd()
{
	
}

void SceneGame::Collision_Player_Player()
{
	//=====<�L�����N�^�[���m�̓����蔻��>=====

	//��l�ڂ̃L�����N�^�[��I��
	for (std::vector<Character*>::iterator it_first = m_Characters.begin();
		it_first != m_Characters.end(); it_first++)
	{
		//��l�ڂ̃L�����N�^�[���Q�[���I�[�o�[�̏ꍇ
		if ((*it_first)->GetState() == Character::STATE::GAMEOVER)
		{
			continue;
		}

		//��l�ڂ̃L�����N�^�[��I��(��l�ڂ̎��̃L�����N�^�[)
		std::vector<Character*>::iterator it_second = it_first + 1;
		for (; it_second != m_Characters.end(); it_second++)
		{
			//��l�ڂ̃L�����N�^�[���Q�[���I�[�o�[�̏ꍇ
			if ((*it_second)->GetState() == Character::STATE::GAMEOVER)
			{
				continue;
			}

			//�l�p�R���C�_�[�̎擾
			BoxCollider* pFirstCollider = (*it_first)->GetCharacterCollider();
			BoxCollider* pSecondCollider = (*it_second)->GetCharacterCollider();

			//�l�p���m�̓����蔻����s��
			if (!pFirstCollider->CollisionBox(*pSecondCollider))
			{
				//�������Ă��Ȃ��ꍇ
				continue;
			}

			//�߂荞�񂾕��𒵂˕Ԃ��Ă��
			float MaxDistanceX = (pFirstCollider->GetSize().x + pSecondCollider->GetSize().x) * 0.5f;
			float NowDistanceX = (pFirstCollider->GetColliderPos().x - pSecondCollider->GetColliderPos().x);
			float MinDistanceX = MaxDistanceX * 0.5f * 0.1f;
			float MoveX = (MaxDistanceX - fabsf(NowDistanceX)) * 0.02f + MinDistanceX;
			float FirstDirect = NowDistanceX < 0.0f ? -1.0f : 1.0f;
			(*it_first)->SetPos((*it_first)->GetPos() + CVector3::GetRight() * MoveX * FirstDirect);
			(*it_second)->SetPos((*it_second)->GetPos() + CVector3::GetRight() * MoveX * -FirstDirect);
		}
	}
}

void SceneGame::Collision_Player_Stage()
{
	//=====<�L�����N�^�[�ƃX�e�[�W�̓����蔻��>=====
	std::vector<BoxCollider>* pStageCollider = m_pStage->GetStageCollider();

	for (std::vector<Character*>::iterator it_Character = m_Characters.begin();
		it_Character != m_Characters.end(); it_Character++)
	{
		//�L�����N�^�[���Q�[���I�[�o�[���Ă����瓖���蔻����s��Ȃ�
		if ((*it_Character)->GetState() == Character::STATE::GAMEOVER)
		{
			continue;
		}

		BoxCollider* pCharacterCollider = (*it_Character)->GetCharacterCollider();

		//X�̈ړ������̓����蔻��
		for (std::vector<BoxCollider>::iterator it_StageCollider = pStageCollider->begin();
			it_StageCollider != pStageCollider->end(); it_StageCollider++)
		{
			CVector3 DiffPos = (*it_Character)->GetPos() - (*it_Character)->GetOldPos();		//�O�̈ʒu���獡�̈ʒu�܂ňړ������x�N�g��
			CVector3 HitSize = (pCharacterCollider->GetSize() + (*it_StageCollider).GetSize()) * 0.5f;
			float NowDistanceX = pCharacterCollider->GetBasePos().x - (*it_StageCollider).GetBasePos().x;
			float AbsNowDistanceX = fabsf(NowDistanceX);
			float OldDistanceY = (pCharacterCollider->GetBasePos().y - DiffPos.y) - (*it_StageCollider).GetBasePos().y;
			float AbsOldDistanceY = fabsf(OldDistanceY);
			float OldDistanceZ = (pCharacterCollider->GetBasePos().z - DiffPos.z) - (*it_StageCollider).GetBasePos().z;
			float AbsOldDistanceZ = fabsf(OldDistanceZ);

			//X�̈ړ��������ē������Ă�����
			if (AbsNowDistanceX < HitSize.x &&
				AbsOldDistanceY < HitSize.y &&
				AbsOldDistanceZ < HitSize.z)
			{
				CVector3 newPos = (*it_Character)->GetPos();
				float MoveDist = DiffPos.x < 0.0f ? HitSize.x : -HitSize.x;
				newPos.x = (*it_StageCollider).GetBasePos().x + MoveDist;
				(*it_Character)->SetPos(newPos);

				(*it_Character)->Character_HitWall();
			}
		}

		//Y�̈ړ������̓����蔻��
		for (std::vector<BoxCollider>::iterator it_Stage = pStageCollider->begin();
			it_Stage != pStageCollider->end(); it_Stage++)
		{
			CVector3 DiffPos = (*it_Character)->GetPos() - (*it_Character)->GetOldPos();		//�O�̈ʒu���獡�̈ʒu�܂ňړ������x�N�g��
			CVector3 HitSize = (pCharacterCollider->GetSize() + (*it_Stage).GetSize()) * 0.5f;
			float NowDistanceX = pCharacterCollider->GetBasePos().x - (*it_Stage).GetBasePos().x;
			float AbsNowDistanceX = fabsf(NowDistanceX);
			float NowDistanceY = pCharacterCollider->GetBasePos().y - (*it_Stage).GetBasePos().y;
			float AbsNowDistanceY = fabsf(NowDistanceY);
			float OldDistanceZ = (pCharacterCollider->GetBasePos().z - DiffPos.z) - (*it_Stage).GetBasePos().z;
			float AbsOldDistanceZ = fabsf(OldDistanceZ);

			//Y�̈ړ��������ē������Ă�����
			if (AbsNowDistanceX < HitSize.x &&
				AbsNowDistanceY < HitSize.y &&
				AbsOldDistanceZ < HitSize.z)
			{
				CVector3 newPos = (*it_Character)->GetPos();
				float MoveDist = DiffPos.y < 0.0f ?
					HitSize.y - (pCharacterCollider->GetType() == BoxCollider::BOXTYPE::FOOT ? (pCharacterCollider->GetSize().y * 0.5f) : 0.0f) :	//�ォ�炠������
					-HitSize.y;	//�����炠������
				newPos.y = (*it_Stage).GetBasePos().y + MoveDist;
				(*it_Character)->SetPos(newPos);

				//�ォ��ړ�������������ړ��������Ŕ���
				if (DiffPos.y < 0.0f)
				{
					(*it_Character)->Character_HitGround();
				}
				else
				{
					(*it_Character)->Character_HitCeiling();
				}
			}
		}

		//Z�̈ړ������̓����蔻��
		for (std::vector<BoxCollider>::iterator it_Stage = pStageCollider->begin();
			it_Stage != pStageCollider->end(); it_Stage++)
		{

			CVector3 DiffPos = (*it_Character)->GetPos() - (*it_Character)->GetOldPos();		//�O�̈ʒu���獡�̈ʒu�܂ňړ������x�N�g��
			CVector3 HitSize = (pCharacterCollider->GetSize() + (*it_Stage).GetSize()) * 0.5f;
			float NowDistanceX = pCharacterCollider->GetBasePos().x - (*it_Stage).GetBasePos().x;
			float AbsNowDistanceX = fabsf(NowDistanceX);
			float NowDistanceY = pCharacterCollider->GetBasePos().y - (*it_Stage).GetBasePos().y;
			float AbsNowDistanceY = fabsf(NowDistanceY);
			float NowDistanceZ = pCharacterCollider->GetBasePos().z - DiffPos.z - (*it_Stage).GetBasePos().z;
			float AbsNowDistanceZ = fabsf(NowDistanceZ);

			//Z�̈ړ��������ē������Ă�����
			if (AbsNowDistanceX < HitSize.x &&
				AbsNowDistanceY < HitSize.y &&
				AbsNowDistanceZ < HitSize.z)
			{
				CVector3 newPos = (*it_Character)->GetPos();
				float MoveDist = DiffPos.z < 0.0f ? HitSize.z : -HitSize.z;
				newPos.z = (*it_Stage).GetBasePos().z + MoveDist;
				(*it_Character)->SetPos(newPos);
			}
		}
	}
}

void SceneGame::Collision_Attack_Player()
{
	//=====<�L�����N�^�[�̍U���̓����蔻��>=====
	//��Őݒ肵���U���̓����蔻����g����
	//�L�����N�^�[���m�̍U���̓����蔻����s��
	for (Character* AttackCharacter : m_Characters)
	{
		//�L�����N�^�[���Q�[���I�[�o�[���Ă����瓖���蔻����s��Ȃ�
		if (AttackCharacter->GetState() == Character::STATE::GAMEOVER)
		{
			continue;
		}

		//�L�����N�^�[���U�����Ă��Ȃ���Ύ��̃L�����N�^�[��
		if (AttackCharacter->GetState() != Character::STATE::ATTACK)
		{
			continue;
		}

		//�U�����Ă���L�����N�^�[����U���̓����蔻�������Ă���
		std::vector<Character::ATTACKPARAM>& attackParamVector = AttackCharacter->GetAttackCollider();

		//�z��̓�����U�������Ă���
		for (Character::ATTACKPARAM& Character_Attack : attackParamVector)
		{
			//�O�̃t���[���Ɉˑ����Ȃ��r�b�g�͂�����0�ɂ��Ă���
			Character_Attack.m_HitCharacterBit = 0x00;
			Character_Attack.m_HitTriggerCharacterBit = 0x00;

			if (!Character_Attack.m_Use)
			{
				continue;
			}

			//�U�����󂯂�L�����N�^�[
			for (Character* HitCharacter : m_Characters)
			{
				//�󂯂�L�����N�^�[���Q�[���I�[�o�[�̏ꍇ
				if (HitCharacter->GetState() == Character::STATE::GAMEOVER)
				{
					continue;
				}

				//�U�����Ă���L�����N�^�[�Ǝ󂯂�L�����N�^�[�������ꍇ
				if (AttackCharacter == HitCharacter)
				{
					continue;
				}

				//���Ă�L�����N�^�[�����G�̏ꍇ�����蔻����s��Ȃ�
				if (HitCharacter->IsInvincible())
				{
					continue;
				}

				//�U���Ǝ󂯂�L�����N�^�[�̓����蔻��
				if (Character_Attack.m_BoxCollider.CollisionBox(*HitCharacter->GetCharacterCollider()))
				{
					//���������L�����N�^�[�̏�������
					Character_Attack.m_HitCharacterBit |= HitCharacter->GetCharacterBit();
					Character_Attack.m_HitTriggerCharacterBit = ~Character_Attack.m_haveHitCharacterBit & HitCharacter->GetCharacterBit();
					Character_Attack.m_haveHitCharacterBit |= HitCharacter->GetCharacterBit();

					//�U���𓖂Ă�̔���
					if ((HitCharacter->GetCharacterBit() & Character_Attack.m_CanAttackCharacterBit) != 0x00)
					{
						//====<�����������̏���>====
						CVector3 HitCharacterPos = HitCharacter->GetPos();
						HitCharacterPos.y += 0.01f;			//�����������Ȃ��Ɖ��Œn�ʂɓ������Ă��܂�
						HitCharacter->SetPos(HitCharacterPos);

						//�����������̏���������
						switch (AttackCharacter->GetAttack())
						{
						case Character::ATTACK::ATTACK_11:
							AttackCharacter->Attack11_Hit(HitCharacter);
							break;
						case Character::ATTACK::ATTACK_12:
							AttackCharacter->Attack12_Hit(HitCharacter);
							break;
						case Character::ATTACK::ATTACK_13:
							AttackCharacter->Attack13_Hit(HitCharacter);
							break;
						case Character::ATTACK::ATTACK_S2:
							AttackCharacter->AttackS2_Hit(HitCharacter);
							break;
						case Character::ATTACK::ATTACK_S4:
							AttackCharacter->AttackS4_Hit(HitCharacter);
							break;
						case Character::ATTACK::ATTACK_AIRN:
							AttackCharacter->AttackAirN_Hit(HitCharacter);
							break;
						case Character::ATTACK::SPECIAL_N:
							AttackCharacter->SpecialN_Hit(HitCharacter);
							break;
						case Character::ATTACK::SPECIAL_AIRN:
							AttackCharacter->SpecialAirN_Hit(HitCharacter);
							break;
						case Character::ATTACK::MAX:
							break;
						default:
							break;
						}
					}
				}
			}
		}
	}
}