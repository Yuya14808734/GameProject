#include "XboxKeyboard.h"
#include <math.h>

#define RightStickDeadZone (5000)

DWORD dwResult;
XINPUT_STATE state;     //XINPUT_STATE�^�̍\���̐錾(�R���g���[���[�̕ύX�����������A���݂̏��)
XINPUT_STATE oldstate;

XINPUT_VIBRATION vibration;
int Vibtime = 0;
bool Stop = false;

DirectX::XMFLOAT2 NowRightStickValue = DirectX::XMFLOAT2(0.0f,0.0f);
DirectX::XMFLOAT2 OldRightStickValue = DirectX::XMFLOAT2(0.0f, 0.0f);
DirectX::XMFLOAT2 NowLeftStickValue = DirectX::XMFLOAT2(0.0f, 0.0f);
DirectX::XMFLOAT2 OldLeftStickValue = DirectX::XMFLOAT2(0.0f, 0.0f);
float RightStickMoveValue = 0.0f;
float LeftStickMoveValue = 0.0f;

//====================================================================
//�p�r�@�F�R���g���[���[�̏�Ԃ��擾(�X�V)
//�߂�l�F�Ȃ�
//�g�����Fmain.cpp��Game.cpp��Update�֐��̏��߂̂ق��ɏ����Ă�������
//���ӓ_�F���݃R���g���[���[�͈��݂̂̐ݒ�ɂ��Ă���܂�
//=====================================================================
void UpdateGamePad()
{
	ZeroMemory(&oldstate, sizeof(XINPUT_STATE));
	oldstate = state;
	static int Count = 0;

	//�O�̃t���[���ŃX�e�B�b�N�̓|������
	OldRightStickValue = GetPressRightStick();
	OldLeftStickValue = GetPressLeftStick();

	for (DWORD i = 0; i < 1; i++)
	{		                      
		ZeroMemory(&state, sizeof(XINPUT_STATE));      //XINPUT_STATE�^�̃�����������

	    //XInput����R���g���[���̏����擾(��Ώ����Ȃ���)
		dwResult = XInputGetState(i, &state);    //����(�R���g���[���[�̃C���f�b�N�X�A XINPUT_STATE�\���̂ւ̃|�C���^)		

		//�o�C�u���[�V�����̐ݒ�
		ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
		vibration.wLeftMotorSpeed = 0;                       //�o�C�u���[�V�����̋����ݒ�(�Ƃ肠�����K���Ȓl�ŏ��������Ă��܂�)
		vibration.wRightMotorSpeed = 0;
	}

	if (Stop != false)
	{
		Count++;
		if (Count > Vibtime)
		{
			SetPowerVibration(0, 0);
			XInputSetState(0, &vibration);
			Count = 0;
			Stop = false;
		}
	}

	//���̃X�e�B�b�N�̓|�����ʂ�ݒ�
	SetPressRightStick();
	SetPressLeftStick();

	//�X�e�B�b�N���O�̃t���[������ǂꂭ�炢�������̂���ݒ�
	float leftmoveX = NowLeftStickValue.x - OldLeftStickValue.x;
	float leftmoveY = NowLeftStickValue.y - OldLeftStickValue.y;
	LeftStickMoveValue = sqrtf(leftmoveX * leftmoveX + leftmoveY * leftmoveY);

	float rightmoveX = NowRightStickValue.x - OldRightStickValue.x;
	float rightmoveY = NowRightStickValue.y - OldRightStickValue.y;
	RightStickMoveValue = sqrtf(rightmoveX * rightmoveX + rightmoveY * rightmoveY);
}

