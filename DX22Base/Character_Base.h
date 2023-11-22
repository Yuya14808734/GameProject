#pragma once
#include "Calculation.h"
#include "Collider.h"
#include "ModelDrawer.h"
#include <vector>

class Attack;

class Character
{
public:
	enum class STATE
	{
		IDLE = 0,	//�ҋ@
		WALK,		//����
		DASH,		//����
		ATTACK,		//�U��
		BLOWOFF,	//������΂�
		JUMP,		//�W�����v
		FALL,		//����
		DOWN,		//�|���

		MAX,
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
	void Character_HitGround();							//�n�ʂɓ���������
	void DrawCollider();								//�R���C�_�[�̕`��

protected:

	/*����(�����X�s�[�h, ����X�s�[�h, �����Ă���Ƃ��̉��ɓ����X�s�[�h, 
	�W�����v�ł����, �W�����v�����, �d��, �����鑬��, ���C��, ��C��R)*/
	void SetParameter(
	float WalkSpeed,float DashSpeed,float  FallSideMoveSpeed,
		int MaxJumpCount,float JumpPower,float GravityScale,
		float MaxFallSpeed,float Friction,	float AirResistance);
	void SetAttack(Attack* pAttack);

protected:

	//======================================================
	//��������Ȃǂ��قړ����ɂȂ邽�ߏ�̊֐����g�����ƂɂȂ肻��

	virtual void Init() {};			//�p����̏�����
	virtual void Uninit() {};		//�p����̏I������
	virtual void Update() {};		//�p����̍X�V
	virtual void Draw() {};			//�p����̕`��

	virtual void IdleUpdate();		//�~�܂��Ă���Ƃ��̃A�b�v�f�[�g
	virtual void WalkUpdate();		//�������̃A�b�v�f�[�g
	virtual void DashUpdate();		//����Ƃ��̃A�b�v�f�[�g
	virtual void AttackUpdate();	//�U���̃A�b�v�f�[�g
	virtual void BlowOffUpdate();	//������΂��̃A�b�v�f�[�g
	virtual void JumpUpdate();		//������ł���Ƃ��̃A�b�v�f�[�g
	virtual void FallUpdate();		//�����Ă���Ƃ��̃A�b�v�f�[�g
	virtual void DownUpdate();		//�|��Ă����Ԃ̃A�b�v�f�[�g
	
	virtual void HitGround();		//�n�ʂɓ����������ɌĂ΂��

protected:
	//�U���̊��֐�
	//virtual void 


private:
	//======================================================
	//�ŏ��ɐݒ肷��p�����[�^
	int		m_PlayerBit = 0x00;				//���̃L�����N�^�[�����ԂȂ̂�������
	float	m_WalkSpeed			= 0.0f;		//�����X�s�[�h
	float	m_DashSpeed			= 0.0f;		//����X�s�[�h
	float	m_FallSideMoveSpeed = 0.0f;		//�����Ă���Ƃ��̉��ړ��̃X�s�[�h
	int		m_MaxJumpCount		= 0;		//�W�����v�ł���ő吔
	float	m_JumpPower			= 0.0f;		//�W�����v����Ƃ��̗�
	float	m_Gravity			= 0.0f;		//�d��
	float	m_MaxFallSpeed		= 0.0f;		//�ő嗎�����x
	float	m_Friction			= 0.0f;		//���C��
	float	m_AirResistance		= 0.0f;		//��C��R

protected:
	Character::STATE m_State = STATE::MAX;	//�L�����N�^�[�̏��
	ModelDrawer m_CharacterModel;			//�L�����N�^�[�̃��f��
	CVector3 m_pos;							//���W
	CVector3 m_oldPos;						//�O�̍��W
	CVector3 m_scale;						//�傫��
	CQuaternion m_rotate;					//��]��
	CVector3 m_Velocity;					//�d�͂Ȃ�
	CVector3 m_MoveVector;					//�R���g���[���[�̈ړ���
	float m_DamagePercentage = 0.0f;		//�_���[�W�̗�
	Attack* m_pNowAttack = nullptr;			//�U�����
	BoxCollider m_CharacterCollider;		//�v���C���[�̓����蔻��
	int m_JumpCount = 0;
};