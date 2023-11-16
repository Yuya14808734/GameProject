#include "Stage_Base.h"

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
}

std::vector<BoxCollider>* Stage::GetStageCollider() const
{
	return const_cast<std::vector<BoxCollider>*>(&m_StageCollider);
}
