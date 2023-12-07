#pragma once
#include "Calculation.h"
#include "Collider.h"
#include "ModelDrawer.h"
#include <vector>

class Character
{
public:
	enum class STATE : int
	{
		IDLE = 0,	//�ҋ@
		WALK,		//����
		DASH,		//����
		ATTACK,		//�U��
		SMASH,		//������΂�
		JUMPIN,		//�W�����v�̓���
		JUMP,		//�W�����v
		AIRMOVE,	//����
		DOWN,		//�|���
		MAX,
	};
	enum class ATTACK : int
	{
		ATTACK_11,		//��1
		ATTACK_12,		//��2
		ATTACK_13,		//��3
		ATTACK_S2,		//����
		ATTACK_S4,		//���X�}�b�V��
		ATTACK_AIRN,	//��N
		SPECIAL_N,		//�K�E�Z����
		SPECIAL_AIRN,	//�󒆕K�E�Z
		MAX,
	};

	enum class LOOKDIR : int
	{
		RIGHT = 0,
		LEFT,
		UP,
		DOWN,
		MAX
	};

	struct AttackParam
	{
		bool m_Use = false;									//���̍U���̓����蔻����s����
		BoxCollider m_BoxCollider;							//�U���̓����蔻��
		unsigned int m_HitCharacterBit = 0x00;				//�O�̃t���[���œ��������L�����N�^�[�̃r�b�g�ԍ�������
		unsigned int m_CanAttackCharacterBit = 0x00;		//�����邱�Ƃ��o����L�����N�^�[�̃r�b�g�ԍ�
		unsigned int m_haveHitCharacterBit = 0x00;			//���܂łœ����������Ƃ�����L�����N�^�[�r�b�g�ԍ�
	};

public:
	static void InitPlayerBit();	//���̊֐��ł��炦��ԍ�������������
protected:
	static int GetNewPlayerBit();	//�V�����v���C���[�̔ԍ�(2�i��)���󂯎��
									//�ςȂƂ���ŌĂԂƔԍ�������Ă��܂��̂�Init�ȊO�ŌĂ΂Ȃ��悤��
private:
	static int m_NewPlayerBit;		//�V�����v���C���[�̃r�b�g�ԍ�


public:
	Character() {};
	~Character() {};
	void Character_Init();								//�L�����N�^�[�̏�����
	void Character_Uninit();							//�L�����N�^�[�̏I������
	void Character_Update();							//�L�����N�^�[�̍X�V
	void Character_Draw();								//�L�����N�^�[�̕`��
	int GetCharacterBit();								//�L�����N�^�[�ԍ��̎擾
	const Character::STATE& GetState() const;			//���̏�Ԃ̎擾
	const Character::ATTACK& GetAttack() const;			//�����Ă���U�����
	ModelDrawer* GetModel() const;						//���f�����̎擾
	const CVector3& GetPos() const;						//�ʒu�̎擾
	void SetPos(const CVector3& pos);					//�ʒu�̐ݒ�
	const CVector3& GetOldPos() const;					//�O�̍��W���擾
	void SetOldPos();									//�O�̍��W��ݒ�
	const CVector3& GetScale() const;					//�T�C�Y�̎擾
	void SetScale(const CVector3& scale);				//�T�C�Y�̐ݒ�
	const CQuaternion& GetRotate() const;				//��]�ʂ̎擾
	void SetRotate(const CQuaternion& rotate);			//��]�ʂ̐ݒ�(Quaternion)
	void SetRotate(const CVector3& rotate);				//��]�ʂ̐ݒ�(�x���@)
	void AddForce(const CVector3& force);				//�͂𑫂��Ă��
	void SetForce(const CVector3& force);				//�͂�ݒ�
	float GetDamage() const;							//�_���[�W�̎擾
	void AddDamage(float damage);						//�_���[�W�̉��Z
	void SetDamage(float damage);						//�_���[�W�̐ݒ�
	BoxCollider* GetCharacterCollider() const;			//�L�����N�^�[�A�X�e�[�W�����蔻��̎擾
	std::vector<AttackParam>& GetAttackCollider();		//�U���R���C�_�[�̎擾
	void Character_ColliderInit();
	void Character_HitCeiling();						//�V��ɓ�������	
	void Character_HitGround();							//�n�ʂɓ�������
	void Character_HitWall();							//�ǂɓ�������
	void DrawCollider();								//�R���C�_�[�̕`��

protected:
	void ChangeAttack(Character::ATTACK attack);
	void ChangeState(Character::STATE state);

protected:

