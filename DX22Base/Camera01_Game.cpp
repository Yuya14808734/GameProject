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

	//キャラクターとキャラクターの中間を取って移動する位置を設定
	const float NearZ = -7.0f;				//一番近くに置けるカメラ座標
	const float FarZ = -25.0f;				//一番遠くに置けるカメラ座標
	const float NearDistance = 3.0f;		//これ距離より短ければカメラが一番近くなる
	const float FarDistance = 10.0f;		//この距離より遠ければカメラが一番遠い距離に行く
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

	//今いる座標から向かうべき座標を補完しながら移動する
	CVector3 GoVector = GotoPos - m_pos;
	GoVector = GoVector * 0.03f;

	m_pos = m_pos + GoVector;
	m_look.x = m_pos.x;
	m_look.y = m_pos.y;



	//カメラが行ける最大の端以上だった場合戻してやる
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
