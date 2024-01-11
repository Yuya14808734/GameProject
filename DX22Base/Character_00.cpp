#include "Character_00.h"
#include "Input.h"
#include "MiniWindow.h"

//==============================================
#include "Character00_AirMoveState.h"
#include "Character00_BlowAwayState.h"
#include "Character00_DashState.h"
#include "Character00_DeadState.h"
#include "Character00_DownState.h"
#include "Character00_FallDownState.h"
#include "Character00_GameOverState.h"
#include "Character00_HitStopState.h"
#include "Character00_IdleState.h"
#include "Character00_JumpInState.h"
#include "Character00_JumpState.h"
#include "Character00_LeanBackState.h"
#include "Character00_RespawnState.h"
#include "Character00_WakeUpState.h"
#include "Character00_WalkState.h"
//==============================================
#include "Character00_Attack11.h"
#include "Character00_Attack12.h"
#include "Character00_Attack13.h"
#include "Character00_AttackAirN.h"
#include "Character00_AttackDS.h"
#include "Character00_AttackS2.h"
//==============================================


void Character_00::Init()
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
	ModelDrawer::LoadModel("Assets/unitychan/unitychan.fbx", "UnityChan", 0.003f);
	ModelDrawer::LoadAnime("Assets/unitychan/unitychan_ARpose2.fbx", "Pose2", "UnityChan");
	ModelDrawer::LoadAnime("Assets/unitychan/unitychan_WAIT00.fbx", "Idle", "UnityChan");
	ModelDrawer::LoadAnime("Assets/unitychan/unitychan_UMATOBI00.fbx", "Umatobi", "UnityChan");
	ModelDrawer::LoadAnime("Assets/unitychan/unitychan_WAIT04.fbx", "WAIT04", "UnityChan");
	ModelDrawer::LoadAnime("Assets/unitychan/unitychan_WALK00_F.fbx", "Walk", "UnityChan");
	ModelDrawer::LoadAnime("Assets/unitychan/unitychan_RUN00_F.fbx", "Dash", "UnityChan");
	ModelDrawer::LoadAnime("Assets/unitychan/unitychan_JUMP00B.fbx", "Jump", "UnityChan");
	ModelDrawer::LoadAnime("Assets/unitychan/unitychan_DAMAGED00.fbx", "Damage00", "UnityChan");
	ModelDrawer::LoadAnime("Assets/unitychan/unitychan_DAMAGED01.fbx", "Damage01", "UnityChan");
	ModelDrawer::LoadAnime("Assets/unitychan/unitychan_SLIDE00.fbx", "Slide00", "UnityChan");
	//============================================================================
	
	//=====<モデル・アニメーションの設定>=========================================
	m_CharacterModel.SetModel("UnityChan");
	m_CharacterModel.PlayAnime("Walk",true);
	//============================================================================

	//=====<位置の設定>===========================================================
	m_CharacterModel.SetPosition(CVector3(0.0f, 3.0f, 0.0f));
	m_CharacterModel.SetRotate(CVector3::GetZero());
	m_CharacterModel.SetScale(CVector3(5.0f, 5.0f, 5.0f));
	//============================================================================

	m_stateWindow.SetCharacter(this);

	SetNextState(Character::STATE::State_Idle);

	m_FrameCount = 0;

	m_DamageUI.SetCharacterIconImage("Assets/CharacterImage/IconImage_UnityChan.png");
}


void Character_00::SetDefaultCollider()
{
	m_CharacterCollider.SetType(BoxCollider::BOXTYPE::FOOT);
	m_CharacterCollider.SetBasePos(m_Parameter.Pos);
	m_CharacterCollider.SetShiftVec(CVector3::GetZero());
	m_CharacterCollider.SetSize(CVector3(1.0f, 2.0f, 1.0f));
}

State* Character_00::SetNextState(STATE NextState)
{
	switch (NextState)
	{
	case Character::STATE::State_None:
		break;
	case Character::STATE::State_AirMove:
		m_CharacterStateContext.SetNextState(new Character00_AirMoveState());
		break;
	case Character::STATE::State_BlowAway:
		m_CharacterStateContext.SetNextState(new Character00_BlowAwayState());
		break;
	case Character::STATE::State_Dash:
		m_CharacterStateContext.SetNextState(new Character00_DashState());
		break;
	case Character::STATE::State_Dead:
		m_CharacterStateContext.SetNextState(new Character00_DeadState());
		break;
	case Character::STATE::State_Down:
		m_CharacterStateContext.SetNextState(new Character00_DownState());
		break;
	case Character::STATE::State_FallDown:
		m_CharacterStateContext.SetNextState(new Character00_FallDownState());
		break;
	case Character::STATE::State_GameOver:
		m_CharacterStateContext.SetNextState(new Character00_GameOverState());
		break;
	case Character::STATE::State_HitStop:
		m_CharacterStateContext.SetNextState(new Character00_HitStopState());
		break;
	case Character::STATE::State_Idle:
		m_CharacterStateContext.SetNextState(new Character00_IdleState());
		break;
	case Character::STATE::State_JumpIn:
		m_CharacterStateContext.SetNextState(new Character00_JumpInState());
		break;
	case Character::STATE::State_Jump:
		m_CharacterStateContext.SetNextState(new Character00_JumpState());
		break;
	case Character::STATE::State_LeanBack:
		m_CharacterStateContext.SetNextState(new Character00_LeanBackState());
		break;
	case Character::STATE::State_Respawn:
		m_CharacterStateContext.SetNextState(new Character00_RespawnState());
		break;
	case Character::STATE::State_WakeUp:
		m_CharacterStateContext.SetNextState(new Character00_WakeUpState());
		break;
	case Character::STATE::State_Walk:
		m_CharacterStateContext.SetNextState(new Character00_WalkState());
		break;
	case Character::STATE::State_Attack11:
		m_CharacterStateContext.SetNextState(new Character00_Attack11());
		break;
	case Character::STATE::State_Attack12:
		m_CharacterStateContext.SetNextState(new Character00_Attack12());
		break;
	case Character::STATE::State_Attack13:
		m_CharacterStateContext.SetNextState(new Character00_Attack13());
		break;
	case Character::STATE::State_AttackAirN:
		m_CharacterStateContext.SetNextState(new Character00_AttackAirN);
		break;
	case Character::STATE::State_AttackDS:
		m_CharacterStateContext.SetNextState(new Character00_AttackDS());
		break;
	case Character::STATE::State_AttackS2:
		m_CharacterStateContext.SetNextState(new Character00_AttackS2());
		break;
	}

	return m_CharacterStateContext.GetNextState();
}

void Character_00::Uninit()
{
	m_stateWindow.Uninit_MiniWindow();
}

void Character_00::Update()
{

}

void Character_00::Draw()
{

}