	virtual void Init() {};			//�p����̏�����
	virtual void Uninit() {};		//�p����̏I������
	virtual void Update() {};		//�p����̍X�V
	virtual void Draw() {};			//�p����̕`��

	//==========================================================================
	virtual void IdleInit();		//�~�܂��Ă���Ƃ��̏�����
	virtual void IdleUninit();		//�~�܂��Ă���Ƃ��̏I������
	virtual void IdleUpdate();		//�~�܂��Ă���Ƃ��̃A�b�v�f�[�g
	//==========================================================================
	virtual void WalkInit();		//�������̏�����
	virtual void WalkUninit();		//�������̏I������
	virtual void WalkUpdate();		//�������̃A�b�v�f�[�g
	//==========================================================================
	virtual void DashInit();		//����Ƃ��̏�����
	virtual void DashUninit();		//����Ƃ��̏I������
	virtual void DashUpdate();		//����Ƃ��̃A�b�v�f�[�g
	//==========================================================================
	virtual void AttackInit();		//�U������Ƃ��̏�����
	virtual void AttackUninit();	//�U������Ƃ��̏I������
	virtual void AttackUpdate();	//�U������Ƃ��̃A�b�v�f�[�g
	//==========================================================================
	virtual void SmashInit();		//������΂���鎞�̏�����
	virtual void SmashUninit();		//������΂��̏I������
	virtual void SmashUpdate();		//������΂��̃A�b�v�f�[�g
	//==========================================================================
	virtual void JumpInInit();		//�W�����v�n�߂̏�����
	virtual void JumpInUpdate();	//�W�����v�n�߂̃A�b�v�f�[�g
	virtual void JumpInUninit();	//�W�����v�n�߂̏I������
	//==========================================================================
	virtual void JumpInit();		//�W�����v�����Ƃ��̏�����
	virtual void JumpUninit();		//�W�����v�����Ƃ��̏I������
	virtual void JumpUpdate();		//�W�����v�����Ƃ��̃A�b�v�f�[�g
	//==========================================================================
	virtual void AirMoveInit();		//�󒆂ɂ���Ƃ��̏�����
	virtual void AirMoveUninit();	//�󒆂ɂ���Ƃ��̏I������
	virtual void AirMoveUpdate();	//�����Ă���Ƃ��̃A�b�v�f�[�g
	//==========================================================================
	virtual void DownInit();		//�|�ꂽ���̏�����
	virtual void DownUninit();		//�|�ꂽ���̏I������
	virtual void DownUpdate();		//�|��Ă����Ԃ̃A�b�v�f�[�g
	