//====================================================================
//�p�r�@�F������Ă���L�[�̔���
//�߂�l�F���ɍl�����Ȃ��Ă悢
//�g�����Fif���ň͂��Ă�����Ƃ�낵������
//���ӓ_�F�Ȃ�
//=====================================================================
int InputPressKey(PadButton key)
{
	switch (key)
	{
	case PadButton::A_BUTTON:
		return (state.Gamepad.wButtons & XINPUT_GAMEPAD_A);
		break;
	case PadButton::B_BUTTON:
		return (state.Gamepad.wButtons & XINPUT_GAMEPAD_B);
		break;
	case PadButton::X_BUTTON:
		return (state.Gamepad.wButtons & XINPUT_GAMEPAD_X);
		break;
	case PadButton::Y_BUTTON:
		return (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y);
		break;
	case PadButton::START_BUTTON:
		return (state.Gamepad.wButtons & XINPUT_GAMEPAD_START);
		break;
	case PadButton::BACK_BUTTON:
		return (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK);
		break;
	case PadButton::LEFT_SHOULDER:
		return (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER);
		break;
	case PadButton::RIGHT_SHOULDER:
		return (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER);
		break;
	case PadButton::UP_BUTTON:
		return (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP);
		break;
	case PadButton::DOWN_BUTTON:
		return (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN);
		break;
	case PadButton::LEFT_BUTTON:
		return (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT);
		break;
	case PadButton::RIGHT_BUTTON:
		return (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT);
		break;
	case PadButton::LEFT_TRIGGER:
		return (state.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
		break;
	case PadButton::RIGHT_TRIGGER:
		return (state.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
		break;
	case PadButton::LEFT_STICK:
		return (((state.Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) || (state.Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
			|| ((state.Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) || (state.Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)));
		break;
	case PadButton::RIGHT_STICK:
		return (((state.Gamepad.sThumbRX > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) || (state.Gamepad.sThumbRX < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE))
			|| ((state.Gamepad.sThumbRY > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) || (state.Gamepad.sThumbRY < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)));
		break;
	default:
		return 0;
		break;
	}
}

//====================================================================
//�p�r�@�F�������u�Ԃ̃L�[�̔���
//�߂�l�F���ɍl�����Ȃ��Ă悢
//�g�����Fif���ň͂��Ă�����Ƃ�낵������
//���ӓ_�F�Ȃ�
//=====================================================================
int InputTriggerKey(PadButton key)
{
	switch (key)
	{
	case PadButton::A_BUTTON:
		return TRIGGER & XINPUT_GAMEPAD_A;  //�r�b�g���Z^(�r���IOR���Z) &(AND���Z)
		break;
	case PadButton::B_BUTTON:
		return TRIGGER & XINPUT_GAMEPAD_B;
		break;
	case PadButton::X_BUTTON:
		return TRIGGER & XINPUT_GAMEPAD_X;
		break;
	case PadButton::Y_BUTTON:
		return TRIGGER & XINPUT_GAMEPAD_Y;
		break;
	case PadButton::START_BUTTON:
		return TRIGGER & XINPUT_GAMEPAD_START;
		break;
	case PadButton::BACK_BUTTON:
		return TRIGGER & XINPUT_GAMEPAD_BACK;
		break;
	case PadButton::LEFT_SHOULDER:
		return TRIGGER & XINPUT_GAMEPAD_LEFT_SHOULDER;
		break;
	case PadButton::RIGHT_SHOULDER:
		return TRIGGER & XINPUT_GAMEPAD_RIGHT_SHOULDER;
		break;
	case PadButton::UP_BUTTON:
		return TRIGGER & XINPUT_GAMEPAD_DPAD_UP;
		break;
	case PadButton::DOWN_BUTTON:
		return TRIGGER & XINPUT_GAMEPAD_DPAD_DOWN;
		break;
	case PadButton::LEFT_BUTTON:
		return TRIGGER & XINPUT_GAMEPAD_DPAD_LEFT;
		break;
	case PadButton::RIGHT_BUTTON:
		return TRIGGER & XINPUT_GAMEPAD_DPAD_RIGHT;
		break;
	case PadButton::LEFT_TRIGGER:
		state.Gamepad.wButtons |= TriggerChangeButton(state.Gamepad.bLeftTrigger, XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
		return (TRIGGER & state.Gamepad.wButtons && InputPressKey(PadButton::LEFT_TRIGGER));
		break;
	case PadButton::RIGHT_TRIGGER:
		state.Gamepad.wButtons |= TriggerChangeButton(state.Gamepad.bRightTrigger, XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
		return (TRIGGER & state.Gamepad.wButtons) && InputPressKey(PadButton::RIGHT_TRIGGER);
		break;
	case PadButton::LEFT_STICK:
		state.Gamepad.wButtons |= StickChangeButton(
			state.Gamepad.sThumbLX, state.Gamepad.sThumbLY, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
		return (TRIGGER & state.Gamepad.wButtons && InputPressKey(PadButton::LEFT_STICK));
		break;
	case PadButton::RIGHT_STICK:
		state.Gamepad.wButtons |= StickChangeButton(
			state.Gamepad.sThumbRX, state.Gamepad.sThumbRY, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
		return (TRIGGER & state.Gamepad.wButtons && InputPressKey(PadButton::RIGHT_STICK));
		break;	
	default:
		return 0;
		break;
	}
}

//====================================================================
//�p�r�@�F�L�[�𗣂����u�Ԃ̔���
//�߂�l�F���ɍl�����Ȃ��Ă悢
//�g�����Fif���ň͂��Ă�����Ƃ�낵������
//���ӓ_�F�X�e�B�b�N�͑Ή����Ă���܂���(�ǂ����Ă��K�v�Ȃ�������܂�)
//        �g���K�[�͂����ɗ������肷��Ɣ������Ȃ����Ƃ�����܂�
//=====================================================================
int InputReleaseKey(PadButton key)
{
	switch (key)
	{
	case PadButton::A_BUTTON:
		return RELEASE & XINPUT_GAMEPAD_A;
		break;
	case PadButton::B_BUTTON:
		return RELEASE & XINPUT_GAMEPAD_B;
		break;
	case PadButton::X_BUTTON:
		return RELEASE & XINPUT_GAMEPAD_X;
		break;
	case PadButton::Y_BUTTON:
		return RELEASE & XINPUT_GAMEPAD_Y;
		break;
	case PadButton::START_BUTTON:
		return RELEASE & XINPUT_GAMEPAD_START;
		break;
	case PadButton::BACK_BUTTON:
		return RELEASE & XINPUT_GAMEPAD_BACK;
		break;
	case PadButton::LEFT_SHOULDER:
		return RELEASE & XINPUT_GAMEPAD_LEFT_SHOULDER;
		break;
	case PadButton::RIGHT_SHOULDER:
		return RELEASE & XINPUT_GAMEPAD_RIGHT_SHOULDER;
		break;
	case PadButton::UP_BUTTON:
		return RELEASE & XINPUT_GAMEPAD_DPAD_UP;
		break;
	case PadButton::DOWN_BUTTON:
		return RELEASE & XINPUT_GAMEPAD_DPAD_DOWN;
		break;
	case PadButton::LEFT_BUTTON:
		return RELEASE & XINPUT_GAMEPAD_DPAD_LEFT;
		break;
	case PadButton::RIGHT_BUTTON:
		return RELEASE & XINPUT_GAMEPAD_DPAD_RIGHT;
		break;
	case PadButton::LEFT_TRIGGER:
		state.Gamepad.wButtons |= TriggerChangeButtonReleaseVer(
			state.Gamepad.bLeftTrigger, XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
		return TRIGGER & state.Gamepad.wButtons && state.Gamepad.bLeftTrigger > 0.0f;
		break;
	case PadButton::RIGHT_TRIGGER:
		state.Gamepad.wButtons |= TriggerChangeButtonReleaseVer(
			state.Gamepad.bRightTrigger, XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
		return TRIGGER & state.Gamepad.wButtons && state.Gamepad.bRightTrigger > 0.0f;
		break;
	default:
		return 0;
		break;
	}
}

//====================================================================
//�p�r�@�F�X�e�B�b�N���X�������̒l��Ԃ�(Press)
//�߂�l�FXMFLOAT2�^
//�g�����F�v���C���[�̍��W�X�V�Ȃǂɂ������߂ł�
//���ӓ_�F-1.0�`1.0�̒l�ŕԂ��܂�
//=====================================================================
DirectX::XMFLOAT2 GetPressStick()
{
	DirectX::XMFLOAT2 normalized(0, 0);
	float normalizedMagnitude = 0;              //0.0�`1.0�ɕ␳�����傫���x�N�g�����i�[����ϐ�

	if(InputPressKey(PadButton::LEFT_STICK))
	{
		float LX = state.Gamepad.sThumbLX;    //���X�e�B�b�N��X��
		float LY = state.Gamepad.sThumbLY;    //���X�e�B�b�N��Y��

		float magnitudeL = sqrt(LX * LX + LY * LY);  //�X�e�B�b�N���X���������̃x�N�g���̑傫��

		normalized.x = LX / magnitudeL;        //�X�e�B�b�N���X���������̃x�N�g������(X��)
		normalized.y = LY / magnitudeL;        //�X�e�B�b�N���X���������̃x�N�g������(Y��)

		//�X�e�B�b�N���~�`�̃f�b�h�]�[���̊O���ɂ��邩(�X�e�B�b�N���X�����Ƃ��̍ő�l)
		if (magnitudeL > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)     //�X�e�B�b�N�̂�����(���ۂɔ�������܂ł̗]���݂����Ȃ���)�𒴂�����
		{
			if (magnitudeL > 32767) magnitudeL = 32767;           //�X�e�B�b�N�̃x�N�g���̑傫�����ő�l�𒴂����Ƃ��ő�l�ɕ␳

			magnitudeL -= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;    //���ۂɎg���镪�̃x�N�g���̑傫�����v�Z

			normalizedMagnitude = magnitudeL / (32767 - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);     //�g���Ă���x�N�g���̑傫����0.0�`1.0�̒l�ɕ␳
		}
		else
		{
			magnitudeL = 0.0f;
			normalizedMagnitude = 0.0f;
		}
	}
	else if(InputPressKey(PadButton::RIGHT_STICK))
	{
		 float RX = state.Gamepad.sThumbRX;
		float RY = state.Gamepad.sThumbRY;

		float magnitudeR = sqrt(RX * RX + RY * RY);

		normalized.x = RX / magnitudeR;
		normalized.y = RY / magnitudeR;

		//�X�e�B�b�N���~�`�̃f�b�h�]�[���̊O���ɂ��邩(�X�e�B�b�N���X�����Ƃ��̍ő�l)
		if (magnitudeR > RightStickDeadZone)
		{
			if (magnitudeR > 32767) magnitudeR = 32767;

			magnitudeR -= RightStickDeadZone;

			normalizedMagnitude = magnitudeR / (32767 - RightStickDeadZone);
		}
		else
		{
			magnitudeR = 0.0f;
			normalizedMagnitude = 0.0f;
		}
	}

	normalized.x *= normalizedMagnitude;
	normalized.y *= normalizedMagnitude;
	return normalized;
}

//====================================================================
//�p�r�@�F�E�X�e�B�b�N���X�������̒l��Ԃ�(Press)
//�߂�l�FXMFLOAT2�^
//�g�����F�v���C���[�̍��W�X�V�Ȃǂɂ������߂ł�
//���ӓ_�F-1.0�`1.0�̒l�ŕԂ��܂�
//=====================================================================
const DirectX::XMFLOAT2& GetPressRightStick()
{
	return NowRightStickValue;
}

//====================================================================
//�p�r�@�F���X�e�B�b�N���X�������̒l��Ԃ�(Press)
//�߂�l�FXMFLOAT2�^
//�g�����F�v���C���[�̍��W�X�V�Ȃǂɂ������߂ł�
//���ӓ_�F-1.0�`1.0�̒l�ŕԂ��܂�
//=====================================================================
const DirectX::XMFLOAT2& GetPressLeftStick()
{
	return NowLeftStickValue;
}

//====================================================================
//�p�r�@�F�E�X�e�B�b�N���X�������̒l��ݒ�
//�߂�l�F�Ȃ�
// ���ӓ_�F�ĂԂ�
//=====================================================================
void SetPressRightStick()
{
	DirectX::XMFLOAT2 normalized(0, 0);
	float normalizedMagnitude = 0;              //0.0�`1.0�ɕ␳�����傫���x�N�g�����i�[����ϐ�

	if (InputPressKey(PadButton::RIGHT_STICK))
	{
		float RX = state.Gamepad.sThumbRX;
		float RY = state.Gamepad.sThumbRY;

		float magnitudeR = sqrt(RX * RX + RY * RY);

		normalized.x = RX / magnitudeR;
		normalized.y = RY / magnitudeR;

		//�X�e�B�b�N���~�`�̃f�b�h�]�[���̊O���ɂ��邩(�X�e�B�b�N���X�����Ƃ��̍ő�l)
		if (magnitudeR > RightStickDeadZone)
		{
			if (magnitudeR > 32767) magnitudeR = 32767;

			magnitudeR -= RightStickDeadZone;

			normalizedMagnitude = magnitudeR / (32767 - RightStickDeadZone);
		}
		else
		{
			magnitudeR = 0.0f;
			normalizedMagnitude = 0.0f;
		}
	}

	normalized.x *= normalizedMagnitude;
	normalized.y *= normalizedMagnitude;
	NowRightStickValue = normalized;
}

//====================================================================
//�p�r�@�F���X�e�B�b�N���X�������̒l��ݒ�
//�߂�l�F�Ȃ�
//���ӓ_�F�ĂԂ�
//=====================================================================
void SetPressLeftStick()
{
	DirectX::XMFLOAT2 normalized(0, 0);
	float normalizedMagnitude = 0;              //0.0�`1.0�ɕ␳�����傫���x�N�g�����i�[����ϐ�

	if (InputPressKey(PadButton::LEFT_STICK))
	{
		float LX = state.Gamepad.sThumbLX;    //���X�e�B�b�N��X��
		float LY = state.Gamepad.sThumbLY;    //���X�e�B�b�N��Y��

		float magnitudeL = sqrt(LX * LX + LY * LY);  //�X�e�B�b�N���X���������̃x�N�g���̑傫��

		normalized.x = LX / magnitudeL;        //�X�e�B�b�N���X���������̃x�N�g������(X��)
		normalized.y = LY / magnitudeL;        //�X�e�B�b�N���X���������̃x�N�g������(Y��)

		//�X�e�B�b�N���~�`�̃f�b�h�]�[���̊O���ɂ��邩(�X�e�B�b�N���X�����Ƃ��̍ő�l)
		if (magnitudeL > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)     //�X�e�B�b�N�̂�����(���ۂɔ�������܂ł̗]���݂����Ȃ���)�𒴂�����
		{
			if (magnitudeL > 32767) magnitudeL = 32767;           //�X�e�B�b�N�̃x�N�g���̑傫�����ő�l�𒴂����Ƃ��ő�l�ɕ␳

			magnitudeL -= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;    //���ۂɎg���镪�̃x�N�g���̑傫�����v�Z

			normalizedMagnitude = magnitudeL / (32767 - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);     //�g���Ă���x�N�g���̑傫����0.0�`1.0�̒l�ɕ␳
		}
		else
		{
			magnitudeL = 0.0f;
			normalizedMagnitude = 0.0f;
		}
	}

	normalized.x *= normalizedMagnitude;
	normalized.y *= normalizedMagnitude;
	NowLeftStickValue = normalized;
}

bool GetRightSmash(float SmashValue)
{
	return (RightStickMoveValue > SmashValue);
}

bool GetLeftSmash(float SmashValue)
{
	return (LeftStickMoveValue > SmashValue);
}

//====================================================================
//�p�r�@�F�g���K�[���ǂꂭ�炢�����Ă��邩�l��Ԃ�(Press)
//�߂�l�Ffloat�^
//�g�����F���߂̓���Ȃǂɂ������߂ł�
//���ӓ_�F0�`255�̒l�ŕԂ��܂�
//=====================================================================
float GetPressTrigger()
{
	float normalized = 0;
	float normalizedMagnitude = 0;

	if (InputPressKey(PadButton::LEFT_TRIGGER))
	{
		float LT = state.Gamepad.bLeftTrigger;
		if (LT > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		{
			if (LT > 255) LT = 255;
			LT -= XINPUT_GAMEPAD_TRIGGER_THRESHOLD;
			normalizedMagnitude = LT / (255 - XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
		}
		else if(LT < 30)
		{
			LT = 0.0f;
			normalizedMagnitude = 0.0f;
		}
		normalized = LT;
	}
	else if (InputPressKey(PadButton::RIGHT_TRIGGER))
	{
		float RT = state.Gamepad.bRightTrigger;
		if (RT > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		{
			if (RT > 255) RT = 255;
			RT -= XINPUT_GAMEPAD_TRIGGER_THRESHOLD;
			normalizedMagnitude = RT / (255 - XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
		}
		else if(RT < 30)
		{
			RT = 0.0f;
			normalizedMagnitude = 0.0f;
		}
		normalized = RT;
	}
	normalized *= normalizedMagnitude;
	return normalized;
}

//====================================================================
//�p�r�@�F�X�e�B�b�N���X�����u�Ԃ̒l��Ԃ�(Trigger)
//�߂�l�FXMFLOAT2�^
//�g�����F���ɂȂ�
//���ӓ_�F�g���ƃX�e�B�b�N�̓��͂��ςȊ����ɂȂ�܂�
//        (���݌����������I���o���邾��GetPressStick()�ő�p���܂��傤)
//=====================================================================
DirectX::XMFLOAT2 GetTriggerStick()
{
	DirectX::XMFLOAT2 Clone(0.0f, 0.0f);

	if (InputTriggerKey(PadButton::LEFT_STICK))
	{
		Clone = GetPressStick();
	}
	else if (InputTriggerKey(PadButton::RIGHT_STICK))
	{
		Clone = GetPressStick();
	}

	return Clone;
}

//====================================================================
//�p�r�@�F�g���K�[���������u�Ԃ̒l��Ԃ�(Trigger)
//�߂�l�Ffloat�^
//�g�����F���ɂȂ�
//���ӓ_�F��{�I�ɂ��̊֐��͎g�����Ȃ��ł�(�������������u�Ԃ�����Ԃ�l������������)
//=====================================================================
float GetTriggerTrigger()
{
	float Clone = 0.0f;
	if (InputTriggerKey(PadButton::LEFT_TRIGGER))
	{
		Clone = GetPressTrigger();
	}
	if (InputTriggerKey(PadButton::RIGHT_TRIGGER))
	{
		Clone = GetPressTrigger();
	}
	return Clone;
}

//====================================================================
//�p�r�@�F�����{�^�����������Ƃ���������(�g���K�[)
//�߂�l�Fint�^
//�g�����Fif���ň͂��Ă�����΂悢����
//���ӓ_�F�Ȃ�
//=====================================================================
int AllKeyTrigger()
{
	if (InputTriggerKey(PadButton::A_BUTTON) || InputTriggerKey(PadButton::B_BUTTON) || InputTriggerKey(PadButton::X_BUTTON) || InputTriggerKey(PadButton::Y_BUTTON)
		|| InputTriggerKey(PadButton::START_BUTTON) || InputTriggerKey(PadButton::BACK_BUTTON) || InputTriggerKey(PadButton::LEFT_SHOULDER)
		|| InputTriggerKey(PadButton::RIGHT_SHOULDER) || InputTriggerKey(PadButton::UP_BUTTON) || InputTriggerKey(PadButton::DOWN_BUTTON)
		|| InputTriggerKey(PadButton::LEFT_BUTTON) || InputTriggerKey(PadButton::RIGHT_BUTTON) || InputTriggerKey(PadButton::LEFT_TRIGGER)
		|| InputTriggerKey(PadButton::RIGHT_TRIGGER) || InputTriggerKey(PadButton::LEFT_STICK) || InputTriggerKey(PadButton::RIGHT_STICK))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//====================================================================
//�p�r�@�FABXY�̃{�^���̂ݎg��
//�߂�l�Fint�^
//�g�����Fif���ň͂��Ă�����΂悢����(����̑���Ŏg���邩������Ȃ�)
//���ӓ_�F�Ȃ�
//=====================================================================
int AlfaKeyTrigger()
{
	if (InputTriggerKey(PadButton::A_BUTTON) || InputTriggerKey(PadButton::B_BUTTON)
		|| InputTriggerKey(PadButton::X_BUTTON) || InputTriggerKey(PadButton::Y_BUTTON))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//====================================================================
//�p�r�@�FABXY�̃{�^���̂ݎg��(Press)
//�߂�l�Fint�^
//�g�����Fif���ň͂��Ă�����΂悢����(����̑���Ŏg���邩������Ȃ�)
//���ӓ_�F�Ȃ�
//=====================================================================
int AlfaKeyPress()
{
	if (InputPressKey(PadButton::A_BUTTON) || InputPressKey(PadButton::B_BUTTON)
		|| InputPressKey(PadButton::X_BUTTON) || InputPressKey(PadButton::Y_BUTTON))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//====================================================================
//�p�r�@�F�X�e�B�b�N���͂��L�[���͂ɕϊ�
//�߂�l�FWORD�^
//�g�����F�L�[���͂ɂ���Trigger�Ȃǂ̔���Ɏg��
//���ӓ_�F��{�I�ɕʂ̊֐����Ŏg���p�ł�(�g��Ȃ��ł�������)
//=====================================================================
WORD StickChangeButton(SHORT StickX, SHORT StickY, SHORT DeadZone)
{
	WORD wButton = 0;
	if (StickY >= DeadZone)
	{
		wButton |= XINPUT_GAMEPAD_DPAD_UP;
	}
	else if(StickY <= -DeadZone)
	{
		wButton |= XINPUT_GAMEPAD_DPAD_DOWN;
	}
	if (StickX <= -DeadZone)
	{
		wButton |= XINPUT_GAMEPAD_DPAD_LEFT;
	}
	else if (StickX >= DeadZone)
	{
		wButton |= XINPUT_GAMEPAD_DPAD_RIGHT;
	}

	return wButton;
}

//====================================================================
//�p�r�@�F�g���K�[���͂��L�[���͂ɕϊ�
//�߂�l�FWORD�^
//�g�����F�L�[���͂ɂ���Trigger�Ȃǂ̔���Ɏg��
//���ӓ_�F��{�I�ɕʂ̊֐����Ŏg���p�ł�(�g��Ȃ��ł�������)
//=====================================================================
WORD TriggerChangeButton(BYTE Trigger, BYTE DeadZone)
{
	WORD wButton = 0;

	if (Trigger >= DeadZone)
	{
		wButton |= XINPUT_GAMEPAD_DPAD_UP;
	}	

	return wButton;
}

//====================================================================
//�p�r�@�F�g���K�[���͂��L�[���͂ɕϊ�(ReleaseVer)
//�߂�l�FWORD�^
//�g�����F�L�[���͂ɂ���Release�Ȃǂ̔���Ɏg��
//���ӓ_�F��{�I�ɕʂ̊֐����Ŏg���p�ł�(�g��Ȃ��ł�������)
//=====================================================================
WORD TriggerChangeButtonReleaseVer(BYTE Trigger, BYTE DeadZone)
{
	WORD wButton = 0;

	if (Trigger <= DeadZone)
	{
		wButton |= XINPUT_GAMEPAD_DPAD_UP;
		wButton |= XINPUT_GAMEPAD_DPAD_DOWN;
		wButton |= XINPUT_GAMEPAD_DPAD_LEFT;
		wButton |= XINPUT_GAMEPAD_DPAD_RIGHT;
		wButton |= XINPUT_GAMEPAD_START;
		wButton |= XINPUT_GAMEPAD_BACK;
		wButton |= XINPUT_GAMEPAD_LEFT_SHOULDER;
		wButton |= XINPUT_GAMEPAD_RIGHT_SHOULDER;
		wButton |= XINPUT_GAMEPAD_A;
		wButton |= XINPUT_GAMEPAD_B;
		wButton |= XINPUT_GAMEPAD_X;
		wButton |= XINPUT_GAMEPAD_Y;
	}

	return wButton;
}

//====================================================================
//�p�r�@�F�o�C�u���[�V�����̋��x��ύX
//�߂�l�F�Ȃ�
//�g�����F�����ɍ��̃��[�^�[�ƉE�̃��[�^�[�̋��x��ݒ�
//���ӓ_�F���x��0�`65535�̊ԂŐݒ肵�Ă�������(���E�̋��x�͈���Ă����v�ł�)
//        �f�t�H���g�͍�(0),�E(0)�ɐݒ肵�Ă���܂��B
//=====================================================================
void SetPowerVibration(WORD LEFT, WORD RIGHT)  //���x0�`65535
{
	vibration.wLeftMotorSpeed = LEFT;
	vibration.wRightMotorSpeed = RIGHT;
}

//====================================================================
//�p�r�@�F�o�C�u���[�V����������
//�߂�l�F�Ȃ�
//�g�����F�o�C�u���[�V�������������Ƃ���ŌĂ�
//���ӓ_�FSetPowerVibration(����)�ŋ��x��ݒ肵�Ă���łȂ��Ɨh��Ȃ�
//�@�@�@�@�����ɐU�����������t���[���������
//=====================================================================
void SetVibration(int num)
{
	XInputSetState(0, &vibration);
	Vibtime = num;
	Stop = true;
}

//====================================================================
//�p�r�@�F�o�C�u���[�V�����������I�ɔ���(�~�߂�֐����ĂԂ܂�)
//�߂�l�F�Ȃ�
//�g�����F�o�C�u���[�V�������������Ƃ���ŌĂ�
//���ӓ_�FSetPowerVibration(����)�ŋ��x��ݒ肵�Ă���łȂ��Ɨh��Ȃ�
//=====================================================================
void MoveVibration()
{
	XInputSetState(0, &vibration);
}

//====================================================================
//�p�r�@�F�o�C�u���[�V�����������I�~�߂�
//�߂�l�F�Ȃ�
//�g�����F�o�C�u���[�V���������I�����������Ƃ���ŌĂ�
//���ӓ_�F�Ȃ�
//=====================================================================
void StopVibration()
{
	SetPowerVibration(0, 0);
	XInputSetState(0, &vibration);
}
