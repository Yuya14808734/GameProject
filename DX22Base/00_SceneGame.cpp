#include "00_SceneGame.h"
#include "CameraManager.h"
#include "00_CameraDebug.h"
#include "ModelDrawer.h"
#include "Geometory.h"
#include "Input.h"
#include "Stage_00.h"
#include "Character_00.h"

bool ColliderDraw = false;
ModelDrawer errorModel;
ModelDrawer UnityChanModel;
float AnimeTime = 0.0f;

void SceneGame::Init()
{
#if 1
	CameraManager::GetInstance().CreateCamera(new CameraDebug(), "DebugCamera");
	CameraManager::GetInstance().SetSceneCamera("DebugCamera");

	m_pStage = new Stage00();
	m_pStage->Stage_Init();
	m_Characters.push_back(new Character_00());
	m_Characters[0]->Character_Init();

#else

	//モデルデバッグ用
	//ユニティちゃんの読み込み
	ModelDrawer::LoadModel("Assets/unitychan/unitychan.fbx", "UnityChan", 0.003f);
	ModelDrawer::LoadAnime("Assets/unitychan/walk.fbx", "Walk", "UnityChan");
	ModelDrawer::LoadModel("Assets/Character00/Model02.fbx", "Character00", 0.001f);
	//エラーが出るというか描画してくれないモデルの描画
	errorModel.SetModel("Character00");
	errorModel.SetPosition(CVector3::GetZero());
	errorModel.SetScale({ 1.0f, 1.0f, 1.0f });
	//ユニティちゃんの描画
	UnityChanModel.SetModel("UnityChan");
	UnityChanModel.PlayAnime("Walk", true);
	AnimeTime = 0.0f;
	UnityChanModel.SetPosition(CVector3(1.0f, 0.0f, 0.0f));
	UnityChanModel.SetScale(CVector3(5.0f, 5.0f, 5.0f));
	UnityChanModel.SetRotate(CVector3(0.0f,180.0f,0.0f));

#endif // 1
}

void SceneGame::Uninit()
{
	for (auto it = m_Characters.begin(); it != m_Characters.end();)
	{
		(*it)->Character_Uninit();
		delete (*it);
		it = m_Characters.erase(it);
	}

	m_pStage->Stage_Uninit();
	delete m_pStage;
	CameraManager::GetInstance().DestroyCamera("DebugCamera", true);
}

