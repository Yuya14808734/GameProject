#include "00_SceneGame.h"
#include "CameraManager.h"
#include "00_CameraDebug.h"
#include "ModelDrawer.h"
#include "Geometory.h"
#include "Input.h"
#include "Stage_00.h"
#include "Character_00.h"
#include "Player_Controller.h"

bool ColliderDraw = false;

void SceneGame::Init()
{
	//=====<�R���g���[���[�̏�����>=====
	PlayerController::InitXPadNum();

	//=====<�J�����̐���>=====
	CameraManager::GetInstance().CreateCamera(new CameraDebug(), "DebugCamera");
	CameraManager::GetInstance().SetSceneCamera("DebugCamera");

	//=====<�X�e�[�W�̍쐬>=====
	m_pStage = new Stage00();
	m_pStage->Stage_Init();

	//=====<�L�����N�^�[�̐���>=====
	Character::InitPlayerBit();
	m_Characters.push_back(new Character_00());
	m_Characters.push_back(new Character_00());

	for (Character* pCharacter : m_Characters)
	{
		pCharacter->Character_Init();
	}
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
	//=====<�L�����N�^�[�̃A�b�v�f�[�g>=====
	//�����ōU����ړ��Ȃǂ̃A�b�v�f�[�g���s��
	for(std::vector<Character*>::iterator it = m_Characters.begin();
	it != m_Characters.end(); it++)
	{
		(*it)->Character_Update();				//�L�����N�^�[�̃A�b�v�f�[�g���s��
		(*it)->Character_ColliderInit();		//�R���C�_�[�̏������������Ă��
												//(�����蔻����s���Ă��Ȃ��̂œ������Ă��Ȃ����Ƃɂ��鏈��)
	}

	//=====<�L�����N�^�[���m�̓����蔻��>=====

	//��l�ڂ̃L�����N�^�[��I��
	for (std::vector<Character*>::iterator it_first = m_Characters.begin();
		it_first != m_Characters.end();it_first++)
	{
		//��l�ڂ̃L�����N�^�[��I��(��l�ڂ̎��̃L�����N�^�[)
		std::vector<Character*>::iterator it_second = it_first + 1;
		for (; it_second != m_Characters.end(); it_second++)
		{
			//�l�p�R���C�_�[�̎擾
			BoxCollider* pFirstCollider = (*it_first)->GetCharacterCollider();
			BoxCollider* pSecondCollider = (*it_second)->GetCharacterCollider();

			//�l�p���m�̓����蔻����s��
			if (!pFirstCollider->CollisionBox(*pSecondCollider))
			{
				//�������Ă��Ȃ��ꍇ
				continue;
			}

			//�߂荞�񂾔����̈ʒu�ňړ����Ă��(X�̂�)
			float NowHarfDistanceX = (pFirstCollider->GetPos().x - pSecondCollider->GetPos().x) * 0.5f;
			float CenterPosX = pSecondCollider->GetPos().x + NowHarfDistanceX;
			float FirstDirect = NowHarfDistanceX < 0.0f ? -1.0f : 1.0f;	//pFirstCollider�Ɍ���������
			//��̒l���}�C�i�X�Ȃ�ʒu�֌W��
			//pFirstCollider �E pSecondCollider�ƂȂ�
			//��̒l���v���X�Ȃ�ʒu�֌W��
			//pSecondCollider �E pFirstCollider�ƂȂ�

			//��l�ڂ̃L�����N�^�[�̈ʒu�ݒ�
			(*it_first)->SetPos(
				CVector3(
					CenterPosX + ( (pFirstCollider->GetSize().x * 0.5f) * FirstDirect),
					(*it_first)->GetPos().y,
					(*it_first)->GetPos().z
				)
			);
			
			//��l�ڂ̃L�����N�^�[�̈ʒu�ݒ�
			(*it_second)->SetPos(
				CVector3(
					CenterPosX + ((pSecondCollider->GetSize().x * 0.5f) * -FirstDirect),
					(*it_second)->GetPos().y,
					(*it_second)->GetPos().z
				)
			);
		}
	}	

	//=====<�L�����N�^�[�̍U���̓����蔻��>=====
	//��Őݒ肵���U���̓����蔻����g����
	//�L�����N�^�[���m�̍U���̓����蔻����s��
	for (Character* AttackCharacter : m_Characters)
	{
		//�U�����Ă���L�����N�^�[����U���̓����蔻�������Ă���
		std::vector<Character::ATTACKPARAM>& attackParamVector = AttackCharacter->GetAttackCollider();

		if (AttackCharacter->GetState() != Character::STATE::ATTACK)
		{
			continue;
		}

		//�z��̓�����U�������Ă���
		for (Character::ATTACKPARAM& Character_Attack : attackParamVector)
		{
			//�O�̃t���[���Ɉˑ����Ȃ��r�b�g�͂�����0�ɂ��Ă���
			Character_Attack.m_HitCharacterBit = 0x00;
			Character_Attack.m_HitTriggerCharacterBit = 0x00;

			if(!Character_Attack.m_Use)
			{
				continue;
			}

			//�U�����󂯂�L�����N�^�[
			for (Character* HitCharacter : m_Characters)
			{
				//�U�����Ă���L�����N�^�[�Ǝ󂯂�L�����N�^�[�������ꍇ
				if(AttackCharacter == HitCharacter)
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

	//=====<�L�����N�^�[�ƃX�e�[�W�̓����蔻��>=====
	std::vector<BoxCollider>* pStageCollider = m_pStage->GetStageCollider();
	
	for (std::vector<Character*>::iterator it_Character = m_Characters.begin();
		it_Character != m_Characters.end(); it_Character++)
	{
		BoxCollider* pCharacterCollider = (*it_Character)->GetCharacterCollider();

		//X�̈ړ������̓����蔻��
		for (std::vector<BoxCollider>::iterator it_StageCollider = pStageCollider->begin();
			it_StageCollider != pStageCollider->end(); it_StageCollider++)
		{
			CVector3 DiffPos = (*it_Character)->GetPos() - (*it_Character)->GetOldPos();		//�O�̈ʒu���獡�̈ʒu�܂ňړ������x�N�g��
			CVector3 HitSize = (pCharacterCollider->GetSize() + (*it_StageCollider).GetSize()) * 0.5f;
			float NowDistanceX =  pCharacterCollider->GetPos().x - (*it_StageCollider).GetPos().x;
			float AbsNowDistanceX = fabsf(NowDistanceX);
			float OldDistanceY = (pCharacterCollider->GetPos().y - DiffPos.y) - (*it_StageCollider).GetPos().y;
			float AbsOldDistanceY = fabsf(OldDistanceY);
			float OldDistanceZ = (pCharacterCollider->GetPos().z - DiffPos.z) - (*it_StageCollider).GetPos().z;
			float AbsOldDistanceZ = fabsf(OldDistanceZ);
			
			//X�̈ړ��������ē������Ă�����
			if(AbsNowDistanceX < HitSize.x &&
				AbsOldDistanceY < HitSize.y &&
				AbsOldDistanceZ < HitSize.z)
			{
				CVector3 newPos = (*it_Character)->GetPos();
				float MoveDist = DiffPos.x < 0.0f ? HitSize.x : -HitSize.x;
				newPos.x = (*it_StageCollider).GetPos().x + MoveDist;
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
			float NowDistanceX = pCharacterCollider->GetPos().x - (*it_Stage).GetPos().x;
			float AbsNowDistanceX = fabsf(NowDistanceX);
			float NowDistanceY = pCharacterCollider->GetPos().y - (*it_Stage).GetPos().y;
			float AbsNowDistanceY = fabsf(NowDistanceY);
			float OldDistanceZ = (pCharacterCollider->GetPos().z - DiffPos.z) - (*it_Stage).GetPos().z;
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
				newPos.y = (*it_Stage).GetPos().y + MoveDist;
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
			float NowDistanceX = pCharacterCollider->GetPos().x - (*it_Stage).GetPos().x;
			float AbsNowDistanceX = fabsf(NowDistanceX);
			float NowDistanceY = pCharacterCollider->GetPos().y - (*it_Stage).GetPos().y;
			float AbsNowDistanceY = fabsf(NowDistanceY);
			float NowDistanceZ = pCharacterCollider->GetPos().z - DiffPos.z - (*it_Stage).GetPos().z;
			float AbsNowDistanceZ = fabsf(NowDistanceZ);

			//Z�̈ړ��������ē������Ă�����
			if (AbsNowDistanceX < HitSize.x &&
				AbsNowDistanceY < HitSize.y &&
				AbsNowDistanceZ < HitSize.z)
			{
				CVector3 newPos = (*it_Character)->GetPos(); 
				float MoveDist = DiffPos.z < 0.0f ? HitSize.z : -HitSize.z;
				newPos.z = (*it_Stage).GetPos().z + MoveDist;
				(*it_Character)->SetPos(newPos);
			}
		}
	}
}

void SceneGame::Draw()
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

	EnableDepth(true);
}

std::vector<Character*>& SceneGame::GetCharacter()
{
	return m_Characters;
}

Stage* SceneGame::GetStage()
{
	return m_pStage;
}
