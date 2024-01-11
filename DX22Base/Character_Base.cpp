#include "Character_Base.h"
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
	//0:�v���C���[1,1:�v���C���[2
	int PlayerNum = static_cast<int>(log2f(static_cast<float>(m_PlayerBit)));

	//=====<�L�����N�^�[�̈ʒu�̐ݒ�>=============================================
	//�L�����N�^�[�̔ԍ��ɂ���ăX�e�[�W�̔z�u�ꏊ��ς���
	std::vector<CVector3>* startPosV = static_cast<SceneGame*>(CScene::GetScene())->GetStage()->GetCharacterStartPos();
	m_Parameter.Pos = (*startPosV)[PlayerNum];
	//============================================================================
	 
	//=====<�L�����N�^�[��UI�̈ʒu�̐ݒ�>=============================================
	CVector2 BasePos(450.0f, 620.0f);
	CVector2 PosDistance(400.0f, 0.0f);

	m_DamageUI.SetBoardColor(static_cast<Character_DamageUI::BOARDCOLOR>(PlayerNum));
	m_DamageUI.SetPos(BasePos + (PosDistance * static_cast<float>(PlayerNum)));
	m_CharacterStock = 3;
	m_DamageUI.SetStockNum(m_CharacterStock);
	//============================================================================

	//=====<�����蔻��̐ݒ�>=============================================
	SetDefaultCollider();
	//============================================================================

	Init();

	m_Parameter.JumpCount = 0;
	m_Parameter.HitGround = m_Parameter.HitCeiling = m_Parameter.HitWall = false;
}

void Character::Character_Uninit()
{
	Uninit();
}

void Character::Character_Update()
{
	m_Parameter.OldPos = m_Parameter.Pos;

	Update();

	//========================================
	// �e�X�e�[�^�X�̃A�b�v�f�[�g
	//========================================
	m_CharacterStateContext.StateUpdate();

	//========================================
	// �e�X�e�[�^�X���؂�ւ���Ă�����
	//========================================
	if (m_CharacterStateContext.GetNextState() != nullptr)
	{
		m_CharacterStateContext.StateUninit();
		m_CharacterStateContext.ChangeNextState();
		Character_State* pState = static_cast<Character_State*>(m_CharacterStateContext.GetNowState());
		pState->SetCharacter(this);
		pState->SetAttackCollider(&m_AttackCollider);
		pState->SetCharacterCollider(&m_CharacterCollider);
		pState->SetController(m_Controller);
		pState->SetCharacterParameter(&m_Parameter);
		pState->SetStage(m_pStage);
		m_CharacterStateContext.StateInit();
	}

	//========================================
	// �ʒu�̐ݒ�
	//========================================
	m_CharacterCollider.SetBasePos(m_Parameter.Pos);

	//========================================
	// UI�̍X�V
	//========================================
	m_DamageUI.GetDamageUI()->SetNumber(static_cast<int>(m_DamagePercentage));
	m_DamageUI.Update();
}

void Character::Character_Draw()
{
	Draw();

	//========================================
	// �L�����N�^�[�̕`��
	//========================================
	m_CharacterModel.SetRotate(m_Parameter.Rotate);
	m_CharacterModel.Draw();
}

void Character::Character_UIDraw()
{
	//========================================
	// UI�̕`��
	//========================================
	m_DamageUI.Draw();
}

int Character::GetCharacterBit()
{
	return m_PlayerBit;
}

StateContext* Character::GetStateContext()
{
	return &m_CharacterStateContext;
}

const CVector3& Character::GetPos() const
{
	return m_Parameter.Pos;
}

void Character::SetPos(const CVector3 & pos)
{
	m_Parameter.Pos = pos;
	m_CharacterCollider.SetBasePos(pos);
}

const CVector3& Character::GetOldPos() const
{
	return m_Parameter.OldPos;
}

void Character::SetOldPos()
{
	m_Parameter.OldPos = m_Parameter.Pos;
}

const CVector3 & Character::GetScale() const
{
	return m_Parameter.Scale;
}

void Character::SetScale(const CVector3 & scale)
{
	m_Parameter.Scale = scale;
}

const CQuaternion & Character::GetRotate() const
{
	return m_Parameter.Rotate;
}

void Character::SetRotate(const CQuaternion & rotate)
{
	m_Parameter.Rotate = rotate;
}

void Character::SetRotate(const CVector3 & rotate)
{
	m_Parameter.Rotate.v = DirectX::XMQuaternionRotationRollPitchYaw(
		DirectX::XMConvertToRadians(rotate.x),
		DirectX::XMConvertToRadians(rotate.y),
		DirectX::XMConvertToRadians(rotate.z));
}

void Character::SetLookRight()
{
	m_NowLookDir = Character::LOOKDIR::RIGHT;
	m_Parameter.Rotate = CQuaternion::AngleAxis(CVector3::GetUp(),90.0f);
}

void Character::SetLookLeft()
{
	m_NowLookDir = Character::LOOKDIR::LEFT;
	m_Parameter.Rotate = CQuaternion::AngleAxis(CVector3::GetUp(), -90.0f);
}

void Character::SetNowLook()
{
	switch (m_NowLookDir)
	{
	case Character::LOOKDIR::LEFT:
		SetLookLeft();
		break;
	case Character::LOOKDIR::RIGHT:
		SetLookRight();
		break;
	}
}

Character::LOOKDIR Character::GetLook()
{
	return m_NowLookDir;
}

void Character::AddForce(const CVector3 & force)
{
	m_Parameter.Velocity += force;
}

void Character::SetForce(const CVector3 & force)
{
	m_Parameter.Velocity = force;
}

float Character::GetDamage() const
{
	return m_DamagePercentage;
}

void Character::AddDamage(float damage)
{
	m_DamagePercentage += damage;
}

void Character::SetDamage(float damage)
{
	m_DamagePercentage = damage;
}

void Character::SetStock(int stock)
{
	m_CharacterStock = stock;
	m_DamageUI.SetStockNum(stock);
}

int Character::GetStock()
{
	return m_CharacterStock;
}

void Character::SetInvincible(bool invincible)
{
	m_Invincible = invincible;
}

bool Character::IsInvincible()
{
	return m_Invincible;
}

BoxCollider* Character::GetCharacterCollider() const
{
	return const_cast<BoxCollider*>(&m_CharacterCollider);
}

std::vector<Character::ATTACKPARAM>& Character::GetAttackCollider()
{
	return m_AttackCollider;
}

void Character::Character_ColliderInit()
{
	m_Parameter.HitCeiling = m_Parameter.HitGround = m_Parameter.HitWall = false;
}

void Character::Character_HitCeiling()
{
	m_Parameter.HitCeiling = true;
}

void Character::Character_HitGround()
{
	m_Parameter.Velocity.y = 0.0f;
	m_Parameter.JumpCount = 0;
	m_Parameter.HitGround = true;
}

void Character::Character_HitWall()
{
	m_Parameter.HitWall = true;
}

void Character::DrawCollider()
{
	m_CharacterCollider.DrawCollider();
}

void Character::SetCharacterController(PlayerController* pController)
{
	m_Controller = pController;
}

void Character::SetStage(Stage* pStage)
{
	m_pStage = pStage;
}