	//==========================================================================
	//�X�}�u���Ɠ����悤�Ȗ��O�ɂ��Ă��܂�
	//https://www.youtube.com/watch?v=V40sMUAE5ek
	//==========================================================================
	virtual void Attack11_Init() {};		//��1
	virtual void Attack11_Update() {};		//��1
	virtual void Attack11_Uninit() {};		//��1
	//==========================================================================
	virtual void Attack12_Init() {};		//��2
	virtual void Attack12_Update() {};		//��2
	virtual void Attack12_Uninit() {};		//��2
	//==========================================================================
	virtual void Attack13_Init() {};		//��3
	virtual void Attack13_Update() {};		//��3
	virtual void Attack13_Uninit() {};		//��3
	//==========================================================================
	virtual void AttackS2_Init() {};		//����
	virtual void AttackS2_Update() {};		//����
	virtual void AttackS2_Uninit() {};		//����
	//==========================================================================
	virtual void AttackS4_Init() {};		//���X�}�b�V��
	virtual void AttackS4_Update() {};		//���X�}�b�V��
	virtual void AttackS4_Uninit() {};		//���X�}�b�V��
	//==========================================================================
	virtual void AttackAirN_Init() {};		//��N
	virtual void AttackAirN_Update() {};	//��N
	virtual void AttackAirN_Uninit() {};	//��N
	//==========================================================================
	virtual void SpecialN_Init() {};		//�ʏ�K�E�Z
	virtual void SpecialN_Update() {};		//�ʏ�K�E�Z
	virtual void SpecialN_Uninit() {};		//�ʏ�K�E�Z
	//==========================================================================
	virtual void SpecialAirN_Init() {};		//�ʏ�K�E�Z(��)
	virtual void SpecialAirN_Update() {};	//�ʏ�K�E�Z(��)
	virtual void SpecialAirN_Uninit() {};	//�ʏ�K�E�Z(��)

public:
	virtual void Attack11_Hit(Character* HitCharacter) {};			//��1
	virtual void Attack12_Hit(Character* HitCharacter) {};			//��2
	virtual void Attack13_Hit(Character* HitCharacter) {};			//��3
	virtual void AttackS2_Hit(Character* HitCharacter) {};			//����
	virtual void AttackS4_Hit(Character* HitCharacter) {};			//���X�}�b�V��
	virtual void AttackAirN_Hit(Character* HitCharacter) {};		//��N
	virtual void SpecialN_Hit(Character* HitCharacter) {};			//�ʏ�K�E�Z
	virtual void SpecialAirN_Hit(Character* HitCharacter) {};		//�ʏ�K�E�Z(��)


protected:

	virtual void HitCeiling() {};		//�V��ɓ����������ɌĂ�
	virtual void HitGround() {};	//�n�ʂɓ����������ɌĂ΂��
	virtual void HitWall() {};		//�ǂɓ����������ɌĂ�

protected:
	//===============================================================================
	// �p�����[�^�ꗗ
	//===============================================================================
	
	//-------------------------------------------------------------------------------
	// ���ړ��Ɋւ���p�����[�^
	//-------------------------------------------------------------------------------
	void SetMoveParameter(float WalkSpeed, float DashSpeed, float AirSideMoveSpeed)
	{
		m_WalkSpeed = WalkSpeed;
		m_DashSpeed = DashSpeed;
		m_AirSideMoveSpeed = AirSideMoveSpeed;
	}

	float	m_WalkSpeed			= 0.0f;		//�����X�s�[�h
	float	m_DashSpeed			= 0.0f;		//����X�s�[�h
	float	m_AirSideMoveSpeed = 0.0f;		//�����Ă���Ƃ��̉��ړ��̃X�s�[�h
	//-------------------------------------------------------------------------------
	// �W�����v�Ɋւ���p�����[�^
	//-------------------------------------------------------------------------------
	void SetjumpParameter(int MaxJumpCount, int MiniJumpEndCount, int ChargeJumpStartCount,
		float FirstMiniJumpPower, float FirstJumpPower, float SecondJumpPower,
		float Gravity, float DefaultFallSpeed, float SpeedupFallSpeed)
	{
		m_MaxJumpCount = MaxJumpCount;
		m_MiniJumpEndCount = MiniJumpEndCount;
		m_ChargeJumpStartCount = ChargeJumpStartCount;
		m_FirstMiniJumpPower = FirstMiniJumpPower;
		m_FirstJumpPower = FirstJumpPower;
		m_SecondJumpPower = SecondJumpPower;
		m_Gravity = Gravity;
		m_DefaultFallSpeed = DefaultFallSpeed;
		m_SpeedUpFallSpeed = SpeedupFallSpeed;
	}

