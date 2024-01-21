#pragma once
#include "Calculation.h"
#include "Collider.h"
#include "ModelDrawer.h"
#include <vector>
#include "GameUI03_CharacterDamageUI.h"
#include "XboxKeyboard.h"
#include "Player_Controller.h"
#include "Stage_Base.h"
#include "StatePattern.h"

class Character;
class Character_State;
class Character_Attack;

class Character
{
public:
	enum class LOOKDIR : int
	{
		RIGHT = 0,
		LEFT,
		UP,
		DOWN,
		FRONT,
		BACK,
		MAX,
	};

	enum class STATE : int
	{
		State_None = 0,
		State_AirMove,
		State_BlowAway,
		State_Dash,
		State_Dead,
		State_Down,
		State_FallDown,
		State_GameOver,
		State_HitStop,
		State_Idle,
		State_JumpIn,
		State_Jump,
		State_LeanBack,
		State_Respawn,
		State_StartAnime,
		State_WakeUp,
		State_Walk,
		State_Attack11,
		State_Attack12,
		State_Attack13,
		State_AttackAirN,
		State_AttackDS,
		State_AttackS2,
		State_Max,
	};

	struct ATTACKPARAM
	{
		bool m_Use = false;									//���̍U���̓����蔻����s����
		BoxCollider m_BoxCollider;							//�U���̓����蔻��
		unsigned int m_HitCharacterBit = 0x00;				//�O�̃t���[���œ��������L�����N�^�[�̃r�b�g�ԍ�������
		unsigned int m_CanAttackCharacterBit = 0x00;		//�����邱�Ƃ��o����L�����N�^�[�̃r�b�g�ԍ�
		unsigned int m_haveHitCharacterBit = 0x00;			//���܂łœ����������Ƃ�����L�����N�^�[�r�b�g�ԍ�
		unsigned int m_HitTriggerCharacterBit = 0x00;		//�O�̃t���[���ŏ��߂ē���������������L�����N�^�[�̃r�b�g�ԍ�
	};

	struct CHARACTER_PARAMETER
	{
		//-------------------------------------------------------------------------------
		// ���W�Ɋւ���ϐ�
		//-------------------------------------------------------------------------------
		CVector3		Pos;						//���W
		CVector3		AddDrawPos;					//�`�悷��Ƃ��ɂ��炷���W
		CVector3		OldPos;						//�O�̍��W
		CVector3		Scale;						//�傫��
		CQuaternion		Rotate;						//��]��
		CVector3		Velocity;					//�d�͂Ȃ�
		CVector3		MoveVector;					//�R���g���[���[�̈ړ���
		CVector3		ShiftCenterPos;				//��]��g�k�����钆�S�ʒu�����炷

		//-------------------------------------------------------------------------------
		// �W�����v�Ɋւ���ϐ�
		//-------------------------------------------------------------------------------
		int				JumpCount = 0;				//���W�����v������
		int				JumpCharageCount = 0;		//�W�����v���`���[�W���鎞�̃J�E���g

		//-------------------------------------------------------------------------------
		//�X�e�[�W�ɓ���������
		//-------------------------------------------------------------------------------
		bool			HitGround = false;			//�O�̃t���[���Œn�ʂɓ���������
		bool			HitCeiling = false;			//�O�̃t���[���œV��ɓ���������
		bool			HitWall = false;				//�O�̃t���[���ŕǂɓ���������
	};

	struct MOVEPARAMETER
	{
		float	WalkSpeed = 0.0f;		//�����X�s�[�h
		float	DashSpeed = 0.0f;		//����X�s�[�h
		float	AirSideMoveSpeed = 0.0f;		//�����Ă���Ƃ��̉��ړ��̃X�s�[�h
		float	Friction = 0.0f;		//���C��
		float	AirDrag = 0.0f;		//��C��R
	};

	struct JUMPPARAMETER
	{
		int		MaxJumpCount = 0;				//�W�����v�ł���ő吔
		int		MiniJumpPushButtonCount = 0;	//���W�����v����Ƃ��̃t���[��
		int		JumpChargeCount = 0;			//�W�����v����܂ł̃`���[�W����
		float	FirstMiniJumpPower = 0.0f;	//���W�����v������Ƃ��̗�
		float	FirstJumpPower = 0.0f;		//�W�����v����Ƃ��̗�
		float	SecondJumpPower = 0.0f;		//���ڂ̃W�����v�̗�
		float	JumpUpReduction = 0.0f;		//�W�����v���ď�ɏオ��Ƃ��̏d��
		float	FallDownGravity = 0.0f;		//�W�����v���I����ĉ��ɉ�����Ƃ��̏d��
		float	DefaultFallSpeed = 0.0f;		//�ő嗎�����x
		float	SpeedUpFallSpeed = 0.0f;		//�������ɉ����������ꍇ�̗�����
		float	ChangeFallSpeed = 0.0f;		//�����ɕς��Ƃ��̃X�s�[�h
	};

