#include "Character_01.h"
#include "Input.h"
#include "MiniWindow.h"

//==============================================
//==============================================
//==============================================


void Character_01::Init()
{
	m_stateWindow.Init_MiniWindow();

	//=====<動きのパラメータの設定>======================================
	MOVEPARAMETER moveParameter;
	moveParameter.WalkSpeed = 4.0f / 60.0f;
	moveParameter.DashSpeed = 8.0f / 60.0f;
	moveParameter.AirSideMoveSpeed = 4.0f / 60.0f;
	moveParameter.Friction = 0.65f;
	moveParameter.AirDrag = 0.98f;
	SetMoveParameter(moveParameter);

	JUMPPARAMETER jumpParameter;
	jumpParameter.MaxJumpCount = 2;
	jumpParameter.MiniJumpPushButtonCount = 2;
	jumpParameter.JumpChargeCount = 3;
	jumpParameter.FirstMiniJumpPower = 0.15f;
	jumpParameter.FirstJumpPower = 0.3f;
	jumpParameter.SecondJumpPower = 0.7f;
	jumpParameter.JumpUpReduction = 0.93f;
	jumpParameter.FallDownGravity = -0.01f;
	jumpParameter.DefaultFallSpeed = -0.15f;
	jumpParameter.SpeedUpFallSpeed = -0.3f;
	jumpParameter.ChangeFallSpeed = 0.05f;
	SetjumpParameter(jumpParameter);

	BLOWAWAYPARAMETER blowAwayParameter;
	blowAwayParameter.SmashMitigation = 0.9f;
	blowAwayParameter.VectorChangePower = 0.02f;
	blowAwayParameter.MinimumSmashLength = 0.03f;
	SetBlowAwayParameter(blowAwayParameter);
	//============================================================================

	//=====<モデル・アニメーションの読み込み>======================================
	ModelDrawer::LoadModel("Assets/LoboNock/characterrobonock.fbx", "LoboNock", 0.003f);
	ModelDrawer::LoadAnime("Assets/LoboNock/character_anim_walk.fbx", "Idle", "LoboNock");
	//============================================================================

	//=====<モデル・アニメーションの設定>=========================================
	m_CharacterModel.SetModel("LoboNock");
	m_CharacterModel.PlayAnime("Idle", true);
	//============================================================================

	//=====<位置の設定>===========================================================
	m_CharacterModel.SetPosition(CVector3(0.0f, 3.0f, 0.0f));
	m_CharacterModel.SetRotate(CVector3::GetZero());
	m_CharacterModel.SetScale(CVector3(5.0f, 5.0f, 5.0f));
	//============================================================================

	m_stateWindow.SetCharacter(this);

	SetNextState(Character::STATE::State_StartAnime);

	m_DamageUI.SetCharacterIconImage("Assets/CharacterImage/IconImage_UnityChan.png");
}


void Character_01::SetDefaultCollider()
{
	m_CharacterCollider.SetType(BoxCollider::BOXTYPE::FOOT);
	m_CharacterCollider.SetBasePos(m_Parameter.Pos);
	m_CharacterCollider.SetShiftVec(CVector3::GetZero());
	m_CharacterCollider.SetSize(CVector3(0.7f, 2.0f, 1.0f));
}

State* Character_01::SetNextState(STATE NextState)
{
	switch (NextState)
	{
	case Character::STATE::State_None:
		break;
	case Character::STATE::State_AirMove:
		break;
	case Character::STATE::State_BlowAway:
		break;
	case Character::STATE::State_Dash:
		break;
	case Character::STATE::State_Dead:
		break;
	case Character::STATE::State_Down:
		break;
	case Character::STATE::State_FallDown:
		break;
	case Character::STATE::State_GameOver:
		break;
	case Character::STATE::State_HitStop:
		break;
	case Character::STATE::State_Idle:
		break;
	case Character::STATE::State_JumpIn:
		break;
	case Character::STATE::State_Jump:
		break;
	case Character::STATE::State_LeanBack:
		break;
	case Character::STATE::State_StartAnime:
		break;
	case Character::STATE::State_Respawn:
		break;
	case Character::STATE::State_WakeUp:
		break;
	case Character::STATE::State_Walk:
		break;
	case Character::STATE::State_Attack11:
		break;
	case Character::STATE::State_Attack12:
		break;
	case Character::STATE::State_Attack13:
		break;
	case Character::STATE::State_AttackAirN:
		break;
	case Character::STATE::State_AttackDS:
		break;
	case Character::STATE::State_AttackS2:
		break;
	}

	return m_CharacterStateContext.GetNextState();
}

void Character_01::Uninit()
{
	m_stateWindow.Uninit_MiniWindow();
}

void Character_01::Update()
{

}

void Character_01::Draw()
{

}