	int		m_MaxJumpCount			= 0;	//�W�����v�ł���ő吔
	int		m_MiniJumpEndCount		= 0;	//���W�����v����Ƃ��̃t���[��
	int		m_ChargeJumpStartCount	= 0;		//�W�����v����܂ł̃`���[�W����
	float	m_FirstMiniJumpPower	= 0.0f;	//���W�����v������Ƃ��̗�
	float	m_FirstJumpPower		= 0.0f;		//�W�����v����Ƃ��̗�
	float	m_SecondJumpPower		= 0.0f;		//���ڂ̃W�����v�̗�
	float	m_Gravity				= 0.0f;		//�d��
	float	m_DefaultFallSpeed		= 0.0f;		//�ő嗎�����x
	float	m_SpeedUpFallSpeed		= 0.0f;		//�������ɉ����������ꍇ�̗�����

	//-------------------------------------------------------------------------------
	// �ړ��X�s�[�h�̌����Ɋւ���p�����[�^
	//-------------------------------------------------------------------------------
	void SetResistance(float Friction, float AirDrag)
	{
		m_Friction = Friction;
		m_AirDrag = AirDrag;
	}

	float	m_Friction	= 0.0f;		//���C��
	float	m_AirDrag	= 0.0f;		//��C��R

	//-------------------------------------------------------------------------------
	// ������΂��ꂽ���Ɋւ���p�����[�^
	//-------------------------------------------------------------------------------
	float m_SmashMitigation = 0.0f;			//������΂��ꂽ���ɂǂꂭ�炢�キ���Ă�����
	float m_VectorChangePower = 0.0f;		//������΂��ꂽ���Ƀx�N�g���ύX���銄��
	float m_MinimumSmashLength = 0.0f;		//�������ł���Ɣ��肷��Œ዗��


	//===============================================================================
	// �ϐ��ꗗ
	//===============================================================================
protected:
	int		m_PlayerBit = 0x00;				//���̃L�����N�^�[�����ԂȂ̂�������
	
	//-------------------------------------------------------------------------------
	// �v���C���[�X�e�[�g�Ɋւ���ϐ�
	//-------------------------------------------------------------------------------
	Character::STATE m_NowState	 = STATE::MAX;	//�L�����N�^�[�̏��
	Character::STATE m_NextState = STATE::MAX;	//�L�����N�^�[�̏��
	Character::ATTACK m_NowAttack = ATTACK::MAX;	//�v���C���[�����Ă���U��
	Character::LOOKDIR m_NowLookDir = LOOKDIR::MAX;	//�v���C���[�����Ă������
	bool	m_ChangeState		= false;
	
	//-------------------------------------------------------------------------------
	// ���f���`��Ɋւ���ϐ�
	//-------------------------------------------------------------------------------
	ModelDrawer m_CharacterModel;			//�L�����N�^�[�̃��f��
	
	//-------------------------------------------------------------------------------
	// ���W�Ɋւ���ϐ�
	//-------------------------------------------------------------------------------
	CVector3 m_pos;							//���W
	CVector3 m_oldPos;						//�O�̍��W
	CVector3 m_scale;						//�傫��
	CQuaternion m_rotate;					//��]��
	CVector3 m_Velocity;					//�d�͂Ȃ�
	CVector3 m_MoveVector;					//�R���g���[���[�̈ړ���
		
	//-------------------------------------------------------------------------------
	// �����蔻��Ɋւ���ϐ�
	//-------------------------------------------------------------------------------
	BoxCollider m_CharacterCollider;		//�v���C���[�̓����蔻��
	std::vector<AttackParam> m_AttackCollider;	//�U�������Ƃ��̓����蔻��
	float m_DamagePercentage = 0.0f;		//�_���[�W�̗�

	//-------------------------------------------------------------------------------
	// �W�����v�Ɋւ���ϐ�
	//-------------------------------------------------------------------------------
	int m_JumpCount = 0;					//���W�����v������
	int m_JumpCharageCount = 0;				//�W�����v���`���[�W���鎞�̃J�E���g

	//-------------------------------------------------------------------------------
	//�X�e�[�W�ɓ�����������Ɏg���ϐ�
	//-------------------------------------------------------------------------------
	bool m_HitGround = false;				//�O�̃t���[���Œn�ʂɓ���������
	bool m_HitCeiling = false;				//�O�̃t���[���œV��ɓ���������
	bool m_HitWall = false;					//�O�̃t���[���ŕǂɓ���������
};