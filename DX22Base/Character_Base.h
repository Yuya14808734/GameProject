#pragma once
#include "Calculation.h"
#include "Collider.h"
#include "ModelDrawer.h"
#include <vector>
#include "Character_DamageUI.h"
#include "XboxKeyboard.h"
#include "Player_Controller.h"
#include "Stage_Base.h"
#include "StatePattern.h"

class Character;
class Character_State;
class Character_AttackState;
class StateContext;
class State;

class Character
{
public:
	enum class LOOKDIR : int
	{
		RIGHT = 0,
		LEFT,
		UP,
		DOWN,
		MAX
	};

	enum class STATE
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
		State_WakeUp,
		State_Walk,
		State_Attack11,
		State_Attack12,
		State_Attack13,
		State_AttackAirN,
		State_AttackDS,
		State_AttackS2,
		State_Max
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

public:
	static void InitPlayerBit();	//���̊֐��ł��炦��ԍ�������������
protected:
	static int GetNewPlayerBit();	//�V�����v���C���[�̔ԍ�(2�i��)���󂯎��
									//�ςȂƂ���ŌĂԂƔԍ�������Ă��܂��̂�Init�ȊO�ŌĂ΂Ȃ��悤��
private:
	static int m_NewPlayerBit;		//�V�����v���C���[�̃r�b�g�ԍ�(�L�����N�^�[�𐔂��邽�߂Ɏg��)

public:
	Character() {};
	virtual ~Character() {};

	//==========================================================================
	void Character_Init();								//�L�����N�^�[�̏�����
	void Character_Uninit();							//�L�����N�^�[�̏I������
	void Character_Update();							//�L�����N�^�[�̍X�V
	void Character_Draw();								//�L�����N�^�[�̕`��
	void Character_UIDraw();							//UI�̕`��
	//==========================================================================
	int GetCharacterBit();								//�L�����N�^�[�ԍ����擾
	virtual State* SetNextState(STATE NextState) = 0;
	void ChangeNextState();
	StateContext* GetStateContext();					//���̏�Ԃ̎擾
	//==========================================================================
	const CVector3& GetPos() const;						//�ʒu�̎擾
	void SetPos(const CVector3& pos);					//�ʒu�̐ݒ�
	const CVector3& GetOldPos() const;					//�O�̍��W���擾
	void SetOldPos();									//�O�̍��W��ݒ�
	const CVector3& GetScale() const;					//�T�C�Y�̎擾
	void SetScale(const CVector3& scale);				//�T�C�Y�̐ݒ�
	const CQuaternion& GetRotate() const;				//��]�ʂ̎擾
	void SetRotate(const CQuaternion& rotate);			//��]�ʂ̐ݒ�(Quaternion)
	void SetRotate(const CVector3& rotate);				//��]�ʂ̐ݒ�(�x���@)
	void SetLookRight();								//�E����������
	void SetLookLeft();									//������������
	void SetNowLook();									//m_NowLook�Ō��Ă������������
	LOOKDIR GetLook();
	//==========================================================================
	void AddForce(const CVector3& force);				//�͂𑫂��Ă��
	void SetForce(const CVector3& force);				//�͂�ݒ�
	float GetDamage() const;							//�_���[�W�̎擾
	void AddDamage(float damage);						//�_���[�W�̉��Z
	void SetDamage(float damage);						//�_���[�W�̐ݒ�
	void SetStock(int stock);
	int GetStock();
	//==========================================================================
	void SetInvincible(bool invincible);				//�L�����N�^�[�𖳓G�ɂ��邩
	bool IsInvincible();								//�L�����N�^�[�����G���ۂ�
	BoxCollider* GetCharacterCollider() const;			//�L�����N�^�[�A�X�e�[�W�����蔻��̎擾
	std::vector<Character::ATTACKPARAM>& GetAttackCollider();		//�U���R���C�_�[�̎擾
	void Character_ColliderInit();						//�n�ʂȂǂɓ������Ă��Ȃ����Ƃɂ���
	void Character_HitCeiling();						//�V��ɓ�������	
	void Character_HitGround();							//�n�ʂɓ�������
	void Character_HitWall();							//�ǂɓ�������
	void DrawCollider();								//�R���C�_�[�̕`��
	//==========================================================================
	void SetCharacterController(PlayerController* pController);
	void SetStage(Stage* pStage);

protected:

	virtual void Init() {};			//�p����̏�����
	virtual void Uninit() {};		//�p����̏I������
	virtual void Update() {};		//�p����̍X�V
	virtual void Draw() {};			//�p����̕`��

public:

	virtual void SetDefaultCollider() = 0;	//�ŏ��̓����蔻��ɖ߂�(�L�����N�^�[�̓����蔻������������ꍇ

public:
	//===============================================================================
	// �p�����[�^�ꗗ
	//===============================================================================

	//-------------------------------------------------------------------------------
	// ���ړ��Ɋւ���p�����[�^
	//-------------------------------------------------------------------------------

	MOVEPARAMETER m_MoveParameter;

	void SetMoveParameter(const MOVEPARAMETER& MoveParameter)
	{
		m_MoveParameter = MoveParameter;
	}

	const MOVEPARAMETER& GetMoveParameter()
	{
		return m_MoveParameter;
	}

	//-------------------------------------------------------------------------------
	// �W�����v�Ɋւ���p�����[�^
	//-------------------------------------------------------------------------------

	JUMPPARAMETER m_JumpParameter;

