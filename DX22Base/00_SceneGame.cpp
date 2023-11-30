#include "00_SceneGame.h"
#include "CameraManager.h"
#include "00_CameraDebug.h"
#include "ModelDrawer.h"
#include "Geometory.h"
#include "Input.h"
#include "Stage_00.h"
#include "Character_00.h"

bool ColliderDraw = false;
ModelDrawer modeldrawer;

void SceneGame::Init()
{
	CameraManager::GetInstance().CreateCamera(new CameraDebug(), "DebugCamera");
	CameraManager::GetInstance().SetSceneCamera("DebugCamera");
	modeldrawer.LoadModel("Assets/Character00/Model03.fbx", "Character00");
	modeldrawer.SetModel("Character00");
	modeldrawer.SetPosition(CVector3::GetZero());
	modeldrawer.SetScale({ 0.1f, 0.1f, 0.1f });

	m_pStage = new Stage00();
	m_pStage->Stage_Init();

	m_Characters.push_back(new Character_00());
	m_Characters[0]->Character_Init();
}

void SceneGame::Uninit()
{
	for (auto it = m_Characters.begin(); it != m_Characters.end();)
	{
		(*it)->Character_Uninit();
		delete (*it);
		it = m_Characters.erase(it);
	}

	m_pStage->Stage_Uninit();
	delete m_pStage;
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
	}

	//=====<�L�����N�^�[���m�̓����蔻��>=====
	for (std::vector<Character*>::iterator it_first = m_Characters.begin();
		it_first != m_Characters.end();it_first++)
	{
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
				return;
			}

			//�߂荞�񂾔����̈ʒu�ňړ����Ă��
			float NowHarfDistanceX = (pFirstCollider->GetPos().x - pSecondCollider->GetPos().x) * 0.5f;
			CVector3 CenterPos = pSecondCollider->GetPos() + CVector3(NowHarfDistanceX,0.0f,0.0f);

			float Direct = NowHarfDistanceX < 0.0f ? -1.0f : 1.0f;

			(*it_first)->SetPos(CenterPos + CVector3(pFirstCollider->GetSize().x * Direct,0.0f,0.0f));
			(*it_second)->SetPos(CenterPos + CVector3(pFirstCollider->GetSize().x * Direct, 0.0f, 0.0f));
		}
	}	

	//=====<�L�����N�^�[�̍U���̓����蔻��>=====
	//��Őݒ肵���U���̓����蔻����g����
	//�L�����N�^�[���m�̍U���̓����蔻����s��



	//=====<�L�����N�^�[�ƃX�e�[�W�̓����蔻��>=====
	std::vector<BoxCollider>* pStageCollider = m_pStage->GetStageCollider();
	
	for (std::vector<Character*>::iterator it_Character = m_Characters.begin();
		it_Character != m_Characters.end(); it_Character++)
	{
		BoxCollider* pCharacterCollider = (*it_Character)->GetCharacterCollider();

		//X�̈ړ������̓����蔻��
		for (std::vector<BoxCollider>::iterator it_Stage = pStageCollider->begin();
			it_Stage != pStageCollider->end(); it_Stage++)
		{
			CVector3 DiffPos = (*it_Character)->GetPos() - (*it_Character)->GetOldPos();		//�O�̈ʒu���獡�̈ʒu�܂ňړ������x�N�g��
			CVector3 HitSize = (pCharacterCollider->GetSize() + (*it_Stage).GetSize()) * 0.5f;
			float NowDistanceX =  pCharacterCollider->GetPos().x - (*it_Stage).GetPos().x;
			float AbsNowDistanceX = fabsf(NowDistanceX);
			float OldDistanceY = (pCharacterCollider->GetPos().y - DiffPos.y) - (*it_Stage).GetPos().y;
			float AbsOldDistanceY = fabsf(OldDistanceY);
			float OldDistanceZ = (pCharacterCollider->GetPos().z - DiffPos.z) - (*it_Stage).GetPos().z;
			float AbsOldDistanceZ = fabsf(OldDistanceZ);
			
			//X�̈ړ��������ē������Ă�����
			if(AbsNowDistanceX < HitSize.x &&
				AbsOldDistanceY < HitSize.y &&
				AbsOldDistanceZ < HitSize.z)
			{
				CVector3 newPos = (*it_Character)->GetPos();
				float MoveDist = DiffPos.x < 0.0f ? HitSize.x : -HitSize.x;
				newPos.x = (*it_Stage).GetPos().x + MoveDist;
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
	m_pStage->Stage_Draw();

	for (Character* copy : m_Characters)
	{
		copy->Character_Draw();
	}

	if (IsKeyTrigger(VK_RETURN))
	{
		ColliderDraw = !ColliderDraw;
	}

	if (ColliderDraw)
	{
		m_pStage->StageColliderDraw();

		for (Character* copy : m_Characters)
		{
			copy->DrawCollider();
		}
	}

	modeldrawer.Draw();
}
