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

	void SetDefaultCollider() override;

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
	void BlowAwayInit() override;	//������΂���鎞�̏�����
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
	void DeadInit() override;		//���񂾂Ƃ��̏�����
	void DeadUninit() override;		//���񂾂Ƃ��̏I������
	void DeadUpdate() override;		//���񂾂Ƃ��̃A�b�v�f�[�g
	//====================================================================
	void RespawnInit() override;	//���X�|�[�������Ƃ��̏�����
	void RespawnUninit() override;	//���X�|�[�������Ƃ��̏I������
	void RespawnUpdate() override;	//���X�|�[�������Ƃ��̃A�b�v�f�[�g
	//====================================================================
	void GameOverInit() override;	//���X�|�[�������Ƃ��̏�����
	void GameOverUninit() override;	//���X�|�[�������Ƃ��̏I������
	void GameOverUpdate() override;	//���X�|�[�������Ƃ��̃A�b�v�f�[�g
	//====================================================================

	//==========================================================================
	//�U���̃A�b�v�f�[�g
	//=====================================================
	void Attack11_Init() override;									//��1
	void Attack11_Update() override;
	void Attack11_Uninit() override;
	void Attack11_Hit(Character* HitCharacter) override;			
	//=====================================================
	void Attack12_Init() override;									//��2
	void Attack12_Update() override;
	void Attack12_Uninit() override;
	void Attack12_Hit(Character* HitCharacter) override;
	//=====================================================
	void Attack13_Init() override;									//��3
	void Attack13_Update() override;
	void Attack13_Uninit() override;
	void Attack13_Hit(Character* HitCharacter) override;
	//=====================================================
	void AttackS2_Init() override;									//����
	void AttackS2_Update() override;
	void AttackS2_Uninit() override;
	void AttackS2_Hit(Character* HitCharacter) override;
	//=====================================================
	void AttackSD_Init() override;								//���X�}�b�V��
	void AttackSD_Update() override;
	void AttackSD_Uninit() override;
	void AttackSD_Hit(Character* HitCharacter) override;
	//=====================================================
	void AttackAirN_Init() override;									//��N
	void AttackAirN_Update() override;
	void AttackAirN_Uninit() override;
	void AttackAirN_Hit(Character* HitCharacter) override;		
	//=====================================================


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