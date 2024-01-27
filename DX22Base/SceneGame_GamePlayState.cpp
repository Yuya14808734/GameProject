#include "SceneGame_GamePlayState.h"
#include "Character_State.h"
#include "Character_Attack.h"
#include "CameraManager.h"

void SceneGame_PlayState::Init()
{
	m_VisibleGo_CountTime = 0;

	CameraManager::GetInstance().SetSceneCamera("GameCamera");
}

void SceneGame_PlayState::Uninit()
{
	m_pGameScene->EffectPause();
}

void SceneGame_PlayState::Update()
{
	if (m_VisibleGo_CountTime < 60)
	{
		m_VisibleGo_CountTime++;
		m_pGameStartCountUI->Update();
	}

	//=====<キャラクターのアップデート>=====
	//ここで攻撃や移動などのアップデートを行う
	for (std::vector<Character*>::iterator it = m_pCharacters->begin();
		it != m_pCharacters->end(); it++)
	{
		(*it)->Character_Update();				//キャラクターのアップデートを行う
		(*it)->Character_ColliderInit();		//コライダーの情報を初期化してやる
												//(当たり判定を行っていないので当たっていないことにする処理)
	}

	//=====<キャラクター同士の当たり判定>=====
	Collision_Player_Player();

	//=====<キャラクターの攻撃の当たり判定>=====
	Collision_Attack_Player();

	//=====<キャラクターとステージの当たり判定>=====
	Collision_Player_Stage();

	//=====<キャラクターのどちらかがストックが無くなったら>=====
	CheckGameEnd();

	//=====<ストックの動き>=====
	m_pStockCountUI->Update();
}

void SceneGame_PlayState::Draw()
{
	//=====<背景の描画>=====
	m_pBackGround->Draw();

	//=====<当たり判定の描画>=====
	ColliderDraw();

	//=====<ステージの描画>=====
	m_pStage->Stage_Draw();

	//=====<キャラクターの描画>=====
	for (Character* copy : (*m_pCharacters))
	{
		copy->Character_Draw();
	}

	//=====<エフェクトの描画>=====
	for (EffectBase* pEffect : (*m_pEffects))
	{
		pEffect->Draw();
	}

	//=====<UIの描画>=====
	EnableDepth(false);

	for (Character* copy : (*m_pCharacters))
	{
		copy->Character_UIDraw();
	}

	//Goの描画(1秒だけ)
	if (m_VisibleGo_CountTime < 60)
	{
		m_pGameStartCountUI->Draw();
	}

	m_pStockCountUI->Draw();

	EnableDepth(true);
}

void SceneGame_PlayState::DrawCharacterStock()
{
	if ((*m_pCharacters).size() > 2)
	{
		return;
	}

	m_pStockCountUI->LerpStart(
		(*m_pCharacters)[0]->GetStock(),
		(*m_pCharacters)[1]->GetStock());
}

void SceneGame_PlayState::Collision_Player_Player()
{
	//=====<キャラクター同士の当たり判定>=====

	//一人目のキャラクターを選択
	for (std::vector<Character*>::iterator it_first = m_pCharacters->begin();
		it_first != m_pCharacters->end(); it_first++)
	{
		//二人目のキャラクターを選択(一人目の次のキャラクター)
		std::vector<Character*>::iterator it_second = it_first + 1;
		for (; it_second != m_pCharacters->end(); it_second++)
		{
			//四角コライダーの取得
			BoxCollider* pFirstCollider = (*it_first)->GetCharacterCollider();
			BoxCollider* pSecondCollider = (*it_second)->GetCharacterCollider();

			//四角同士の当たり判定を行う
			if (!pFirstCollider->CollisionBox(*pSecondCollider))
			{
				//当たっていない場合
				continue;
			}

			//めり込んだ分を跳ね返してやる
			float MaxDistanceX = (pFirstCollider->GetSize().x + pSecondCollider->GetSize().x) * 0.5f;
			float NowDistanceX = (pFirstCollider->GetColliderPos().x - pSecondCollider->GetColliderPos().x);
			float MinDistanceX = MaxDistanceX * 0.5f * 0.1f;
			float MoveX = (MaxDistanceX - fabsf(NowDistanceX)) * 0.02f + MinDistanceX;
			float FirstDirect = NowDistanceX < 0.0f ? -1.0f : 1.0f;
			(*it_first)->SetPos((*it_first)->GetPos() + CVector3::GetRight() * MoveX * FirstDirect);
			(*it_second)->SetPos((*it_second)->GetPos() + CVector3::GetRight() * MoveX * -FirstDirect);
		}
	}
}

