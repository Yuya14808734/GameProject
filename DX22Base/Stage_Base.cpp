#include "Stage_Base.h"
#include "Geometory.h"

void Stage::Stage_Init()
{
	Init();
	m_UseRespawnNum = 0;
}

void Stage::Stage_Uninit()
{
	Uninit();
}

void Stage::Stage_Update()
{
	Update();
}

void Stage::Stage_Draw()
{
	Draw();

	for (ModelDrawer& copy : m_ModelDrawer)
	{
		copy.Draw();
	}
}

void Stage::StageColliderDraw()
{
	SetGeometoryRotation(0.0f, 0.0f, 0.0f);

	for (BoxCollider& copy : m_StageCollider)
	{
		SetGeometoryTranslate(copy.GetBasePos());
		SetGeometoryScaling(copy.GetSize());
		DrawBox();
	}
}

std::vector<BoxCollider>* Stage::GetStageCollider() const
{
	return const_cast<std::vector<BoxCollider>*>(&m_StageCollider);
}

std::vector<CVector3>* Stage::GetCharacterStartPos() const
{
	return const_cast<std::vector<CVector3>*>(&m_CharacterStartPos);
}

float Stage::GetCameraMaxRightX()
{
	return m_CameraMaxRightX;
}

float Stage::GetCameraMaxLeftX()
{
	return m_CameraMaxLeftX;
}

float Stage::GetCameraMaxTopY()
{
	return m_CameraMaxTopY;
}

float Stage::GetCameraMaxBottomY()
{
	return m_CameraMaxBottomY;
}

float Stage::GetDeadLineRightX()
{
	return m_DeadLineRightX;
}

float Stage::GetDeadLineLeftX()
{
	return m_DeadLineLeftX;
}

float Stage::GetDeadLineTopY()
{
	return m_DeadLineTopY;
}

float Stage::GetDeadLineBottomY()
{
	return m_DeadLineBottomY;
}

CVector3 Stage::AddRespawn()
{
	CVector3 returnVector = m_BaseRespawnPos;

	//リスポーンで使っている場所の数
	m_UseRespawnNum++;
	int TempRespawnNum = m_UseRespawnNum - 1;

	//奇数だと左、偶数だと右に行く
	if (TempRespawnNum % 2 == 0)
	{
		//偶数の場合、左に行く
		TempRespawnNum = m_UseRespawnNum / 2;
		returnVector.x = returnVector.x - m_RespawnDistance * static_cast<float>(TempRespawnNum);
	}
	else
	{
		//奇数の場合、右に行く
		TempRespawnNum = m_UseRespawnNum / 2 + 1;
		returnVector.x = returnVector.x + m_RespawnDistance * static_cast<float>(TempRespawnNum);
	}

	return returnVector;
}

void Stage::MinaRespawn()
{
	m_UseRespawnNum--;
}
