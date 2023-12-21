#include "Character_00.h"
#include "Input.h"
#include "MiniWindow.h"

void Character_00::Init()
{
	m_stateWindow.Init_MiniWindow();

	MOVEPARAMETER moveParameter;
	moveParameter.m_WalkSpeed = 4.0f / 60.0f;
	moveParameter.m_DashSpeed = 8.0f / 60.0f;
	moveParameter.m_AirSideMoveSpeed = 4.0f / 60.0f;
	moveParameter.m_Friction = 0.65f;
	moveParameter.m_AirDrag = 0.98f;
	SetMoveParameter(moveParameter);

	JUMPPARAMETER jumpParameter;
	jumpParameter.m_MaxJumpCount = 2;
	jumpParameter.m_MiniJumpPushButtonCount = 2;
	jumpParameter.m_JumpChargeCount = 3;
	jumpParameter.m_FirstMiniJumpPower = 0.15f;
	jumpParameter.m_FirstJumpPower = 0.3f;
	jumpParameter.m_SecondJumpPower = 0.7f;
	jumpParameter.m_JumpUpReduction = 0.93f;
	jumpParameter.m_FallDownGravity = -0.01f;
	jumpParameter.m_DefaultFallSpeed = -0.15f;
	jumpParameter.m_SpeedUpFallSpeed = -0.3f;
	jumpParameter.m_ChangeFallSpeed = 0.05f;
	SetjumpParameter(jumpParameter);

	BLOWAWAYPARAMETER blowAwayParameter;
	blowAwayParameter.m_SmashMitigation = 0.85f;
	blowAwayParameter.m_VectorChangePower = 0.02f;
	blowAwayParameter.m_MinimumSmashLength = 0.3f;
	SetBlowAwayParameter(blowAwayParameter);

	ModelDrawer::LoadModel("Assets/unitychan/unitychan.fbx", "UnityChan", 0.003f);
	ModelDrawer::LoadAnime("Assets/unitychan/unitychan_ARpose2.fbx", "Pose2", "UnityChan");
	ModelDrawer::LoadAnime("Assets/unitychan/unitychan_WAIT00.fbx", "Idle", "UnityChan");
	ModelDrawer::LoadAnime("Assets/unitychan/unitychan_UMATOBI00.fbx", "Umatobi", "UnityChan");
	ModelDrawer::LoadAnime("Assets/unitychan/unitychan_WAIT04.fbx", "WAIT04", "UnityChan");
	ModelDrawer::LoadAnime("Assets/unitychan/unitychan_WALK00_F.fbx", "Walk", "UnityChan");
	ModelDrawer::LoadAnime("Assets/unitychan/unitychan_RUN00_F.fbx", "Dash", "UnityChan");
	ModelDrawer::LoadAnime("Assets/unitychan/unitychan_JUMP00B.fbx", "Jump", "UnityChan");
	m_CharacterModel.SetModel("UnityChan");
	m_CharacterModel.PlayAnime("Walk",true);
	m_CharacterModel.SetPosition(CVector3(0.0f, 3.0f, 0.0f));
	m_CharacterModel.SetRotate(CVector3::GetZero());
	m_CharacterModel.SetScale(CVector3(5.0f, 5.0f, 5.0f));

	m_NowState = Character::STATE::IDLE;

	m_CharacterCollider.SetType(BoxCollider::BOXTYPE::FOOT);
	m_CharacterCollider.SetPos(m_pos);
	m_CharacterCollider.SetSize(CVector3(1.0f,2.0f,1.0f));

	m_stateWindow.SetCharacter(this);

	m_FrameCount = 0;

	m_DamageUI.GetCharacterIconUI()->SetIconTexture("Assets/CharacterImage/UnitychanImage.png");

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

void Character_00::IdleInit()
{
	Character::IdleInit();
	m_CharacterModel.PlayAnime("Idle", true);
	m_AnimeTime = 0.0f;
}

void Character_00::IdleUpdate()
{
	Character::IdleUpdate();

	m_AnimeTime += 0.015f;
	if (m_AnimeTime > 1.0f)
	{
		m_AnimeTime -= 1.0f;
	}

	m_CharacterModel.SetAnimeLerp(m_AnimeTime);
}

void Character_00::WalkInit()
{
	Character::WalkInit();
	m_CharacterModel.PlayAnime("Walk",true);
	m_AnimeTime = 0.0f;
}

void Character_00::WalkUpdate()
{
	Character::WalkUpdate();

	m_AnimeTime += 0.015f;
	if (m_AnimeTime > 1.0f)
	{
		m_AnimeTime -= 1.0f;
	}

	m_CharacterModel.SetAnimeLerp(m_AnimeTime);
}

void Character_00::DashInit()
{
	Character::DashInit();
	m_CharacterModel.PlayAnime("Dash", true);
	m_AnimeTime = 0.0f;
}

void Character_00::DashUpdate()
{
	Character::DashUpdate();

	m_AnimeTime += 0.015f;
	if (m_AnimeTime > 1.0f)
	{
		m_AnimeTime -= 1.0f;
	}

	m_CharacterModel.SetAnimeLerp(m_AnimeTime);
}

void Character_00::JumpInInit()
{
	Character::JumpInInit();
	m_CharacterModel.PlayAnime("Jump", false);
	m_AnimeTime = 0.0f;
}

void Character_00::JumpInUpdate()
{
	Character::JumpInUpdate();
	m_AnimeTime = (static_cast<float>(m_JumpCharageCount) / 3.0f) * 0.05f + 0.1f;

	m_CharacterModel.SetAnimeTime(m_AnimeTime);
}

void Character_00::JumpInit()
{
	Character::JumpInit();
}

void Character_00::JumpUpdate()
{
	Character::JumpUpdate();

	m_AnimeTime = (1.0f - (m_Velocity.y / m_JumpParameter.m_FirstJumpPower)) * 0.93f + 0.15f;

	m_CharacterModel.SetAnimeTime(m_AnimeTime);
}

void Character_00::AirMoveInit()
{
	Character::AirMoveInit();

	if (m_NowState == Character::STATE::WALK ||
		m_NowState == Character::STATE::DASH ||
		m_NowState == Character::STATE::IDLE ||
		m_NowAttack == Character::ATTACK::ATTACK_AIRN)
	{
		m_CharacterModel.PlayAnime("Jump", false);
	}
}

void Character_00::AirMoveUpdate()
{
	Character::AirMoveUpdate();

	m_AnimeTime = sinf(static_cast<float>(m_FrameCount) / 60.0f * 3.14f * 3.0f) * 0.03f + 1.08f;

	m_CharacterModel.SetAnimeTime(m_AnimeTime);

}

void Character_00::HitGround()
{
	m_Velocity.y = 0.0f;
}
