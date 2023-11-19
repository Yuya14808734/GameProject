#include "00_SceneGame.h"

void SceneGame::Init()
{

}

void SceneGame::Uninit()
{

}

void SceneGame::Update()
{
	//�L�����N�^�[�̃A�b�v�f�[�g
	//�����ōU����ړ��Ȃǂ̃A�b�v�f�[�g���s��
	for(std::vector<Character*>::iterator it = m_Characters.begin();
	it != m_Characters.end(); it++)
	{
		(*it)->Character_Update();
	}

	//�L�����N�^�[���m�̓����蔻��
	//�l�p�Ǝl�p
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
			float NowHarfDistanceX = (pFirstCollider->pos.x - pSecondCollider->pos.x) * 0.5f;
			CVector3 CenterPos = pSecondCollider->pos + CVector3(NowHarfDistanceX,0.0f,0.0f);

			float Direct = NowHarfDistanceX < 0.0f ? -1.0f : 1.0f;

			(*it_first)->SetPos(CenterPos + CVector3(pFirstCollider->size.x * Direct,0.0f,0.0f));
			(*it_second)->SetPos(CenterPos + CVector3(pFirstCollider->size.x * Direct, 0.0f, 0.0f));
		}
	}	

	//�L�����N�^�[�̍U���̓����蔻��
	//��ŋ��߂��U���̓����蔻����g����
	//�L�����N�^�[���m�̍U���̓����蔻����s��
	//�~�Ɖ~


	//�L�����N�^�[�ƃX�e�[�W�̓����蔻��
	//�_�Ǝl�p
	std::vector<BoxCollider>* pStageCollider = m_pStage->GetStageCollider();
	
	for (std::vector<Character*>::iterator it_Character = m_Characters.begin();
		it_Character != m_Characters.end(); it_Character++)
	{
		BoxCollider* pCharacterCollider = (*it_Character)->GetCharacterCollider();

		//�����蔻������
		for (std::vector<BoxCollider>::iterator it_Stage = pStageCollider->begin();
			it_Stage != pStageCollider->end(); it_Stage++)
		{
			CVector3 DiffPos = (*it_Character)->GetPos() - (*it_Character)->GetOldPos();		//�O�̈ʒu���獡�̈ʒu�܂ňړ������x�N�g��
			CVector3 HitSize = (pCharacterCollider->size - (*it_Stage).size) * 0.5f;
			float NowDistanceX =  pCharacterCollider->pos.x - (*it_Stage).pos.x;
			float AbsNowDistanceX = fabsf(NowDistanceX);
			CVector3 OldDistance = (pCharacterCollider->pos - DiffPos) - (*it_Stage).pos;
			CVector3 AbsOldDistance = OldDistance.Abs();

			//X�̈ړ�
			if(AbsNowDistanceX < HitSize.x &&
				AbsOldDistance.y < HitSize.y &&
				AbsOldDistance.z < HitSize.z)
			{
				CVector3 newPos = (*it_Character)->GetPos();
				newPos.x = (*it_Stage).pos.x + NowDistanceX < 0.0f ? -HitSize.x : HitSize.x;
				(*it_Character)->SetPos(newPos);
			}
		}

		//Y�̈ړ�

		//Z�̈ړ�

	}


}

void SceneGame::Draw()
{

}
