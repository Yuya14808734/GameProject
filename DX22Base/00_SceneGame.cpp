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

}

void SceneGame::Draw()
{

}
