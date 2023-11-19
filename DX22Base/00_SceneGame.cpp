#include "00_SceneGame.h"

void SceneGame::Init()
{

}

void SceneGame::Uninit()
{

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
		for (std::vector<BoxCollider>::iterator it_Stage = pStageCollider->begin();
			it_Stage != pStageCollider->end(); it_Stage++)
		{
			CVector3 DiffPos = (*it_Character)->GetPos() - (*it_Character)->GetOldPos();		//前の位置から今の位置まで移動したベクトル
			CVector3 HitSize = (pCharacterCollider->size - (*it_Stage).size) * 0.5f;
			float NowDistanceX =  pCharacterCollider->pos.x - (*it_Stage).pos.x;
			float AbsNowDistanceX = fabsf(NowDistanceX);
			CVector3 OldDistance = (pCharacterCollider->pos - DiffPos) - (*it_Stage).pos;
			CVector3 AbsOldDistance = OldDistance.Abs();

			//Xの移動
			if(AbsNowDistanceX < HitSize.x &&
				AbsOldDistance.y < HitSize.y &&
				AbsOldDistance.z < HitSize.z)
			{
				CVector3 newPos = (*it_Character)->GetPos();
				newPos.x = (*it_Stage).pos.x + NowDistanceX < 0.0f ? -HitSize.x : HitSize.x;
				(*it_Character)->SetPos(newPos);
			}
		}

		//Yの移動

		//Zの移動

	}


}

void SceneGame::Draw()
{

}
