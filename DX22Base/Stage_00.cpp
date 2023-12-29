#include "Stage_00.h"

void Stage00::Init()
{
	ModelDrawer::LoadModel("Assets/Stage/Block/konnkurito/blocks_konnkurito.fbx", "ConcreteBlock", 0.0125f);

	//横幅10.0f,縦幅3.0f,奥行3.0f
	//中心0.0f, 1.5f,0.0f

	const int StageWidthX = 10;
	const int StageHeightY = 3;
	const int StageDepthZ = 1;
	CVector3 BlockSize = CVector3(2.0f, 2.0f, 2.0f);

	//ステージ情報
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

	//ブロック一つ一つの位置の設定
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


	//キャラクターの最初の位置の設定
	CVector3 characterstartpos;
	characterstartpos = CVector3(-5.0f, 0.0f, 0.0f);
	m_CharacterStartPos.push_back(characterstartpos);
	characterstartpos = CVector3(5.0f, 0.0f, 0.0f);
	m_CharacterStartPos.push_back(characterstartpos);
	characterstartpos = CVector3(0.0f, 0.0f, 0.0f);
	m_CharacterStartPos.push_back(characterstartpos);


	m_CameraMaxRightX	= 3.0f;
	m_CameraMaxLeftX	= -3.0f;
	m_CameraMaxTopY		= 15.0f;
	m_CameraMaxBottomY	= -15.0f;

	m_DeadLineRightX	= 30.0f;
	m_DeadLineLeftX		= -30.0f;
	m_DeadLineTopY		= 20.0f;
	m_DeadLineBottomY	= -20.0f;

	//キャラクターがリスポーンする位置を設定
	m_BaseRespawnPos = CVector3(0.0f, 3.0f, 0.0f);
	m_RespawnDistance = 1.0f;

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
