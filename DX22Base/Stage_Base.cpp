#include "Stage_Base.h"
#include "Geometory.h"

void Stage::Stage_Init()
{
	Init();
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
		SetGeometoryTranslate(copy.GetPos());
		SetGeometoryScaling(copy.GetSize());
		DrawBox();
	}
}

std::vector<BoxCollider>* Stage::GetStageCollider() const
{
	return const_cast<std::vector<BoxCollider>*>(&m_StageCollider);
}