	struct BLOWAWAYPARAMETER
	{
		float SmashMitigation = 0.0f;			//������΂��ꂽ���ɂǂꂭ�炢�キ���Ă�����
		float VectorChangePower = 0.0f;		//������΂��ꂽ���Ƀx�N�g���ύX���銄��
		float MinimumSmashLength = 0.0f;		//�������ł���Ɣ��肷��Œ዗�����x
	};


	//===============================================================================
	//static�֐��E�ϐ�
	//===============================================================================
public:
	static void InitPlayerBit();	//���̊֐��ł��炦��ԍ�������������
protected:
	static int GetNewPlayerBit();	//�V�����v���C���[�̔ԍ�(2�i��)���󂯎��
									//�ςȂƂ���ŌĂԂƔԍ�������Ă��܂��̂�Init�ȊO�ŌĂ΂Ȃ��悤��
private:
	static int m_NewPlayerBit;		//�V�����v���C���[�̃r�b�g�ԍ�(�L�����N�^�[�𐔂��邽�߂Ɏg��)

	//===============================================================================
	//�֐�
	//===============================================================================
public:
	Character() {};
	virtual ~Character() {};

	void Character_Init();								//�L�����N�^�[�̏�����
	void Character_Uninit();							//�L�����N�^�[�̏I������
	void Character_Update();							//�L�����N�^�[�̍X�V
	void Character_Draw();								//�L�����N�^�[�̕`��
	void Character_UIDraw();							//UI�̕`��
	void DrawCollider();								//�R���C�_�[�̕`��
	void ChangeNextState();								//���̃X�e�[�g�֕ύX
	void CheckDeadLineOver();								//�Q�[���I�[�o�[�����Ă��邩�m�F

	//===============================================================================
	//�p����Ŏ�������֐�
	//===============================================================================
protected:
	virtual void Init() {};			//�p����̏�����
	virtual void Uninit() {};		//�p����̏I������
	virtual void Update() {};		//�p����̍X�V
	virtual void Draw() {};			//�p����̕`��

public:
	//===============================================================================
	//�������z�֐�
	//===============================================================================
	virtual State* SetNextState(STATE NextState) = 0;
	virtual void SetDefaultCollider() = 0;	//�ŏ��̓����蔻��ɖ߂�(�L�����N�^�[�̓����蔻������������ꍇ

	
protected:
	//===============================================================================
	//�ϐ��ꗗ
	//===============================================================================
	int						 m_PlayerBit = 0x00;			//���̃L�����N�^�[�����ԂȂ̂�������
	PlayerController*		 m_Controller = nullptr;		//�L�����N�^�[�̃R���g���[���[
	CHARACTER_PARAMETER		 m_Parameter;					//�L�����N�^�[�̈ʒu�Ȃǂ̕ϐ����܂Ƃ߂��ϐ�
	StateContext			 m_CharacterStateContext;		//�X�e�[�g�R���e�N�X�g
	Character::LOOKDIR		 m_NowLookDir = LOOKDIR::MAX;	//�v���C���[�����Ă������
	ModelDrawer				 m_CharacterModel;				//�L�����N�^�[�̃��f��
	int						 m_CharacterStock = 0;			//�X�g�b�N
	float					 m_DamagePercentage = 0.0f;		//�_���[�W�̗�
	bool					 m_Invincible = false;			//���G���ۂ�
	bool					 m_GameOver = false;			//�Q�[���I�[�o�[���Ă��邩
	bool					 m_IsCheckDead = false;			//���ʔ����A���ł��Ȃ��悤�ɂ���
	BoxCollider				 m_CharacterCollider;			//�v���C���[�̓����蔻��
	std::vector<ATTACKPARAM> m_AttackCollider;				//�U�������Ƃ��̓����蔻��
	Character_DamageUI		 m_DamageUI;					//�_���[�WUI
	MOVEPARAMETER			 m_MoveParameter;				//���������Ȃǂ̓����̃p�����[�^
	JUMPPARAMETER			 m_JumpParameter;				//�W�����v�͂Ȃǂ̃p�����[�^
	BLOWAWAYPARAMETER		 m_BlowAwayParameter;			//������΂��͂Ȃǂ̃p�����[�^
	Stage*					 m_pStage = nullptr;			//�X�e�[�W�̏�񂪓���

public:
	//===============================================================================
	// Set�AGet�֐�(�������牺�͑S��)
	//===============================================================================
	
