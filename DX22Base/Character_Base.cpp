#include "Character_Base.h"
#include "Character_State.h"
#include "Character_Attack.h"
#include "Scene.h"
#include "Scene00_Game.h"

int Character::m_NewPlayerBit = 0x01;

void Character::InitPlayerBit()
{
	m_NewPlayerBit = 0x01;
}

int Character::GetNewPlayerBit()
{
	int ReturnBit = m_NewPlayerBit;
	m_NewPlayerBit = m_NewPlayerBit << 1;
	return ReturnBit;
}

void Character::Character_Init()
{
	m_PlayerBit = GetNewPlayerBit();
	//0:プレイヤー1,1:プレイヤー2
	int PlayerNum = static_cast<int>(log2f(static_cast<float>(m_PlayerBit)));

	//=====<キャラクターの位置の設定>=============================================
	//キャラクターの番号によってステージの配置場所を変える
	std::vector<CVector3>* startPosV = static_cast<SceneGame*>(CScene::GetScene())->GetStage()->GetCharacterStartPos();
	m_Parameter.Pos = (*startPosV)[PlayerNum];
	//============================================================================
	 
	//=====<キャラクターのUIの位置の設定>=============================================
	CVector2 BasePos(450.0f, 620.0f);
	CVector2 PosDistance(400.0f, 0.0f);

	m_DamageUI.SetBoardColor(static_cast<Character_DamageUI::BOARDCOLOR>(PlayerNum));
	m_DamageUI.SetPos(BasePos + (PosDistance * static_cast<float>(PlayerNum)));
	m_CharacterStock = 3;
	m_DamageUI.SetStockNum(m_CharacterStock);
	//============================================================================

	//=====<当たり判定の設定>=============================================
	SetDefaultCollider();
	//============================================================================

	Init();

	ChangeNextState();

	m_Parameter.JumpCount = 0;
	Character_ColliderInit();
}

void Character::Character_Uninit()
{
	//========================================
	// 終了処理
	//========================================
	m_CharacterStateContext.ReleaseAllState();
	Uninit();
}

void Character::Character_Update()
{
	m_Parameter.OldPos = m_Parameter.Pos;

	Update();

	//========================================
	// 各ステータスのアップデート
	//========================================
	m_CharacterStateContext.StateUpdate();

	//========================================
	// 各ステータスが切り替わっていたら
	//========================================
	ChangeNextState();

	//========================================
	// 位置の設定
	//========================================
	m_CharacterCollider.SetBasePos(m_Parameter.Pos);

	//========================================
	// UIの更新
	//========================================
	m_DamageUI.GetDamageUI()->SetNumber(static_cast<int>(m_DamagePercentage));
	m_DamageUI.Update();
}

void Character::Character_Draw()
{
	Draw();

	//========================================
	// キャラクターの描画
	//========================================
	m_CharacterModel.SetPosition(m_Parameter.Pos);
	m_CharacterModel.SetRotate(m_Parameter.Rotate);
	m_CharacterModel.Draw();
}

void Character::Character_UIDraw()
{
	//========================================
	// UIの描画
	//========================================
	m_DamageUI.Draw();
}

void Character::DrawCollider()
{
	//========================================
	// 当たり判定の描画
	//========================================
	m_CharacterCollider.DrawCollider();
}


void Character::ChangeNextState()
{
	//========================================
	// 次のステートを設定していたら変更する
	//========================================

	if (m_CharacterStateContext.GetNextState() != nullptr)
	{
		m_CharacterStateContext.StateUninit();

		m_CharacterStateContext.ChangeNextState();

		Character_State* pState = static_cast<Character_State*>(m_CharacterStateContext.GetNowState());
		pState->SetCharacter(this);
		pState->SetController(m_Controller);
		pState->SetCharacterParameter(&m_Parameter);
		pState->SetStage(m_pStage);
		pState->SetModelDrawer(&m_CharacterModel);
		pState->SetCharacterCollider(&m_CharacterCollider);
		pState->SetAttackCollider(&m_AttackCollider);
		pState->SetMoveParameter(&m_MoveParameter);
		pState->SetJumpParameter(&m_JumpParameter);
		pState->SetBlowAwayParameter(&m_BlowAwayParameter);

		m_CharacterStateContext.StateInit();
	}
}

void Character::SetCharacterController(PlayerController* pController) 	//コントローラーを設定
{
	m_Controller = pController;
	if (m_CharacterStateContext.GetNowState() != nullptr)
	{
		Character_State* pState = static_cast<Character_State*>(m_CharacterStateContext.GetNowState());
		pState->SetController(pController);
	}
}

void Character::SetStage(Stage* pStage)								//ステージを設定
{
	m_pStage = pStage;
	if (m_CharacterStateContext.GetNowState() != nullptr)
	{
		Character_State* pState = static_cast<Character_State*>(m_CharacterStateContext.GetNowState());
		pState->SetStage(pStage);
	}
}