#pragma once
#include <vector>
#include "Collider.h"
#include "Calculation.h"
#include "ModelDrawer.h"

class Stage
{
public:
	void Stage_Init();		//�L�����N�^�[�̏�����
	void Stage_Uninit();	//�L�����N�^�[�̏I������
	void Stage_Update();	//�L�����N�^�[�̍X�V
	void Stage_Draw();		//�L�����N�^�[�̕`��
	void StageColliderDraw();	//�X�e�[�W�̃R���C�_�[�̕`��
	std::vector<BoxCollider>* GetStageCollider() const;
	std::vector<CVector3>* GetCharacterStartPos() const;
	float GetDeadLineRightX();
	float GetDeadLineLeftX();
	float GetDeadLineTopY();
	float GetDeadLineBottomY();
	CVector3 AddRespawn();			//���X�|�[�����Ă��鐔�𑝂₷�B�߂�l�͐V�������X�|�[���ʒu
	void MinaRespawn();

protected:

	//======================================================
	//��������͂قړ����ɂȂ邽�ߏ�̊֐����g�����ƂɂȂ肻��

	virtual void Init() {};		//�p����̏�����
	virtual void Uninit() {};	//�p����̏I������
	virtual void Update() {}; 	//�p����̍X�V
	virtual void Draw() {};		//�p����̕`��


protected:
	std::vector<BoxCollider> m_StageCollider;
	std::vector<CVector3> m_CharacterStartPos;
	std::vector<ModelDrawer> m_ModelDrawer;
	float m_CameraNearZ = 0.0f;
	float m_CameraFarZ	= 0.0f;

	//�v���C���[�����̈ʒu�𒴂���Ǝ���
	float m_DeadLineRightX	= 0.0f;
	float m_DeadLineLeftX	= 0.0f;
	float m_DeadLineTopY	= 0.0f;
	float m_DeadLineBottomY = 0.0f;

	//�v���C���[�̃��X�|�[���ʒu
	CVector3 m_BaseRespawnPos;
	float m_RespawnDistance;
	int m_UseRespawnNum = 0;




};