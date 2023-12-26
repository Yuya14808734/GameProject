#pragma once
#include "Character_Base.h"
#include "Effect_Manager.h"
#include "CharacterStateWindow.h"
#include "Timer.h"

class Character_00 : public Character
{
private:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	//==========================================================================
	void IdleInit() override;		//�~�܂��Ă���Ƃ��̏�����
	void IdleUninit() override;		//�~�܂��Ă���Ƃ��̏I������
	void IdleUpdate() override;		//�~�܂��Ă���Ƃ��̃A�b�v�f�[�g
	//==========================================================================
	void WalkInit() override;		//�������̏�����
	void WalkUninit() override;		//�������̏I������
	void WalkUpdate() override;		//�������̃A�b�v�f�[�g
	//==========================================================================
	void DashInit() override;		//����Ƃ��̏�����
	void DashUninit() override;		//����Ƃ��̏I������
	void DashUpdate() override;		//����Ƃ��̃A�b�v�f�[�g
	//==========================================================================
	//void AttackInit() override;		//�U������Ƃ��̏�����
	//void AttackUninit() override;	//�U������Ƃ��̏I������
	//void AttackUpdate() override;	//�U������Ƃ��̃A�b�v�f�[�g
	//==========================================================================
	void BlowAwayInit() override;		//������΂���鎞�̏�����
	void BlowAwayUninit() override;	//������΂��̏I������
	void BlowAwayUpdate() override;	//������΂��̃A�b�v�f�[�g
	//==========================================================================
	void JumpInInit() override;		//�W�����v�n�߂̏�����
	void JumpInUpdate() override;	//�W�����v�n�߂̃A�b�v�f�[�g
	void JumpInUninit() override;	//�W�����v�n�߂̏I������
	//==========================================================================
	void JumpInit() override;		//�W�����v�����Ƃ��̏�����
	void JumpUninit() override;		//�W�����v�����Ƃ��̏I������
	void JumpUpdate() override;		//�W�����v�����Ƃ��̃A�b�v�f�[�g
	//==========================================================================
	void AirMoveInit() override;	//�󒆂ɂ���Ƃ��̏�����
	void AirMoveUninit() override;	//�󒆂ɂ���Ƃ��̏I������
	void AirMoveUpdate() override;	//�����Ă���Ƃ��̃A�b�v�f�[�g
	//==========================================================================
	void FallDownInit() override;
	void FallDownUninit() override;
	void FallDownUpdate() override;
	//==========================================================================
	void DownInit() override;		//�|�ꂽ���̏�����
	void DownUninit() override;		//�|�ꂽ���̏I������
	void DownUpdate() override;		//�|��Ă����Ԃ̃A�b�v�f�[�g
	//==========================================================================
	void WakeUpInit() override;
	void WakeUpUninit() override;
	void WakeUpUpdate() override;
	//==========================================================================
	void LeanBackInit() override;
	void LeanBackUninit() override;
	void LeanBackUpdate() override;
	//==========================================================================	
	void HitStopInit() override;	//�q�b�g�X�g�b�v�̏�����
	void HitStopUninit() override;	//�q�b�g�X�g�b�v�̏I������
	void HitStopUpdate() override;	//�q�b�g�X�g�b�v��Ԃ̃A�b�v�f�[�g

	//==========================================================================
	//�U���̃A�b�v�f�[�g
	//=====================================================
	void Attack11_Init();								//��1
	void Attack11_Update();
	void Attack11_Uninit();
	void Attack11_Hit(Character* HitCharacter);			
	//=====================================================
	void Attack12_Init();								//��2
	void Attack12_Update();
	void Attack12_Uninit();
	void Attack12_Hit(Character* HitCharacter);			
	//=====================================================
	void Attack13_Init();								//��3
	void Attack13_Update();
	void Attack13_Uninit();
	void Attack13_Hit(Character* HitCharacter);			
	//=====================================================
	void AttackS2_Init();									//����
	void AttackS2_Update();
	void AttackS2_Uninit();
	void AttackS2_Hit(Character* HitCharacter);			
	//=====================================================
	void AttackS4_Init() {};								//���X�}�b�V��
	void AttackS4_Update() {};
	void AttackS4_Uninit() {};
	void AttackS4_Hit(Character* HitCharacter) {};
	//=====================================================
	void AttackAirN_Init();								//��N
	void AttackAirN_Update();
	void AttackAirN_Uninit();
	void AttackAirN_Hit(Character* HitCharacter);		
	//=====================================================
	void SpecialN_Init() {};								//�ʏ�K�E�Z
	void SpecialN_Update() {};
	void SpecialN_Uninit() {};
	void SpecialN_Hit(Character* HitCharacter) {};
	//=====================================================
	void SpecialAirN_Init() {};								//�ʏ�K�E�Z(��)
	void SpecialAirN_Update() {};
	void SpecialAirN_Uninit() {};
	void SpecialAirN_Hit(Character* HitCharacter) {};		


	void HitGround() override;
private:

	int m_FrameCount = 0;					//�A�^�b�N�����Ă���Ƃ��Ɏg���J�E���g
	float m_AnimeTime = 0.0f;				//�A�j���[�V�����̃^�C��
	CharacterStateWindow m_stateWindow;		//�L�����N�^�[�̃f�o�b�O�E�B���h�E
	//unsigned int m_FrameCount = 0;
	int m_HitAttackStopCount = 0;			//�q�b�g�X�g�b�v�̃J�E���g
	bool m_PushButton = false;

	//�G�t�F�N�g�̕ϐ�
	Effekseer::Handle m_SwordHandle;
	Effekseer::Handle m_AirNEffect;
};