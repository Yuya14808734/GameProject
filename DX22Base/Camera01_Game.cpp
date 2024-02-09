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
	//=====<移動に関する情報を取得できるか確認>========================
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

	//=====<移動に関する情報を取得できるか確認>========================
	float MaxRightX, MaxLeftX, MaxTopY, MaxBottomY;

	std::vector<Character*>::iterator Character_It = (*m_pCharacterVector).begin();

	//一番最初のキャラクターから比較をしていく
	MaxRightX = MaxLeftX = (*Character_It)->GetPos().x; 
	MaxTopY	= MaxBottomY = (*Character_It)->GetPos().y;
	Character_It++;

	//今までのキャラクターと比べて一番端が変わるかを確認
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

	//デットラインより少しずらした位置をカメラが見れる橋として設定する
	float StageCanSeeLineRightX = m_pStage->GetDeadLineRightX() - 3.0f;
	float StageCanSeeLineLeftX = m_pStage->GetDeadLineLeftX() + 3.0f;
	float StageCanSeeLineTopY = m_pStage->GetDeadLineTopY() - 3.0f;
	float StageCanSeeLineBottomY = m_pStage->GetDeadLineBottomY() + 3.0f;
	
	//設定したキャラクターの端の位置が
	//デットラインを超えていた場合、デットラインを映したくないので位置変更
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

	//=====<キャラクターとキャラクターの中間を取って移動する位置を設定>=====
	const float NearZ = -7.0f;				//一番近くに置けるカメラ座標
	const float FarZ = -20.0f;				//一番遠くに置けるカメラ座標
	const float NearDistance = 4.0f;		//斜めがこの長さに近くなるとZがNearZになる
	const float FarDistance = 10.0f;		//斜めがこの長さに近くなるとZがFarZになる
	float HypotenuseDistance =				//端にいるキャラクター同士の位置の斜めの長さが入る
		sqrtf(powf(MaxRightX - MaxLeftX, 2.0f) + powf(MaxTopY - MaxBottomY, 2.0f));

	//カメラが行くべき座標
	CVector3 GotoPos;

	//XとYを設定
	//キャラクター同士の真ん中の位置に移動
	GotoPos.x = (MaxRightX - MaxLeftX) / 2.0f + MaxLeftX;
	GotoPos.y = (MaxTopY - MaxBottomY) / 2.0f + MaxBottomY + 2.0f;

	//Zを設定
	if (HypotenuseDistance < NearDistance)
	{
		//カメラが行ける距離より近ければ
		GotoPos.z = NearZ;
	}
	else if (HypotenuseDistance > FarDistance)
	{
		//カメラが行ける距離より遠ければ
		GotoPos.z = FarZ;
	}
	else
	{
		//上の二つで無ければ
		float PerDistance = HypotenuseDistance - NearDistance;
		float Percent = PerDistance / (FarDistance - NearDistance);
		GotoPos.z = (FarZ - NearZ) * Percent + NearZ;
	}
	//======================================================================

	//=====<Zが0の位置でカメラが見ている4端の位置を特定する>=============================
	float CameraVerticalRadian = DirectX::XMConvertToRadians(m_fovy / 2.0f);		//カメラのカメラ縦方向の画角をラジアンに
	float SlantingLength = (1.0f / cosf(CameraVerticalRadian)) * GotoPos.z;			//上の変数を使って斜めの長さを出す
	float CameraCanLookLengthY =													//三平方の定理を使って縦の長さを出す
		sqrtf(std::powf(SlantingLength, 2.0f) - std::powf(GotoPos.z, 2.0f));
	float CameraCanLookLengthX =													//比率を使って横の長さを出す
		CameraCanLookLengthY * m_aspect;

	//Zが0の位置の見えているライン
	float NowSeeLineRightX	= GotoPos.x + CameraCanLookLengthX;
	float NowSeeLineLeftX	= GotoPos.x - CameraCanLookLengthX;
	float NowSeeLineTopY	= GotoPos.y + CameraCanLookLengthY;
	float NowSeeLineBottomY = GotoPos.y - CameraCanLookLengthY;	
	//======================================================================

	//=====<デットラインをカメラが映していた場合戻してやる>=============
	if(StageCanSeeLineRightX	< NowSeeLineRightX)
	{
		//差分を求めてその量を引く
		float Difference = StageCanSeeLineRightX - NowSeeLineRightX;
		GotoPos.x += Difference;
	}
	if (StageCanSeeLineLeftX > NowSeeLineLeftX)
	{
		//差分を求めてその量を引く
		float Difference = StageCanSeeLineLeftX - NowSeeLineLeftX;
		GotoPos.x += Difference;
	}
	if (StageCanSeeLineTopY < NowSeeLineTopY)
	{
		//差分を求めてその量を引く
		float Difference = StageCanSeeLineTopY - NowSeeLineTopY;
		GotoPos.y += Difference;
	}
	if (StageCanSeeLineBottomY > NowSeeLineBottomY)
	{
		//差分を求めてその量を引く
		float Difference = StageCanSeeLineBottomY - NowSeeLineBottomY;
		GotoPos.y += Difference;
	}
	//======================================================================

	//=====<今いる座標から向かうべき座標を補完しながら移動する>=============
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
