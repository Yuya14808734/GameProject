#include "00_SceneGame.h"
#include "CameraManager.h"
#include "00_CameraDebug.h"
#include "ModelDrawer.h"

ModelDrawer pModel1;
ModelDrawer pModel2;
float animeTime = 0.0f;

void SceneGame::Init()
{
	CameraManager::GetInstance().CreateCamera(new CameraDebug(),"DebugCamera");
	CameraManager::GetInstance().SetSceneCamera("DebugCamera");
	ModelDrawer::LoadModel("Assets/unitychan/unitychan.fbx","UnityChan");
	ModelDrawer::LoadAnime("Assets/unitychan/walk.fbx","Walk", "UnityChan");
	ModelDrawer::LoadAnime("Assets/unitychan/run.fbx","Run", "UnityChan");
	pModel1.SetModel("UnityChan");
	pModel1.PlayAnime("Walk", true);
	pModel1.SetAnimeTime(0.0f);
	pModel1.SetPosition(CVector3(0.0f, 0.0f, 0.0f));
	pModel1.SetScale(CVector3(5.0f, 5.0f, 5.0f));

	pModel2.SetModel("UnityChan");
	pModel2.PlayAnime("Run", true);
	pModel2.SetAnimeTime(0.0f);
	pModel2.SetPosition(CVector3(100.0f, 0.0f, 0.0f));
	pModel2.SetScale(CVector3(5.0f, 5.0f, 5.0f));
}

void SceneGame::Uninit()
{
	CameraManager::GetInstance().DestroyCamera("DebugCamera", true);
}

