#include "SceneGame_GamePlayState.h"
#include "Character_State.h"
#include "Character_Attack.h"
#include "CameraManager.h"

void SceneGame_PlayState::Init()
{
	m_VisibleGo_CountTime = 0;

	CameraManager::GetInstance().SetSceneCamera("GameCamera");
}

void SceneGame_PlayState::Uninit()
{
	m_pGameScene->EffectPause();
}

void SceneGame_PlayState::Update()
{
	if (m_VisibleGo_CountTime < 60)
	{
		m_VisibleGo_CountTime++;
		m_pGameStartCountUI->Update();
	}

	//=====<�L�����N�^�[�̃A�b�v�f�[�g>=====
	//�����ōU����ړ��Ȃǂ̃A�b�v�f�[�g���s��
	for (std::vector<Character*>::iterator it = m_pCharacters->begin();
		it != m_pCharacters->end(); it++)
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

	//=====<�L�����N�^�[�̂ǂ��炩���X�g�b�N�������Ȃ�����>=====
	CheckGameEnd();

	//=====<�X�g�b�N�̓���>=====
	m_pStockCountUI->Update();
}

void SceneGame_PlayState::Draw()
{
	//=====<�w�i�̕`��>=====
	m_pBackGround->Draw();

	//=====<�����蔻��̕`��>=====
	ColliderDraw();

	//=====<�X�e�[�W�̕`��>=====
	m_pStage->Stage_Draw();

	//=====<�L�����N�^�[�̕`��>=====
	for (Character* copy : (*m_pCharacters))
	{
		copy->Character_Draw();
	}

	//=====<�G�t�F�N�g�̕`��>=====
	for (EffectBase* pEffect : (*m_pEffects))
	{
		pEffect->Draw();
	}

	//=====<UI�̕`��>=====
	EnableDepth(false);

	for (Character* copy : (*m_pCharacters))
	{
		copy->Character_UIDraw();
	}

	//Go�̕`��(1�b����)
	if (m_VisibleGo_CountTime < 60)
	{
		m_pGameStartCountUI->Draw();
	}

	m_pStockCountUI->Draw();

	EnableDepth(true);
}

void SceneGame_PlayState::DrawCharacterStock()
{
	if ((*m_pCharacters).size() > 2)
	{
		return;
	}

	m_pStockCountUI->LerpStart(
		(*m_pCharacters)[0]->GetStock(),
		(*m_pCharacters)[1]->GetStock());
}