void SceneGame::Update()
{
	//=====<キャラクターのアップデート>=====
	//ここで攻撃や移動などのアップデートを行う
	for(std::vector<Character*>::iterator it = m_Characters.begin();
	it != m_Characters.end(); it++)
	{
		(*it)->Character_Update();				//キャラクターのアップデートを行う
		(*it)->Character_ColliderInit();		//コライダーの情報を初期化してやる
	}

	//=====<キャラクター同士の当たり判定>=====
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
			float NowHarfDistanceX = (pFirstCollider->GetPos().x - pSecondCollider->GetPos().x) * 0.5f;
			CVector3 CenterPos = pSecondCollider->GetPos() + CVector3(NowHarfDistanceX,0.0f,0.0f);

			float Direct = NowHarfDistanceX < 0.0f ? -1.0f : 1.0f;

			(*it_first)->SetPos(CenterPos + CVector3(pFirstCollider->GetSize().x * Direct,0.0f,0.0f));
			(*it_second)->SetPos(CenterPos + CVector3(pFirstCollider->GetSize().x * Direct, 0.0f, 0.0f));
		}
	}	

	//=====<キャラクターの攻撃の当たり判定>=====
	//上で設定した攻撃の当たり判定を使って
	//キャラクター同士の攻撃の当たり判定を行う
	for (Character* AttackCharacter : m_Characters)
	{
		//攻撃しているキャラクターから攻撃の当たり判定を取ってくる
		std::vector<Character::AttackParam>& attackParamVector = AttackCharacter->GetAttackCollider();

		if (AttackCharacter->GetState() != Character::STATE::ATTACK)
		{
			continue;
		}

		//配列の頭から攻撃を見ていく
		for (Character::AttackParam& Character_Attack : attackParamVector)
		{
			if(!Character_Attack.m_Use)
			{
				continue;
			}

			for (Character* ReceiveCharacter : m_Characters)
			{
				//攻撃しているキャラクターと受けるキャラクターが同じ場合
				if(AttackCharacter == ReceiveCharacter)
				{
					continue;
				}

				//攻撃と受けるキャラクターの当たり判定
				Character_Attack.m_BoxCollider.CollisionBox(
					*ReceiveCharacter->GetCharacterCollider()
				);
			}
		}
	}

	//=====<キャラクターとステージの当たり判定>=====
	std::vector<BoxCollider>* pStageCollider = m_pStage->GetStageCollider();
	
	for (std::vector<Character*>::iterator it_Character = m_Characters.begin();
		it_Character != m_Characters.end(); it_Character++)
	{
		BoxCollider* pCharacterCollider = (*it_Character)->GetCharacterCollider();

		//Xの移動だけの当たり判定
		for (std::vector<BoxCollider>::iterator it_Stage = pStageCollider->begin();
			it_Stage != pStageCollider->end(); it_Stage++)
		{
			CVector3 DiffPos = (*it_Character)->GetPos() - (*it_Character)->GetOldPos();		//前の位置から今の位置まで移動したベクトル
			CVector3 HitSize = (pCharacterCollider->GetSize() + (*it_Stage).GetSize()) * 0.5f;
			float NowDistanceX =  pCharacterCollider->GetPos().x - (*it_Stage).GetPos().x;
			float AbsNowDistanceX = fabsf(NowDistanceX);
			float OldDistanceY = (pCharacterCollider->GetPos().y - DiffPos.y) - (*it_Stage).GetPos().y;
			float AbsOldDistanceY = fabsf(OldDistanceY);
			float OldDistanceZ = (pCharacterCollider->GetPos().z - DiffPos.z) - (*it_Stage).GetPos().z;
			float AbsOldDistanceZ = fabsf(OldDistanceZ);
			
			//Xの移動だけして当たっていたら
			if(AbsNowDistanceX < HitSize.x &&
				AbsOldDistanceY < HitSize.y &&
				AbsOldDistanceZ < HitSize.z)
			{
				CVector3 newPos = (*it_Character)->GetPos();
				float MoveDist = DiffPos.x < 0.0f ? HitSize.x : -HitSize.x;
				newPos.x = (*it_Stage).GetPos().x + MoveDist;
				(*it_Character)->SetPos(newPos);
				
				(*it_Character)->Character_HitWall();
			}
		}

		//Yの移動だけの当たり判定
		for (std::vector<BoxCollider>::iterator it_Stage = pStageCollider->begin();
			it_Stage != pStageCollider->end(); it_Stage++)
		{
			CVector3 DiffPos = (*it_Character)->GetPos() - (*it_Character)->GetOldPos();		//前の位置から今の位置まで移動したベクトル
			CVector3 HitSize = (pCharacterCollider->GetSize() + (*it_Stage).GetSize()) * 0.5f;
			float NowDistanceX = pCharacterCollider->GetPos().x - (*it_Stage).GetPos().x;
			float AbsNowDistanceX = fabsf(NowDistanceX);
			float NowDistanceY = pCharacterCollider->GetPos().y - (*it_Stage).GetPos().y;
			float AbsNowDistanceY = fabsf(NowDistanceY);
			float OldDistanceZ = (pCharacterCollider->GetPos().z - DiffPos.z) - (*it_Stage).GetPos().z;
			float AbsOldDistanceZ = fabsf(OldDistanceZ);

			//Yの移動だけして当たっていたら
			if (AbsNowDistanceX < HitSize.x &&
				AbsNowDistanceY < HitSize.y &&
				AbsOldDistanceZ < HitSize.z)
			{
				CVector3 newPos = (*it_Character)->GetPos();
				float MoveDist = DiffPos.y < 0.0f ?
					HitSize.y - (pCharacterCollider->GetType() == BoxCollider::BOXTYPE::FOOT ? (pCharacterCollider->GetSize().y * 0.5f) : 0.0f) :	//上からあたった
					-HitSize.y;	//下からあたった
				newPos.y = (*it_Stage).GetPos().y + MoveDist;
				(*it_Character)->SetPos(newPos);

				if (DiffPos.y < 0.0f)
				{
					(*it_Character)->Character_HitGround();
				}
				else
				{
					(*it_Character)->Character_HitCeiling();
				}
			}
		}

		//Zの移動だけの当たり判定
		for (std::vector<BoxCollider>::iterator it_Stage = pStageCollider->begin();
			it_Stage != pStageCollider->end(); it_Stage++)
		{
			CVector3 DiffPos = (*it_Character)->GetPos() - (*it_Character)->GetOldPos();		//前の位置から今の位置まで移動したベクトル
			CVector3 HitSize = (pCharacterCollider->GetSize() + (*it_Stage).GetSize()) * 0.5f;
			float NowDistanceX = pCharacterCollider->GetPos().x - (*it_Stage).GetPos().x;
			float AbsNowDistanceX = fabsf(NowDistanceX);
			float NowDistanceY = pCharacterCollider->GetPos().y - (*it_Stage).GetPos().y;
			float AbsNowDistanceY = fabsf(NowDistanceY);
			float NowDistanceZ = pCharacterCollider->GetPos().z - DiffPos.z - (*it_Stage).GetPos().z;
			float AbsNowDistanceZ = fabsf(NowDistanceZ);

			//Zの移動だけして当たっていたら
			if (AbsNowDistanceX < HitSize.x &&
				AbsNowDistanceY < HitSize.y &&
				AbsNowDistanceZ < HitSize.z)
			{
				CVector3 newPos = (*it_Character)->GetPos(); 
				float MoveDist = DiffPos.z < 0.0f ? HitSize.z : -HitSize.z;
				newPos.z = (*it_Stage).GetPos().z + MoveDist;
				(*it_Character)->SetPos(newPos);
			}
		}
	}
}

void SceneGame::Draw()
{

#if 1
	m_pStage->Stage_Draw();
	for (Character* copy : m_Characters)
	{
		copy->Character_Draw();
	}
	if (IsKeyTrigger(VK_RETURN))
	{
		ColliderDraw = !ColliderDraw;
	}
	if (ColliderDraw)
	{
		m_pStage->StageColliderDraw();
		for (Character* CharacterCopy : m_Characters)
		{
			CharacterCopy->DrawCollider();
			
			if (CharacterCopy->GetState() != Character::STATE::ATTACK)
			{
				continue;
			}

			std::vector<Character::AttackParam>& attackVector
				= CharacterCopy->GetAttackCollider();

			for (Character::AttackParam& AttackCopy : attackVector)
			{
				AttackCopy.m_BoxCollider.DrawCollider();
			}

		}
	}

#else
	//モデルデバッグ用
	errorModel.Draw();
	AnimeTime += 0.01f;
	if (AnimeTime > 1.0f)
	{
		AnimeTime -= 1.0f;
	}
	UnityChanModel.SetAnimeLerp(AnimeTime);
	UnityChanModel.Draw();
#endif // 0	
}

std::vector<Character*>& SceneGame::GetCharacter()
{
	return m_Characters;
}

Stage* SceneGame::GetStage()
{
	return m_pStage;
}