void SceneGame::Update()
{
	//キャラクターのアップデート
	//ここで攻撃や移動などのアップデートを行う
	for(std::vector<Character*>::iterator it = m_Characters.begin();
	it != m_Characters.end(); it++)
	{
		(*it)->Character_Update();
	}

	//キャラクター同士の当たり判定
	//四角と四角
	for (std::vector<Character*>::iterator it_first = m_Characters.begin();
		it_first != m_Characters.end();it_first++)
	{
		std::vector<Character*>::iterator it_second = it_first + 1;
		for (; it_second != m_Characters.end(); it_second++)
		{
			//四角コライダーの取得
			BoxCollider* pFirstCollider = (*it_first)->GetCharacterCollider();
			BoxCollider* pSecondCollider = (*it_second)->GetCharacterCollider();

			//四角同士の当たり判定を行う
			if (!pFirstCollider->CollisionBox(*pSecondCollider))
			{
				//当たっていない場合
				return;
			}

			//めり込んだ半分の位置で移動してやる
			float NowHarfDistanceX = (pFirstCollider->pos.x - pSecondCollider->pos.x) * 0.5f;
			CVector3 CenterPos = pSecondCollider->pos + CVector3(NowHarfDistanceX,0.0f,0.0f);

			float Direct = NowHarfDistanceX < 0.0f ? -1.0f : 1.0f;

			(*it_first)->SetPos(CenterPos + CVector3(pFirstCollider->size.x * Direct,0.0f,0.0f));
			(*it_second)->SetPos(CenterPos + CVector3(pFirstCollider->size.x * Direct, 0.0f, 0.0f));
		}
	}	

	//キャラクターの攻撃の当たり判定
	//上で求めた攻撃の当たり判定を使って
	//キャラクター同士の攻撃の当たり判定を行う
	//円と円


	//キャラクターとステージの当たり判定
	//点と四角
	std::vector<BoxCollider>* pStageCollider = m_pStage->GetStageCollider();
	
	for (std::vector<Character*>::iterator it_Character = m_Characters.begin();
		it_Character != m_Characters.end(); it_Character++)
	{
		BoxCollider* pCharacterCollider = (*it_Character)->GetCharacterCollider();

		//当たり判定を取る

		//Xの移動だけの当たり判定
		for (std::vector<BoxCollider>::iterator it_Stage = pStageCollider->begin();
			it_Stage != pStageCollider->end(); it_Stage++)
		{
			CVector3 DiffPos = (*it_Character)->GetPos() - (*it_Character)->GetOldPos();		//前の位置から今の位置まで移動したベクトル
			CVector3 HitSize = (pCharacterCollider->size - (*it_Stage).size) * 0.5f;
			float NowDistanceX =  pCharacterCollider->pos.x - (*it_Stage).pos.x;
			float AbsNowDistanceX = fabsf(NowDistanceX);
			float OldDistanceY = (pCharacterCollider->pos.y - DiffPos.y) - (*it_Stage).pos.y;
			float AbsOldDistanceY = fabsf(OldDistanceY);
			float OldDistanceZ = (pCharacterCollider->pos.z - DiffPos.z) - (*it_Stage).pos.z;
			float AbsOldDistanceZ = fabsf(OldDistanceZ);
			
			//Xの移動だけして当たっていたら
			if(AbsNowDistanceX < HitSize.x &&
				AbsOldDistanceY < HitSize.y &&
				AbsOldDistanceZ < HitSize.z)
			{
				CVector3 newPos = (*it_Character)->GetPos();
				newPos.x = (*it_Stage).pos.x + NowDistanceX < 0.0f ? -HitSize.x : HitSize.x;
				(*it_Character)->SetPos(newPos);
			}
		}

		//Yの移動だけの当たり判定
		for (std::vector<BoxCollider>::iterator it_Stage = pStageCollider->begin();
			it_Stage != pStageCollider->end(); it_Stage++)
		{
			CVector3 DiffPos = (*it_Character)->GetPos() - (*it_Character)->GetOldPos();		//前の位置から今の位置まで移動したベクトル
			CVector3 HitSize = (pCharacterCollider->size - (*it_Stage).size) * 0.5f;
			float NowDistanceX = pCharacterCollider->pos.x - (*it_Stage).pos.x;
			float AbsNowDistanceX = fabsf(NowDistanceX);
			float NowDistanceY = pCharacterCollider->pos.y - (*it_Stage).pos.y;
			float AbsNowDistanceY = fabsf(NowDistanceY);
			float OldDistanceZ = (pCharacterCollider->pos.z - DiffPos.z) - (*it_Stage).pos.z;
			float AbsOldDistanceZ = fabsf(OldDistanceZ);

			//Xの移動だけして当たっていたら
			if (AbsNowDistanceX < HitSize.x &&
				AbsNowDistanceY < HitSize.y &&
				AbsOldDistanceZ < HitSize.z)
			{
				CVector3 newPos = (*it_Character)->GetPos();
				newPos.y = (*it_Stage).pos.y + NowDistanceY < 0.0f ? -HitSize.y : HitSize.y;
				(*it_Character)->SetPos(newPos);
			}
		}

		//Zの移動だけの当たり判定
		for (std::vector<BoxCollider>::iterator it_Stage = pStageCollider->begin();
			it_Stage != pStageCollider->end(); it_Stage++)
		{
			CVector3 DiffPos = (*it_Character)->GetPos() - (*it_Character)->GetOldPos();		//前の位置から今の位置まで移動したベクトル
			CVector3 HitSize = (pCharacterCollider->size - (*it_Stage).size) * 0.5f;
			float NowDistanceX = pCharacterCollider->pos.x - (*it_Stage).pos.x;
			float AbsNowDistanceX = fabsf(NowDistanceX);
			float NowDistanceY = pCharacterCollider->pos.y - (*it_Stage).pos.y;
			float AbsNowDistanceY = fabsf(NowDistanceY);
			float NowDistanceZ = pCharacterCollider->pos.z - DiffPos.z - (*it_Stage).pos.z;
			float AbsNowDistanceZ = fabsf(NowDistanceZ);

			//Xの移動だけして当たっていたら
			if (AbsNowDistanceX < HitSize.x &&
				AbsNowDistanceY < HitSize.y &&
				AbsNowDistanceZ < HitSize.z)
			{
				CVector3 newPos = (*it_Character)->GetPos();
				newPos.z = (*it_Stage).pos.z + NowDistanceZ < 0.0f ? -HitSize.z : HitSize.z;
				(*it_Character)->SetPos(newPos);
			}
		}
	}


}

void SceneGame::Draw()
{
	Model* pModelData = ModelDrawer::GetModel("UnityChan");
	animeTime += 1.0f / 60.0f;
	pModel1.PlayAnime("Walk", true);
	pModel1.SetAnimeTime(animeTime);
	//pModelData->SetAnimeTime(WalkNo,animeTime);	//アニメーションの時間設定
	pModelData->Step(1.0f / 60.0f);
	pModel1.Draw();

	pModel2.PlayAnime("Run",true);
	pModel2.SetAnimeTime(animeTime);
	//pModelData->SetAnimeTime(RunNo,animeTime);	//アニメーションの時間設定
	pModelData->Step(1.0f / 60.0f);
	pModel2.Draw();
}
