#include "Camera01_Game.h"
#include "Input.h"

CameraGame::CameraGame()
{
	m_pos = m_look = CVector3::GetZero();

	m_pos.y = m_look.y = 3.0f;
	m_pos.z = -30.0f;
}

CameraGame::~CameraGame()
{
}

void CameraGame::Update()
{
	if (m_CharacterVector == nullptr)
	{
		return;
	}

	if ((*m_CharacterVector).size() == 0)
	{
		return;
	}


	float MaxRightX, MaxLeftX, MaxTopY, MaxBottomY;

	std::vector<Character*>::iterator Character_It = (*m_CharacterVector).begin();

	MaxRightX = MaxLeftX = (*Character_It)->GetPos().x; 
	MaxTopY	= MaxBottomY = (*Character_It)->GetPos().y;
	Character_It++;

	for (; Character_It != (*m_CharacterVector).end(); Character_It++)
	{
		CVector3 CharacterPos = (*Character_It)->GetPos();
		if (MaxRightX < CharacterPos.x)
		{
			MaxRightX = CharacterPos.x;
		}
		if (MaxLeftX > CharacterPos.x)
		{
			MaxLeftX = CharacterPos.x;
		}
		if (MaxTopY < CharacterPos.y)
		{
			MaxTopY = CharacterPos.y;
		}
		if (MaxBottomY > CharacterPos.y)
		{
			MaxBottomY = CharacterPos.y;
		}
	}

	//�L�����N�^�[�ƃL�����N�^�[�̒��Ԃ�����Ĉړ�����ʒu��ݒ�
	const float NearZ = -7.0f;				//��ԋ߂��ɒu����J�������W
	const float FarZ = -25.0f;				//��ԉ����ɒu����J�������W
	const float NearDistance = 3.0f;		//���ꋗ�����Z����΃J��������ԋ߂��Ȃ�
	const float FarDistance = 10.0f;		//���̋�����艓����΃J��������ԉ��������ɍs��
	float NowDistance = sqrtf(powf(MaxRightX - MaxLeftX, 2.0f) + powf(MaxTopY - MaxBottomY, 2.0f));

	CVector3 GotoPos;
	GotoPos.x = (MaxRightX - MaxLeftX) / 2.0f + MaxLeftX;
	GotoPos.y = (MaxTopY - MaxBottomY) / 2.0f + MaxBottomY + 2.0f;

	if (NowDistance < NearDistance)
	{
		GotoPos.z = NearZ;
	}
	else if (NowDistance > FarDistance)
	{
		GotoPos.z = FarZ;
	}
	else
	{
		float PerDistance = NowDistance - NearDistance;
		float Percent = PerDistance / (FarDistance - NearDistance);
		GotoPos.z = (FarZ - NearZ) * Percent + NearZ;
	}

	//��������W����������ׂ����W��⊮���Ȃ���ړ�����
	CVector3 GoVector = GotoPos - m_pos;
	GoVector = GoVector * 0.03f;

	m_pos = m_pos + GoVector;
	m_look.x = m_pos.x;
	m_look.y = m_pos.y;



	//�J�������s����ő�̒[�ȏゾ�����ꍇ�߂��Ă��
}

void CameraGame::ChangeInit()
{
}

void CameraGame::ChangeUninit()
{
}

void CameraGame::SetCharacter(std::vector<Character*>* pCharacterVector)
{
	m_CharacterVector = pCharacterVector;
}