void SceneGame_PlayState::Collision_Attack_Player()
{
	//=====<キャラクターとステージの当たり判定>=====
	std::vector<BoxCollider>* pStageCollider = m_pStage->GetStageCollider();

	for (std::vector<Character*>::iterator it_Character = m_pCharacters->begin();
		it_Character != m_pCharacters->end(); it_Character++)
	{
		BoxCollider* pCharacterCollider = (*it_Character)->GetCharacterCollider();

		//Xの移動だけの当たり判定
		for (std::vector<BoxCollider>::iterator it_StageCollider = pStageCollider->begin();
			it_StageCollider != pStageCollider->end(); it_StageCollider++)
		{
			CVector3 DiffPos = (*it_Character)->GetPos() - (*it_Character)->GetOldPos();		//前の位置から今の位置まで移動したベクトル
			CVector3 HitSize = (pCharacterCollider->GetSize() + (*it_StageCollider).GetSize()) * 0.5f;
			float NowDistanceX = pCharacterCollider->GetBasePos().x - (*it_StageCollider).GetBasePos().x;
			float AbsNowDistanceX = fabsf(NowDistanceX);
			float OldDistanceY = (pCharacterCollider->GetBasePos().y - DiffPos.y) - (*it_StageCollider).GetBasePos().y;
			float AbsOldDistanceY = fabsf(OldDistanceY);
			float OldDistanceZ = (pCharacterCollider->GetBasePos().z - DiffPos.z) - (*it_StageCollider).GetBasePos().z;
			float AbsOldDistanceZ = fabsf(OldDistanceZ);

			//Xの移動だけして当たっていたら
			if (AbsNowDistanceX < HitSize.x &&
				AbsOldDistanceY < HitSize.y &&
				AbsOldDistanceZ < HitSize.z)
			{
				CVector3 newPos = (*it_Character)->GetPos();
				float MoveDist = DiffPos.x < 0.0f ? HitSize.x : -HitSize.x;
				newPos.x = (*it_StageCollider).GetBasePos().x + MoveDist;
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
			float NowDistanceX = pCharacterCollider->GetBasePos().x - (*it_Stage).GetBasePos().x;
			float AbsNowDistanceX = fabsf(NowDistanceX);
			float NowDistanceY = pCharacterCollider->GetBasePos().y - (*it_Stage).GetBasePos().y;
			float AbsNowDistanceY = fabsf(NowDistanceY);
			float OldDistanceZ = (pCharacterCollider->GetBasePos().z - DiffPos.z) - (*it_Stage).GetBasePos().z;
			float AbsOldDistanceZ = fabsf(OldDistanceZ);

			//Yの移動だけして当たっていたら
			if (AbsNowDistanceX < HitSize.x &&
				AbsNowDistanceY < HitSize.y &&
				AbsOldDistanceZ < HitSize.z)
			{
				CVector3 newPos = (*it_Character)->GetPos();
				float MoveDist = DiffPos.y < 0.0f ?			//Yの動く量
					//----------------------------------------------------------
					HitSize.y -							//上からあたった時の処理
					(pCharacterCollider->GetType() == BoxCollider::BOXTYPE::FOOT ?
						(pCharacterCollider->GetSize().y * 0.5f) : 0.0f) :
					//----------------------------------------------------------
					-HitSize.y -							//下からあたった時の処理
					(pCharacterCollider->GetType() == BoxCollider::BOXTYPE::FOOT ?
						(pCharacterCollider->GetSize().y * 0.5f) : 0.0f);
					//----------------------------------------------------------

				newPos.y = (*it_Stage).GetBasePos().y + MoveDist;	//ステージからの距離で設定
				(*it_Character)->SetPos(newPos);

				//上から移動したか下から移動したかで判定
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
	}
}

void SceneGame_PlayState::Collision_Player_Stage()
{
	//=====<キャラクターの攻撃の当たり判定>=====
	//上で設定した攻撃の当たり判定を使って
	//キャラクター同士の攻撃の当たり判定を行う
	for (Character* AttackCharacter : (*m_pCharacters))
	{
		//キャラクターが攻撃していなければ次のキャラクターに
		if (static_cast<Character_State*>(AttackCharacter->GetStateContext()->GetNowState())
			->GetType() != Character_State::TYPE::ATTACK)
		{
			continue;
		}

		//攻撃しているキャラクターから攻撃の当たり判定を取ってくる
		std::vector<Character::ATTACKPARAM>& attackParamVector = AttackCharacter->GetAttackCollider();

		//配列の頭から攻撃を見ていく
		for (Character::ATTACKPARAM& Character_Attack : attackParamVector)
		{
			//前のフレームに依存しないビットはここで0にしておく
			Character_Attack.m_HitCharacterBit = 0x00;			//このフレームで当たったキャラクター
			Character_Attack.m_HitTriggerCharacterBit = 0x00;	//このフレームで初めて当たったキャラクター

			//この攻撃の当たり判定は使わない
			if (!Character_Attack.m_Use)
			{
				continue;
			}

			//攻撃を受けるキャラクター
			for (Character* HitCharacter : (*m_pCharacters))
			{
				//攻撃しているキャラクターと受けるキャラクターが同じ場合
				if (AttackCharacter == HitCharacter)
				{
					continue;
				}

				//当てるキャラクターが無敵の場合当たり判定を行わない
				if (HitCharacter->IsInvincible())
				{
					continue;
				}

				//攻撃と受けるキャラクターの当たり判定
				if (Character_Attack.m_BoxCollider.CollisionBox(*HitCharacter->GetCharacterCollider()))
				{
					//当たったキャラクターの情報を入れる
					Character_Attack.m_HitCharacterBit |= HitCharacter->GetCharacterBit();				//今のフレームで当たったキャラクター
					Character_Attack.m_HitTriggerCharacterBit
						= ~Character_Attack.m_haveHitCharacterBit & HitCharacter->GetCharacterBit();	//始めて当たったキャラクター
					Character_Attack.m_haveHitCharacterBit |= HitCharacter->GetCharacterBit();			//今まで当たったことのあるキャラクター

					//攻撃を当てるの判定
					if ((HitCharacter->GetCharacterBit() & Character_Attack.m_CanAttackCharacterBit) != 0x00)
					{
						//====<当たった時の処理>====
						CVector3 HitCharacterPos = HitCharacter->GetPos();
						HitCharacterPos.y += 0.01f;			//少し浮かさないと下で地面に当たってしまう
						HitCharacter->SetPos(HitCharacterPos);

						//当たった時の処理をする
						static_cast<Character_AttackState*>(AttackCharacter->GetStateContext()->GetNowState())
							->HitCharacter(HitCharacter);
					}
				}
			}
		}
	}
}

void SceneGame_PlayState::CheckGameEnd()
{
	bool isGameOver = false;

	for (std::vector<Character*>::iterator it = m_pCharacters->begin();
		it != m_pCharacters->end(); it++)
	{
		isGameOver = isGameOver || (*it)->GetGameOver();
	}

	if (isGameOver)
	{
		m_pGameScene->SetNextState(SceneGame::GAMESTATE::GAMEEND);
	}
}

void SceneGame_PlayState::ColliderDraw()
{
	//=====<当たり判定の描画>=====
	if (IsKeyTrigger(VK_RETURN))
	{
		m_ColliderDraw = !m_ColliderDraw;
	}

	if (m_ColliderDraw)
	{
		m_pStage->StageColliderDraw();
		for (Character* CharacterCopy : (*m_pCharacters))
		{
			CharacterCopy->DrawCollider();

			//キャラクターが攻撃していなければ次のキャラクターに
			if (static_cast<Character_State*>(CharacterCopy->GetStateContext()->GetNowState())
				->GetType() != Character_State::TYPE::ATTACK)
			{
				continue;
			}

			std::vector<Character::ATTACKPARAM>& attackVector
				= CharacterCopy->GetAttackCollider();

			for (Character::ATTACKPARAM& AttackCopy : attackVector)
			{
				if (!AttackCopy.m_Use)
				{
					continue;
				}
				AttackCopy.m_BoxCollider.DrawCollider();
			}
		}
	}
}