	void SetjumpParameter(const JUMPPARAMETER& JumpParameter)
	{
		m_JumpParameter	= JumpParameter;
	}

	const JUMPPARAMETER& GetJumpParameter()
	{
		return m_JumpParameter;
	}

	//-------------------------------------------------------------------------------
	// ������΂��ꂽ���Ɋւ���p�����[�^
	//-------------------------------------------------------------------------------
	
	BLOWAWAYPARAMETER m_BlowAwayParameter;

	void SetBlowAwayParameter(const BLOWAWAYPARAMETER& BlowAwayParameter)
	{
		m_BlowAwayParameter = BlowAwayParameter;
	}

	const BLOWAWAYPARAMETER& GetBlowAwayParameter()
	{
		return m_BlowAwayParameter;
	}

protected:
	//===============================================================================
	// �ϐ��ꗗ
	//===============================================================================
	int		m_PlayerBit = 0x00;						//���̃L�����N�^�[�����ԂȂ̂�������
	PlayerController* m_Controller = nullptr;		//�L�����N�^�[�̃R���g���[���[

	//===============================================================================
	// �ʒu�Ȃǂ��܂Ƃ߂��ϐ�
	//===============================================================================
	CHARACTER_PARAMETER m_Parameter;

	//-------------------------------------------------------------------------------
	// �v���C���[�X�e�[�g�Ɋւ���ϐ�
	//-------------------------------------------------------------------------------
	StateContext m_CharacterStateContext;

	Character::LOOKDIR	m_NowLookDir		= LOOKDIR::MAX;	//�v���C���[�����Ă������
	
	//-------------------------------------------------------------------------------
	// ���f���`��Ɋւ���ϐ�
	//-------------------------------------------------------------------------------
	ModelDrawer		m_CharacterModel;				//�L�����N�^�[�̃��f��
	
	//-------------------------------------------------------------------------------
	// �L�����N�^�[�̏�ԂɊւ���ϐ�
	//-------------------------------------------------------------------------------
	int		m_CharacterStock		= 0;		//�X�g�b�N
	float	m_DamagePercentage		= 0.0f;		//�_���[�W�̗�

	//-------------------------------------------------------------------------------
	// �����蔻��Ɋւ���ϐ�
	//-------------------------------------------------------------------------------
	bool						m_Invincible			= false;	//���G���ۂ�
	BoxCollider					m_CharacterCollider;				//�v���C���[�̓����蔻��
	std::vector<ATTACKPARAM>	m_AttackCollider;					//�U�������Ƃ��̓����蔻��

	//-------------------------------------------------------------------------------
	//�X�e�[�W�ɓ�����������Ɏg���ϐ�
	//-------------------------------------------------------------------------------
	Character_DamageUI m_DamageUI;

	//-------------------------------------------------------------------------------
	// �O���̃I�u�W�F�N�g��ێ�����ϐ�
	//-------------------------------------------------------------------------------
	Stage*			m_pStage = nullptr;				//�X�e�[�W�̏�񂪓���
};

class Character_State : public State
{
public:
	enum class TYPE
	{
		DEFAULT = 0,
		ATTACK,
		MAX
	};

public:
	Character_State(TYPE type) : m_StateType(type) {};
	Character_State() : Character_State(Character_State::TYPE::DEFAULT) {};
	virtual ~Character_State() {};

	Character_State::TYPE GetType();
	void SetCharacter(Character* pCharacter);
	void SetController(PlayerController* pController);
	void SetCharacterParameter(Character::CHARACTER_PARAMETER* pCharacterParameter);
	void SetStage(Stage* pStage);
	void SetModelDrawer(ModelDrawer* pModelDrawer);
	void SetCharacterCollider(BoxCollider* pCollider);
	void SetAttackCollider(std::vector<Character::ATTACKPARAM>* pAttackCollider);
	void SetMoveParameter(Character::MOVEPARAMETER* pMoveParameter);
	void SetJumpParameter(Character::JUMPPARAMETER* pJumpParameter);
	void SetBlowAwayParameter(Character::BLOWAWAYPARAMETER* pBlowAwayParameter);

public:
	virtual void Init() {};
	virtual void Uninit() {};
	virtual void Update() {};

private:
	Character_State::TYPE m_StateType = Character_State::TYPE::MAX;

protected:
	Character* m_pCharacter = nullptr;
	PlayerController* m_pController = nullptr;
	Character::CHARACTER_PARAMETER* m_pCharacterParameter = nullptr;
	Stage* m_pStage = nullptr;
	ModelDrawer* m_pModelDrawer = nullptr;
	BoxCollider* m_pCharacterCollider = nullptr;
	std::vector<Character::ATTACKPARAM>* m_pAttackCollider = nullptr;
	Character::MOVEPARAMETER* m_pMoveParameter = nullptr;
	Character::JUMPPARAMETER* m_pJumpParameter = nullptr;
	Character::BLOWAWAYPARAMETER* m_pBlowAwayParameter = nullptr;
};

//==========================================================================
//�X�}�u���Ɠ����悤�Ȗ��O�ɂ��Ă��܂�
//https://www.youtube.com/watch?v=V40sMUAE5ek
//==========================================================================

class Character_AttackState : public Character_State
{
public:
	Character_AttackState() :Character_State(Character_State::TYPE::ATTACK) {};
	virtual ~Character_AttackState() {};
	virtual void HitCharacter(Character* pHitCharacter) {};

protected:
	virtual void Init() override {};
	virtual void Uninit() override {};
	virtual void Update() override {};
};