	int GetCharacterBit()										//�L�����N�^�[�ԍ����擾
	{ return m_PlayerBit; }

	//------------------------------------------------------------------------------
	StateContext* GetStateContext()								//�X�e�[�g�R���e�N�X�g���擾
	{ return &m_CharacterStateContext; }

	//------------------------------------------------------------------------------
	const CVector3& GetPos() const								//�ʒu�̎擾
	{ return m_Parameter.Pos; }

	//------------------------------------------------------------------------------
	void SetPos(const CVector3& pos)							//�ʒu�̐ݒ�
	{ m_Parameter.Pos = pos;
		m_CharacterCollider.SetBasePos(pos); }
	
	//------------------------------------------------------------------------------
	const CVector3& GetOldPos() const							//�O�̍��W���擾
	{ return m_Parameter.OldPos; }

	//------------------------------------------------------------------------------
	void SetOldPos()											//�O�̍��W��ݒ�
	{ m_Parameter.OldPos = m_Parameter.Pos; }

	//------------------------------------------------------------------------------
	const CVector3& GetScale() const							//�X�P�[���̎擾
	{ return m_Parameter.Scale; }

	//------------------------------------------------------------------------------
	void SetScale(const CVector3& scale)						//�X�P�[���̐ݒ�
	{ m_Parameter.Scale = scale; }

	//------------------------------------------------------------------------------
	const CQuaternion& GetRotate() const						//��]�̎擾
	{ return m_Parameter.Rotate; }

	//------------------------------------------------------------------------------
	void SetRotate(const CQuaternion& rotate)					//��]�̐ݒ�(�N�H�[�^�j�I��)
	{ m_Parameter.Rotate = rotate; }

	//------------------------------------------------------------------------------
	void SetRotate(const CVector3& rotate)						//��]�̐ݒ�(�x���@)
	{ m_Parameter.Rotate.SetQuaternion(
			DirectX::XMConvertToRadians(rotate.x),
			DirectX::XMConvertToRadians(rotate.y),
			DirectX::XMConvertToRadians(rotate.z)); }

	//------------------------------------------------------------------------------
	void SetLookRight() 										//�E����������
	{ m_NowLookDir = Character::LOOKDIR::RIGHT;
		m_Parameter.Rotate =
			CQuaternion::AngleAxis(CVector3::GetUp(), 90.0f); }

	//------------------------------------------------------------------------------
	void SetLookLeft()											//������������
	{ m_NowLookDir = Character::LOOKDIR::LEFT;
		m_Parameter.Rotate =
			CQuaternion::AngleAxis(CVector3::GetUp(), -90.0f); }

	//------------------------------------------------------------------------------
	void SetLookFront()											//�O����������
	{
		m_NowLookDir = Character::LOOKDIR::FRONT;
		m_Parameter.Rotate =
			CQuaternion::AngleAxis(CVector3::GetUp(), 180.0f);}

	//------------------------------------------------------------------------------
	void SetLookBack()											//������������
	{
		m_NowLookDir = Character::LOOKDIR::BACK;
		m_Parameter.Rotate =
			CQuaternion::AngleAxis(CVector3::GetUp(), 0.0f);
	}

	//------------------------------------------------------------------------------
	void SetNowLook() 											//���ݒ肵�Ă�������֌�������
	{ switch (m_NowLookDir) {
		case Character::LOOKDIR::LEFT:
			SetLookLeft();
			break;
		case Character::LOOKDIR::RIGHT:
			SetLookRight();
			break;
		}}

	//------------------------------------------------------------------------------
	LOOKDIR GetLook()											//�������Ă�������擾
	{ return m_NowLookDir; };

	//------------------------------------------------------------------------------
	void AddForce(const CVector3& force)						//�d�͂Ȃǂ𑫂��Ă��
	{ m_Parameter.Velocity += force; }

	//------------------------------------------------------------------------------
	void SetForce(const CVector3& force)						//�d�͂�ݒ肵�Ă��
	{ m_Parameter.Velocity = force; }
		
	//------------------------------------------------------------------------------
	float GetDamage() const										//�_���[�W���擾
	{ return m_DamagePercentage; }
	
	//------------------------------------------------------------------------------
	void AddDamage(float damage)								//�_���[�W�����Z
	{ m_DamagePercentage += damage; }

	//------------------------------------------------------------------------------
	void SetDamage(float damage)								//�_���[�W��ݒ�
	{ m_DamagePercentage = damage; }

	//------------------------------------------------------------------------------
	void SetStock(int stock) 									//�X�g�b�N��ݒ�
	{ m_CharacterStock = stock;
		m_DamageUI.SetStockNum(stock); }
	
