#pragma once
#include "Calculation.h"
#include "XboxKeyboard.h"
#include "Input.h"
#include <array>

//=========================================================
//�R���g���[���[�̏�����������
//=========================================================

//�ړI�F�R���g���[���[���ڑ����ꂽ��L�[�{�[�h���낤���p�b�h���낤�������������̃N���X��
//		����������(����{�^�����������ɃL�[�{�[�h�Ȃ�Enter�A�p�b�h�Ȃ�B������������True�Ȃ�)
//		����ɂ��Ⴄ�R���g���[���[�ł��O���猩���瓯���悤�Ɍ��邱�Ƃ��ł���

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
	static void PlayerController_Init();
	static std::array<PlayerController, 5>& GetPlayerControllers();
	static void InitXPadNum();

private:
	static std::array<PlayerController,5> m_PlayerControllers;				//�ڑ����ꂽ�R���g���[���[����
	static int m_XPadNum;											//�Ȃ��ł���R���g���[���[�𐔂��邽�߂̕ϐ�

public:
	//===============================================================
	// �R���X�g���N�^�E�f�X�g���N�^
	//===============================================================
	PlayerController() {};
	~PlayerController() {};

	//===============================================================
	// �R���g���[���[�̐ݒ�
	//===============================================================
	void SetController(PLAYCONTROLLERTYPE type, int PlayerNum);

	//===============================================================
	// �R���g���[���[�̎擾
	//===============================================================
	bool IsConnect();
	InputXPad* GetController();				//�R���g���[���[���Ȃ��ł��Ȃ��ꍇnullptr���A���Ă��܂��B
	PLAYCONTROLLERTYPE GetControllerType();	//�R���g���[���[�̃^�C�v���擾

	//===============================================================
	//���͂Ɋւ���֐�
	//===============================================================
	bool IsPushAnyBotton();					//�Ȃ񂩍��Ȃ�
	bool IsReturn();
	bool IsBack();
	bool GetRightArrow();
	bool GetUpArrow();
	bool GetDownArrow();
	bool GetLeftArrow();
	const CVector2& GetMoveInput();
	bool GetLeftSmash();
	bool GetJumpTrigger();
	bool GetJumpPress();
	bool GetAttack();
	const CVector2& GetLeftInputVector();
	bool GetWakeUp();

private:
	PLAYCONTROLLERTYPE m_ControllerType = PLAYCONTROLLERTYPE::MAX;	//�R���g���[���[�̎��
	InputXPad* m_pXPad = nullptr;									//�Q�[���p�b�h������ꍇ�A�p�b�h�̏�񂪓���܂��B
	int m_PlayerNum = 0;											//���̃R���g���[���[���g���L�����N�^�[�ԍ�(0�`)
};