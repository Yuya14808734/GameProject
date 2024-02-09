#include "Camera01_Game.h"
#include "Input.h"

CameraGame::CameraGame()
	:m_pCharacterVector(nullptr),
	m_pStage(nullptr)
{
}

CameraGame::~CameraGame()
{
}

void CameraGame::Init()
{
	m_pos = m_look = CVector3::GetZero();

	m_pos.y = m_look.y = 3.0f;
	m_pos.z = -30.0f;
}

void CameraGame::Uninit()
{
}

void CameraGame::Update()
{
	//=====<�ړ��Ɋւ�������擾�ł��邩�m�F>========================
	if (m_pCharacterVector == nullptr)
	{
		return;
	}

	if (m_pStage == nullptr)
	{
		return;
	}

	if((*m_pCharacterVector).size() == 0)
	{
		return;
	}
	//=================================================================

	//=====<�ړ��Ɋւ�������擾�ł��邩�m�F>========================
	float MaxRightX, MaxLeftX, MaxTopY, MaxBottomY;

	std::vector<Character*>::iterator Character_It = (*m_pCharacterVector).begin();

	//��ԍŏ��̃L�����N�^�[�����r�����Ă���
	MaxRightX = MaxLeftX = (*Character_It)->GetPos().x; 
	MaxTopY	= MaxBottomY = (*Character_It)->GetPos().y;
	Character_It++;

	//���܂ł̃L�����N�^�[�Ɣ�ׂĈ�Ԓ[���ς�邩���m�F
	for (; Character_It != (*m_pCharacterVector).end(); Character_It++)
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

	//�f�b�g���C����菭�����炵���ʒu���J����������鋴�Ƃ��Đݒ肷��
	float StageCanSeeLineRightX = m_pStage->GetDeadLineRightX() - 3.0f;
	float StageCanSeeLineLeftX = m_pStage->GetDeadLineLeftX() + 3.0f;
	float StageCanSeeLineTopY = m_pStage->GetDeadLineTopY() - 3.0f;
	float StageCanSeeLineBottomY = m_pStage->GetDeadLineBottomY() + 3.0f;
	
	//�ݒ肵���L�����N�^�[�̒[�̈ʒu��
	//�f�b�g���C���𒴂��Ă����ꍇ�A�f�b�g���C�����f�������Ȃ��̂ňʒu�ύX
	if (StageCanSeeLineRightX < MaxRightX)
	{
		MaxRightX = StageCanSeeLineRightX;
	}
	if (StageCanSeeLineLeftX > MaxLeftX)
	{
		MaxLeftX = StageCanSeeLineLeftX;
	}
	if (StageCanSeeLineTopY < MaxTopY)
	{
		MaxTopY = StageCanSeeLineTopY;
	}
	if (StageCanSeeLineBottomY > MaxBottomY)
	{
		MaxBottomY = StageCanSeeLineBottomY;
	}

	//======================================================================

	//=====<�L�����N�^�[�ƃL�����N�^�[�̒��Ԃ�����Ĉړ�����ʒu��ݒ�>=====
	const float NearZ = -7.0f;				//��ԋ߂��ɒu����J�������W
	const float FarZ = -20.0f;				//��ԉ����ɒu����J�������W
	const float NearDistance = 4.0f;		//�΂߂����̒����ɋ߂��Ȃ��Z��NearZ�ɂȂ�
	const float FarDistance = 10.0f;		//�΂߂����̒����ɋ߂��Ȃ��Z��FarZ�ɂȂ�
	float HypotenuseDistance =				//�[�ɂ���L�����N�^�[���m�̈ʒu�̎΂߂̒���������
		sqrtf(powf(MaxRightX - MaxLeftX, 2.0f) + powf(MaxTopY - MaxBottomY, 2.0f));

	//�J�������s���ׂ����W
	CVector3 GotoPos;

	//X��Y��ݒ�
	//�L�����N�^�[���m�̐^�񒆂̈ʒu�Ɉړ�
	GotoPos.x = (MaxRightX - MaxLeftX) / 2.0f + MaxLeftX;
	GotoPos.y = (MaxTopY - MaxBottomY) / 2.0f + MaxBottomY + 2.0f;

	//Z��ݒ�
	if (HypotenuseDistance < NearDistance)
	{
		//�J�������s���鋗�����߂����
		GotoPos.z = NearZ;
	}
	else if (HypotenuseDistance > FarDistance)
	{
		//�J�������s���鋗����艓�����
		GotoPos.z = FarZ;
	}
	else
	{
		//��̓�Ŗ������
		float PerDistance = HypotenuseDistance - NearDistance;
		float Percent = PerDistance / (FarDistance - NearDistance);
		GotoPos.z = (FarZ - NearZ) * Percent + NearZ;
	}
	//======================================================================

	//=====<Z��0�̈ʒu�ŃJ���������Ă���4�[�̈ʒu����肷��>=============================
	float CameraVerticalRadian = DirectX::XMConvertToRadians(m_fovy / 2.0f);		//�J�����̃J�����c�����̉�p�����W�A����
	float SlantingLength = (1.0f / cosf(CameraVerticalRadian)) * GotoPos.z;			//��̕ϐ����g���Ď΂߂̒������o��
	float CameraCanLookLengthY =													//�O�����̒藝���g���ďc�̒������o��
		sqrtf(std::powf(SlantingLength, 2.0f) - std::powf(GotoPos.z, 2.0f));
	float CameraCanLookLengthX =													//�䗦���g���ĉ��̒������o��
		CameraCanLookLengthY * m_aspect;

	//Z��0�̈ʒu�̌����Ă��郉�C��
	float NowSeeLineRightX	= GotoPos.x + CameraCanLookLengthX;
	float NowSeeLineLeftX	= GotoPos.x - CameraCanLookLengthX;
	float NowSeeLineTopY	= GotoPos.y + CameraCanLookLengthY;
	float NowSeeLineBottomY = GotoPos.y - CameraCanLookLengthY;	
	//======================================================================

	//=====<�f�b�g���C�����J�������f���Ă����ꍇ�߂��Ă��>=============
	if(StageCanSeeLineRightX	< NowSeeLineRightX)
	{
		//���������߂Ă��̗ʂ�����
		float Difference = StageCanSeeLineRightX - NowSeeLineRightX;
		GotoPos.x += Difference;
	}
	if (StageCanSeeLineLeftX > NowSeeLineLeftX)
	{
		//���������߂Ă��̗ʂ�����
		float Difference = StageCanSeeLineLeftX - NowSeeLineLeftX;
		GotoPos.x += Difference;
	}
	if (StageCanSeeLineTopY < NowSeeLineTopY)
	{
		//���������߂Ă��̗ʂ�����
		float Difference = StageCanSeeLineTopY - NowSeeLineTopY;
		GotoPos.y += Difference;
	}
	if (StageCanSeeLineBottomY > NowSeeLineBottomY)
	{
		//���������߂Ă��̗ʂ�����
		float Difference = StageCanSeeLineBottomY - NowSeeLineBottomY;
		GotoPos.y += Difference;
	}
	//======================================================================

	//=====<��������W����������ׂ����W��⊮���Ȃ���ړ�����>=============
	CVector3 GoVector = GotoPos - m_pos;
	GoVector = GoVector * 0.03f;

	m_pos = m_pos + GoVector;
	m_look.x = m_pos.x;
	m_look.y = m_pos.y;
	//======================================================================
}

void CameraGame::ChangeInit()
{
	Init();
}

void CameraGame::ChangeUninit()
{
}

void CameraGame::SetCharacter(std::vector<Character*>* pCharacterVector)
{
	m_pCharacterVector = pCharacterVector;
}

void CameraGame::SetStage(Stage* pStage)
{
	m_pStage = pStage;
}
