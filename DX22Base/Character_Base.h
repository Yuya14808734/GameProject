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
	void Character_Init();		//�L�����N�^�[�̏�����
	void Character_Uninit();	//�L�����N�^�[�̏I������
	void Character_Update();	//�L�����N�^�[�̍X�V
	void Character_Draw();		//�L�����N�^�[�̕`��
	int GetPlayerBit();
	const Character::STATE& GetState() const;
	ModelDrawer* GetModel() const;
	const CVector3& GetPos() const;
	void SetPos(const CVector3& pos);
	const CVector3& GetScale() const;
	void SetScale(const CVector3& scale);
	const CQuaternion& GetRotate() const;
	void SetRotate(const CQuaternion& rotate);
	void SetRotate(const CVector3& rotate);
	void AddForce(const CVector3& force);
	void SetForce(const CVector3& force);
	float GetDamage() const;
	void AddDamage(float damage);
	std::vector<BoxCollider>* GetCollider() const;

protected:

	//======================================================
	//��������Ȃǂ��قړ����ɂȂ邽�ߏ�̊֐����g�����ƂɂȂ肻��

	virtual void Init();		//�p����̏�����
	virtual void Uninit();		//�p����̏I������
	virtual void Update();		//�p����̍X�V
	virtual void Draw();		//�p����̕`��


protected:
	//======================================================
	//�p�����[�^
	const float m_WalkSpeed = 0.0f;			//�����X�s�[�h
	const float m_DashSpeed = 0.0f;			//����X�s�[�h

protected:
	int m_PlayerNum = 0x00;					//���̃L�����N�^�[�����ԂȂ̂�������
	Character::STATE m_State = STATE::MAX;	//�L�����N�^�[�̏��
	ModelDrawer m_CharacterModel;			//�L�����N�^�[�̃��f��
	CVector3 m_pos;							//���W
	CVector3 m_scale;						//�傫��
	CQuaternion m_rotate;					//��]��
	CVector3 m_Velocity;					//�d�͂Ȃ�
	CVector3 m_MoveVector;					//�R���g���[���[�̈ړ���
	float m_DamagePercentage = 0.0f;		//�_���[�W�̗�
	Attack* m_pNowAttack = nullptr;			//�U�����
	std::vector<SphereCollider> m_Collider;	//�v���C���[�̍U���p�R���C�_�[(�X�e�[�W�Ƃ͓_�ōs���̂ňႢ�܂�)
};