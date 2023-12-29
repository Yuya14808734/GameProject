#pragma once
#ifndef __XBOXKEYBOARD_H__
#define __XBOXKEYBOARD_H__

#include <Windows.h>
#include <Xinput.h>
#pragma comment(lib, "xinput.lib")
#include <iostream>
#include<DirectXMath.h>
#include "string.h"

#define TRIGGER (m_state.Gamepad.wButtons & m_oldstate.Gamepad.wButtons ^ m_state.Gamepad.wButtons)
#define RELEASE (m_state.Gamepad.wButtons & m_oldstate.Gamepad.wButtons ^ m_oldstate.Gamepad.wButtons)

using namespace std;

enum class PadButton
{
	A_BUTTON,                   //A�{�^��
	B_BUTTON,                   //B�{�^��
	X_BUTTON,                   //X�{�^��
	Y_BUTTON,                   //Y�{�^��
	START_BUTTON,               //START�{�^��
	BACK_BUTTON,                //BACK�{�^��
	LEFT_SHOULDER,				//�����ɂ��Ă����̃{�^��(LB)
	RIGHT_SHOULDER,				//�E���ɂ��Ă����̃{�^��(RB)
	UP_BUTTON,                  //��{�^��
	DOWN_BUTTON,                //���{�^��
	LEFT_BUTTON,                //���{�^��
	RIGHT_BUTTON,               //�E�{�^��
	LEFT_TRIGGER,		        //���g���K�[(LT)
	RIGHT_TRIGGER,			    //�E�g���K�[(RT)
	LEFT_STICK,			        //���X�e�B�b�N
	RIGHT_STICK				    //�E�X�e�B�b�N
};


class InputXPad
{
public:
	static InputXPad* GetXPad(int index);			//X�{�b�N�X�R���g���[���[�̏����擾����֐�(�Ȃ��ꍇ��null���A���Ă���
	static void XpadInit();
	static void XpadUpdate();

private:
	static InputXPad m_XInputArray[4];


public:
	bool IsPadConnect();
	void UpdateGamePad();													//Xbox�R���g���[���[�̏����擾����֐�(Update�̏��߂̕��ɏ����܂��傤) 
	int InputPressKey(PadButton key);										//�v���X�L�[�̓��͊֐�
	int InputTriggerKey(PadButton key);										//�g���K�[�L�[�̓��͊֐�
	int InputReleaseKey(PadButton key);										//�����[�X�L�[�̓��͊֐�
	DirectX::XMFLOAT2 GetPressStick();										//�v���X����Ă���X�e�B�b�N�̒l��Ԃ��֐�(DirectX::Float2�^�ł��A�Ԃ����l�ɕ⊮�������l���|���܂��傤)
	const DirectX::XMFLOAT2& GetPressRightStick();
	const DirectX::XMFLOAT2& GetPressLeftStick();
	void SetPressRightStick();
	void SetPressLeftStick();
	bool GetRightSmash(float SmashValue = 0.25f);
	bool GetLeftSmash(float SmashValue = 0.25f);
	float GetPressTrigger();												//�v���X����Ă���g���K�[�̒l��Ԃ�
	DirectX::XMFLOAT2 GetTriggerStick();									//�g���K�[��Ԃ̃X�e�B�b�N�̒l��Ԃ�(�댯!�o���邾��GetPressStick()�ő�p���܂��傤)              
	float GetTriggerTrigger();												//�g���K�[��Ԃ̃g���K�[�̒l��Ԃ�

	int AllKeyPress();														//�S�Ẵv���X���͊֐�
	int AllKeyTrigger();													//�S�Ẵg���K�[���͊֐�
	int AlfaKeyTrigger();													//ABXY�݂̂ɑΉ������g���K�[����
	int AlfaKeyPress();														//ABXY�݂̂ɑΉ������v���X����
	WORD StickChangeButton(SHORT StickX, SHORT StickY, SHORT DeadZone);		//�X�e�B�b�N���͂��L�[���͂ɕϊ�                   
	WORD TriggerChangeButton(BYTE Trigger, BYTE DeadZone);					//�g���K�[�̓��͂��L�[���͂ɕϊ�
	WORD TriggerChangeButtonReleaseVer(BYTE Trigger, BYTE DeadZone);        //�g���K�[�L�[�̓��͂��L�[���͂ɕϊ�(ReleaseVer)

	void SetPowerVibration(WORD Left, WORD RIGHT);							//�o�C�u���[�V�����̋����ݒ�
	void SetVibration(int num);												//�o�C�u���[�V�����N��(�t���[���w��ł���p)
	void MoveVibration();													//�o�C�u���[�V�������N��(����)
	void StopVibration();													//�o�C�u���[�V�����������I��

private:
	
	int m_ControllerNum = 0;
	DWORD m_dwResult;			//���R���g���[���[���Ȃ��ł���̂��Ȃǂ̏�񂪓���
	XINPUT_STATE m_state;     //XINPUT_STATE�^�̍\���̐錾(�R���g���[���[�̕ύX�����������A���݂̏��)
	XINPUT_STATE m_oldstate;

	XINPUT_VIBRATION vibration;
	int Vibtime = 0;
	bool Stop = false;

	DirectX::XMFLOAT2 m_NowRightStickValue = DirectX::XMFLOAT2(0.0f, 0.0f);
	DirectX::XMFLOAT2 m_OldRightStickValue = DirectX::XMFLOAT2(0.0f, 0.0f);
	DirectX::XMFLOAT2 m_NowLeftStickValue = DirectX::XMFLOAT2(0.0f, 0.0f);
	DirectX::XMFLOAT2 m_OldLeftStickValue = DirectX::XMFLOAT2(0.0f, 0.0f);
	float m_RightStickMoveValue = 0.0f;
	float m_LeftStickMoveValue = 0.0f;
};

#endif
