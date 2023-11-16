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
	std::vector<BoxCollider>* GetStageCollider() const;

protected:

	//======================================================
	//��������͂قړ����ɂȂ邽�ߏ�̊֐����g�����ƂɂȂ肻��

	virtual void Init() {};		//�p����̏�����
	virtual void Uninit() {};	//�p����̏I������
	virtual void Update() {}; 	//�p����̍X�V
	virtual void Draw() {};		//�p����̕`��


protected:
	std::vector<BoxCollider> m_StageCollider;
	ModelDrawer m_ModelDrawer;

};