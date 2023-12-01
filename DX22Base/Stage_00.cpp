#include "Stage_00.h"

void Stage00::Init()
{
	ModelDrawer::LoadModel("Assets/Stage/Block/konnkurito/blocks_konnkurito.fbx", "ConcreteBlock", 0.0125f);

	//â°ïù10.0f,ècïù3.0f,âúçs3.0f
	//íÜêS0.0f, 1.5f,0.0f

	const int StageWidthX = 10;
	const int StageHeightY = 3;
	const int StageDepthZ = 1;
	CVector3 BlockSize = CVector3(2.0f, 2.0f, 2.0f);

	int stage[StageWidthX * StageHeightY] =
	{
		1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,
		0,1,1,1,1,1,1,1,1,0,
	};


	CVector3 StageSize = CVector3(
		static_cast<float>(StageWidthX) * BlockSize.x,
		static_cast<float>(StageHeightY) * BlockSize.y,
		static_cast<float>(StageDepthZ) * BlockSize.z);

	CVector3 TopLeftPos = CVector3(
		0.0f - (StageSize.x / 2.0f) + (BlockSize.x * 0.5f),
		0.0f - (BlockSize.y * 0.5f),
		0.0f
	);

	for (int x = 0; x < StageWidthX; x++)
	{
		for (int y = 0; y < StageHeightY; y++)
		{
			switch (stage[x + (StageWidthX * y)])
			{
			case 0:
			{
				int a = 0;
				a++;
			}
				break;
			case 1:
			{
				CVector3 BlockPos(
					TopLeftPos.x + (BlockSize.x * x),
					TopLeftPos.y - (BlockSize.y * y),
					0.0f
				);

				ModelDrawer tempModelDrawer;
				
				switch (1)
				{
				case 1:
					tempModelDrawer.SetModel("ConcreteBlock");
					break;
				case 2:
					tempModelDrawer.SetModel("LeafBlock");
					break;
				default:
					break;
				}
				tempModelDrawer.SetPosition(BlockPos);
				tempModelDrawer.SetScale(BlockSize);
				m_ModelDrawer.push_back(tempModelDrawer);

				BoxCollider tempBoxCollider;
				tempBoxCollider.SetPos(BlockPos);
				tempBoxCollider.SetSize(BlockSize);				
				m_StageCollider.push_back(tempBoxCollider);
				
			}
				break;
			default:
				break;
			}
		}
	}
}

void Stage00::Uninit()
{

}

void Stage00::Update()
{

}

void Stage00::Draw()
{

}
