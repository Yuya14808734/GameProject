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

}

void SceneGame::Draw()
{

}
