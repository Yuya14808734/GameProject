#include "Character_00.h"
#include "Input.h"

void Character_00::Init()
{
	SetParameter(3.0f / 60.0f, 5.0f / 60.0f, 3.0f / 60.0f, 2, 0.5f, -0.04f, -0.1f,-0.2f, 0.65f, 0.65f);
	ModelDrawer::LoadModel("Assets/unitychan/unitychan.fbx", "UnityChan", 0.003f);
	ModelDrawer::LoadAnime("Assets/unitychan/walk.fbx", "Walk", "UnityChan");
	ModelDrawer::LoadAnime("Assets/unitychan/run.fbx", "Dash", "UnityChan");
	ModelDrawer::LoadAnime("Assets/unitychan/jump.fbx", "Jump", "UnityChan");
	m_CharacterModel.SetModel("UnityChan");
	m_CharacterModel.PlayAnime("Walk",true);
	m_CharacterModel.SetPosition(CVector3(0.0f, 3.0f, 0.0f));
	m_CharacterModel.SetRotate(CVector3::GetZero());
	m_CharacterModel.SetScale(CVector3(5.0f, 5.0f, 5.0f));

	m_NowState = Character::STATE::IDLE;

	m_pos = CVector3(0.0f, 3.0f, 0.0f);

	m_CharacterCollider.SetType(BoxCollider::BOXTYPE::FOOT);
	m_CharacterCollider.SetPos(m_pos);
	m_CharacterCollider.SetSize(CVector3(1.0f,3.0f,1.0f));
}

void Character_00::Uninit()
{

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
	m_CharacterModel.PlayAnime("Jump", true);
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
	m_AnimeTime += 0.015f;
	if (m_AnimeTime > 1.0f)
	{
		m_AnimeTime -= 1.0f;
	}

	m_CharacterModel.SetAnimeLerp(m_AnimeTime);
}

void Character_00::HitGround()
{
	m_Velocity.y = 0.0f;
	if (m_NowState == Character::STATE::AIRMOVE || m_NowState == Character::STATE::JUMP)
	{
		m_NowState = Character::STATE::IDLE;
	}
}