	//------------------------------------------------------------------------------
	int GetStock()												//�X�g�b�N���擾
	{ return m_CharacterStock; }

	//------------------------------------------------------------------------------
	void SetInvincible(bool invincible)							//���G���ۂ���ݒ�
	{ m_Invincible = invincible; }
	
	//------------------------------------------------------------------------------
	bool IsInvincible()											//���G���ۂ��擾
	{ return m_Invincible; }

	//------------------------------------------------------------------------------
	void SetGameOver(bool GameOver)								//�Q�[���I�[�o�[��ݒ�
	{ m_GameOver = GameOver; }
	
	//------------------------------------------------------------------------------
	bool GetGameOver()											//�Q�[���I�[�o�[���擾
	{ return m_GameOver; }

	//------------------------------------------------------------------------------
	void SetCheckDead(bool dead)								//���񂾔�������邩
	{ m_IsCheckDead = dead; }
	//------------------------------------------------------------------------------
	bool IsCheckDead()											//���񂾔�������邩�擾
	{ return m_GameOver; }

	//------------------------------------------------------------------------------
	BoxCollider* GetCharacterCollider() const					//�L�����N�^�[�̓����蔻����擾
	{ return const_cast<BoxCollider*>(&m_CharacterCollider); }

	//------------------------------------------------------------------------------
	std::vector<Character::ATTACKPARAM>& GetAttackCollider()	//�U���̓����蔻����擾
	{ return m_AttackCollider; }

	//------------------------------------------------------------------------------
	void Character_ColliderInit() 								//�X�e�[�W�Ƃ̓����蔻��Ŏg���ϐ���������
	{ m_Parameter.HitCeiling =
			m_Parameter.HitGround =
			m_Parameter.HitWall = false; }

	//------------------------------------------------------------------------------
	void Character_HitCeiling()									//�V��ɓ����������Ƃ�ݒ�
	{
		m_Parameter.Velocity.y = 0.0f;
		m_Parameter.HitCeiling = true;	}

	//------------------------------------------------------------------------------
	bool GetHitCeling()											//�O�̃t���[���œV��ɓ����������擾
	{ return m_Parameter.HitCeiling; }

	//------------------------------------------------------------------------------
	void Character_HitGround() 									//�n�ʂɓ����������̏���
	{ m_Parameter.Velocity.y = 0.0f;
		m_Parameter.JumpCount = 0;
		m_Parameter.HitGround = true; }

	//------------------------------------------------------------------------------
	bool GetHitGround()											//�O�̃t���[���Œn�ʂɓ����������擾
	{ return m_Parameter.HitGround; }
	
	//------------------------------------------------------------------------------
	void Character_HitWall()									//�ǂɓ�����������ݒ�
	{ m_Parameter.HitWall = true; }

	//------------------------------------------------------------------------------
	bool GetHitWall()											//�O�̃t���[���ŕǂɓ����������擾
	{ return m_Parameter.HitWall; }

	//------------------------------------------------------------------------------
	void SetCharacterController(PlayerController* pController); 	//�R���g���[���[��ݒ�
	/*Cpp�Ɏ������Ă��܂�*/

	//------------------------------------------------------------------------------
	void SetStage(Stage* pStage);								//�X�e�[�W��ݒ�
	/*Cpp�Ɏ������Ă��܂�*/

	//------------------------------------------------------------------------------
	void SetMoveParameter(const MOVEPARAMETER& MoveParameter)	//�����Ɋւ���p�����[�^��ݒ�
	{ m_MoveParameter = MoveParameter; }

	//------------------------------------------------------------------------------
	const MOVEPARAMETER& GetMoveParameter()						//�����Ɋւ���p�����[�^���擾
	{ return m_MoveParameter; }

	//------------------------------------------------------------------------------
	void SetjumpParameter(const JUMPPARAMETER& JumpParameter)	//�W�����v�Ɋւ���p�����[�^��ݒ�
	{ m_JumpParameter = JumpParameter; }

	//------------------------------------------------------------------------------
	const JUMPPARAMETER& GetJumpParameter()						//�W�����v�Ɋւ���p�����[�^���擾
	{ return m_JumpParameter; }

	//------------------------------------------------------------------------------
	void SetBlowAwayParameter(const BLOWAWAYPARAMETER& BlowAwayParameter)	//������΂��Ɋւ���p�����[�^��ݒ�
	{ m_BlowAwayParameter = BlowAwayParameter; }

	//------------------------------------------------------------------------------
	const BLOWAWAYPARAMETER& GetBlowAwayParameter()							//������΂��Ɋւ���p�����[�^���擾
	{ return m_BlowAwayParameter; }
};