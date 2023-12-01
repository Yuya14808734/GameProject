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

public:
	static void InitPlayerBit();	//���̊֐��ł��炦��ԍ�������������
protected:
	static int GetNewPlayerBit();	//�V�����v���C���[�̔ԍ�(2�i��)���󂯎��
									//�ςȂƂ���ŌĂԂƔԍ�������Ă��܂�
private:
	static int m_NewPlayerBit;		//�V�����v���C���[�̃r�b�g�ԍ�


public:
	Character() {};
	~Character() {};
	void Character_Init();								//�L�����N�^�[�̏�����
	void Character_Uninit();							//�L�����N�^�[�̏I������
	void Character_Update();							//�L�����N�^�[�̍X�V
	void Character_Draw();								//�L�����N�^�[�̕`��
	int GetPlayerBit();									//�L�����N�^�[�ԍ��̎擾
	const Character::STATE& GetState() const;			//���̏�Ԃ̎擾
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
	std::vector<BoxCollider>& GetAttackCollider();		//�U���R���C�_�[�̎擾
	void Character_ColliderInit();
	void Character_HitCeiling();						//�V��ɓ�������	
	void Character_HitGround();							//�n�ʂɓ�������
	void Character_HitWall();							//�ǂɓ�������
	void DrawCollider();								//�R���C�_�[�̕`��

protected:

	/*����(�����X�s�[�h, ����X�s�[�h, �����Ă���Ƃ��̉��ɓ����X�s�[�h, 
	�W�����v�ł����, �W�����v�����, �d��, �����鑬��, ���C��, ��C��R)*/
	void SetParameter(
	float WalkSpeed,float DashSpeed,float  FallSideMoveSpeed,
		int MaxJumpCount,float JumpPower,float GravityScale,
		float DefaultFallMaxSpeed,float UpFallMaxSpeed ,float Friction,	float AirResistance);
	void SetAttack(Character::ATTACK attack);
	void ChangeState(Character::STATE state);

protected:

	//======================================================
	//��������Ȃǂ��قړ����ɂȂ邽�ߏ�̊֐����g�����ƂɂȂ肻��

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


	virtual void HitCeiling() {};		//�V��ɓ����������ɌĂ�
	virtual void HitGround() {};	//�n�ʂɓ����������ɌĂ΂��
	virtual void HitWall() {};		//�ǂɓ����������ɌĂ�

	//======================================================
	//�ŏ��ɐݒ肷��p�����[�^
private:
	int		m_PlayerBit = 0x00;				//���̃L�����N�^�[�����ԂȂ̂�������

protected:
	float	m_WalkSpeed			= 0.0f;		//�����X�s�[�h
	float	m_DashSpeed			= 0.0f;		//����X�s�[�h
	float	m_FallSideMoveSpeed = 0.0f;		//�����Ă���Ƃ��̉��ړ��̃X�s�[�h
	int		m_MaxJumpCount		= 0;		//�W�����v�ł���ő吔
	float	m_JumpPower			= 0.0f;		//�W�����v����Ƃ��̗�
	float	m_Gravity			= 0.0f;		//�d��
	float	m_DefaultMaxFallSpeed = 0.0f;	//�ő嗎�����x
	float	m_UpMaxFallSpeed	= 0.0f;		//�������ɉ����������ꍇ�̗�����
	float	m_Friction			= 0.0f;		//���C��
	float	m_AirResistance		= 0.0f;		//��C��R

protected:
	Character::STATE m_NowState	 = STATE::MAX;	//�L�����N�^�[�̏��
	Character::STATE m_NextState = STATE::MAX;	//�L�����N�^�[�̏��
	Character::ATTACK m_NowAttack = ATTACK::MAX;	//�v���C���[�����Ă���U��
	Character::LOOKDIR m_NowLook = LOOKDIR::MAX;	//�v���C���[�����Ă������
	bool	m_ChangeState		= false;
	ModelDrawer m_CharacterModel;			//�L�����N�^�[�̃��f��
	CVector3 m_pos;							//���W
	CVector3 m_oldPos;						//�O�̍��W
	CVector3 m_scale;						//�傫��
	CQuaternion m_rotate;					//��]��
	CVector3 m_Velocity;					//�d�͂Ȃ�
	CVector3 m_MoveVector;					//�R���g���[���[�̈ړ���
	float m_DamagePercentage = 0.0f;		//�_���[�W�̗�
	BoxCollider m_CharacterCollider;		//�v���C���[�̓����蔻��
	std::vector<BoxCollider> m_AttackCollider;	//�U�������Ƃ��̓����蔻��
	int m_JumpCount = 0;					//���W�����v������
	bool m_HitGround = false;				//�O�̃t���[���Œn�ʂɓ���������
	bool m_HitCeiling = false;				//�O�̃t���[���œV��ɓ���������
	bool m_HitWall = false;					//�O�̃t���[���ŕǂɓ���������
};