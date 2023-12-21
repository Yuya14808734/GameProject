#pragma once
#include "Calculation.h"
#include "XboxKeyboard.h"
#include "Input.h"

//=========================================================
// �L�����N�^�[�𓮂����R���g���[���[�̏�����������
//=========================================================

class PlayerController
{
public:
	enum class PLAYCONTROLLERTYPE : int
	{
		GAMEPAD = 0,	//�R���g���[���[
		KEYBOARD,		//�L�[�{�[�h
		MAX,
	};

public:
	static void InitXPadNum();
private:
	static int m_XPadNum;		//�Ȃ��ł���R���g���[���[�𐔂��邽�߂̕ϐ�

public:
	//===============================================================
	// �R���g���[���[�̐ݒ�
	//===============================================================
	void SetController(PLAYCONTROLLERTYPE type, int PlayerNum);

	//===============================================================
	// �R���g���[���[�̎擾
	//===============================================================
	InputXPad* GetController();	//�R���g���[���[���Ȃ��ł��Ȃ��ꍇnullptr���A���Ă��܂��B
	PLAYCONTROLLERTYPE GetControllerType();	//�R���g���[���[�̃^�C�v���擾

	//===============================================================
	// �L�����N�^�[�̓��͂Ɋւ���֐�
	//===============================================================
	const CVector2& GetMoveInput();
	bool GetLeftSmash();
	bool GetJumpTrigger();
	bool GetJumpPress();
	bool GetAttack();
	const CVector2& GetLeftInputVector();

private:
	PLAYCONTROLLERTYPE m_ControllerType = PLAYCONTROLLERTYPE::MAX;	//�R���g���[���[�̎��
	InputXPad* m_pXPad = nullptr;									//�Q�[���p�b�h������ꍇ�A�p�b�h�̏�񂪓���܂��B
	int m_PlayerNum = 0;											//���̃R���g���[���[���g���L�����N�^�[�ԍ�
};