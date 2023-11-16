#pragma once

#include "Character_Base.h"
#include "ModelDrawer.h"
#include "Collider.h"
#include <vector>

//======================================================
//class Attack
//�U�����܂Ƃ߂�N���X
//�U�����߂���Ō�܂ł̈ȉ��̎����Ǘ�����
//�E���������v���C���[
//�E�����蔻��
//�E���f���̃A�j���[�V����
//�E�L�����N�^�[�̈ړ�

class Attack
{
public:
	Attack() {};
	~Attack() {};

	void Attack_Init();
	void Attack_Uninit();
	void Attack_Update();
	void Attack_Draw();

	void SetCharacter(Character* character);			//�L�����N�^�[�̐ݒ�

protected:

	virtual void Init() {};
	virtual void Uninit() {};
	virtual void Update() {};
	virtual void Draw() {};

protected:
	const int AttackEndFrame = 0;				//�U������Ⴄ�X�e�[�g�ɕύX����t���[��

private:
	Character* m_pMyCharacter = nullptr;		//�U�������Ă���L�����N�^�[
	ModelDrawer* m_pCharacterModel = nullptr;	//�L�����N�^�[�̃��f�����
	int m_FrameCount = 0;						//�U�����n�܂��Ă���̃t���[��
	int m_HitPlayerBit = 0x00;					//���������v���C���[�ԍ�
	Character::STATE m_CharacterNextState;		//�U���I��������̃L�����N�^�[�̏��
	std::vector<SphereCollider> m_AttackCollider;	//�U���̃R���C�_�[(�ꉞ�����̓����蔻������Ă�悤��)
													//��ѓ���Ȃǂ̓A�C�e���Ȃǂ�����Ă����œ����蔻����s��
};