void SceneGame_PlayState::Collision_Player_Player()
{
	//=====<�L�����N�^�[���m�̓����蔻��>=====

	//��l�ڂ̃L�����N�^�[��I��
	for (std::vector<Character*>::iterator it_first = m_pCharacters->begin();
		it_first != m_pCharacters->end(); it_first++)
	{
		//��l�ڂ̃L�����N�^�[��I��(��l�ڂ̎��̃L�����N�^�[)
		std::vector<Character*>::iterator it_second = it_first + 1;
		for (; it_second != m_pCharacters->end(); it_second++)
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

void SceneGame_PlayState::Collision_Attack_Player()
{
	//=====<�L�����N�^�[�ƃX�e�[�W�̓����蔻��>=====
	std::vector<BoxCollider>* pStageCollider = m_pStage->GetStageCollider();

	for (std::vector<Character*>::iterator it_Character = m_pCharacters->begin();
		it_Character != m_pCharacters->end(); it_Character++)
	{
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
				float MoveDist = DiffPos.y < 0.0f ?			//Y�̓�����
					//----------------------------------------------------------
					HitSize.y -							//�ォ�炠���������̏���
					(pCharacterCollider->GetType() == BoxCollider::BOXTYPE::FOOT ?
						(pCharacterCollider->GetSize().y * 0.5f) : 0.0f) :
					//----------------------------------------------------------
					-HitSize.y -							//�����炠���������̏���
					(pCharacterCollider->GetType() == BoxCollider::BOXTYPE::FOOT ?
						(pCharacterCollider->GetSize().y * 0.5f) : 0.0f);
					//----------------------------------------------------------

				newPos.y = (*it_Stage).GetBasePos().y + MoveDist;	//�X�e�[�W����̋����Őݒ�
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
	}
}

void SceneGame_PlayState::Collision_Player_Stage()
{
	//=====<�L�����N�^�[�̍U���̓����蔻��>=====
	//��Őݒ肵���U���̓����蔻����g����
	//�L�����N�^�[���m�̍U���̓����蔻����s��
	for (Character* AttackCharacter : (*m_pCharacters))
	{
		//�L�����N�^�[���U�����Ă��Ȃ���Ύ��̃L�����N�^�[��
		if (static_cast<Character_State*>(AttackCharacter->GetStateContext()->GetNowState())
			->GetType() != Character_State::TYPE::ATTACK)
		{
			continue;
		}

		//�U�����Ă���L�����N�^�[����U���̓����蔻�������Ă���
		std::vector<Character::ATTACKPARAM>& attackParamVector = AttackCharacter->GetAttackCollider();

		//�z��̓�����U�������Ă���
		for (Character::ATTACKPARAM& Character_Attack : attackParamVector)
		{
			//�O�̃t���[���Ɉˑ����Ȃ��r�b�g�͂�����0�ɂ��Ă���
			Character_Attack.m_HitCharacterBit = 0x00;			//���̃t���[���œ��������L�����N�^�[
			Character_Attack.m_HitTriggerCharacterBit = 0x00;	//���̃t���[���ŏ��߂ē��������L�����N�^�[

			//���̍U���̓����蔻��͎g��Ȃ�
			if (!Character_Attack.m_Use)
			{
				continue;
			}

			//�U�����󂯂�L�����N�^�[
			for (Character* HitCharacter : (*m_pCharacters))
			{
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
					Character_Attack.m_HitCharacterBit |= HitCharacter->GetCharacterBit();				//���̃t���[���œ��������L�����N�^�[
					Character_Attack.m_HitTriggerCharacterBit
						= ~Character_Attack.m_haveHitCharacterBit & HitCharacter->GetCharacterBit();	//�n�߂ē��������L�����N�^�[
					Character_Attack.m_haveHitCharacterBit |= HitCharacter->GetCharacterBit();			//���܂œ����������Ƃ̂���L�����N�^�[

					//�U���𓖂Ă�̔���
					if ((HitCharacter->GetCharacterBit() & Character_Attack.m_CanAttackCharacterBit) != 0x00)
					{
						//====<�����������̏���>====
						CVector3 HitCharacterPos = HitCharacter->GetPos();
						HitCharacterPos.y += 0.01f;			//�����������Ȃ��Ɖ��Œn�ʂɓ������Ă��܂�
						HitCharacter->SetPos(HitCharacterPos);

						//�����������̏���������
						static_cast<Character_AttackState*>(AttackCharacter->GetStateContext()->GetNowState())
							->HitCharacter(HitCharacter);
					}
				}
			}
		}
	}
}

void SceneGame_PlayState::CheckGameEnd()
{
	bool isGameOver = false;

	for (std::vector<Character*>::iterator it = m_pCharacters->begin();
		it != m_pCharacters->end(); it++)
	{
		isGameOver = isGameOver || (*it)->GetGameOver();
	}

	if (isGameOver)
	{
		m_pGameScene->SetNextState(SceneGame::GAMESTATE::GAMEEND);
	}
}

void SceneGame_PlayState::ColliderDraw()
{
	//=====<�����蔻��̕`��>=====
	if (IsKeyTrigger(VK_RETURN))
	{
		m_ColliderDraw = !m_ColliderDraw;
	}

	if (m_ColliderDraw)
	{
		m_pStage->StageColliderDraw();
		for (Character* CharacterCopy : (*m_pCharacters))
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
}
