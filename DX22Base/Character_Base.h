#pragma once

#include <DirectXMath.h>
class Attack;

class Character
{
public:
	void Character_Init();		//�L�����N�^�[�̏�����
	void Character_Uninit();	//�L�����N�^�[�̏I������
	void Character_Update();	//�L�����N�^�[�̍X�V
	void Character_Draw();		//�L�����N�^�[�̕`��

protected:

	//======================================================
	//��������͂قړ����ɂȂ邽�ߏ�̊֐����g�����ƂɂȂ肻��

	virtual void Init();		//�p����̏�����
	virtual void Uninit();		//�p����̏I������
	virtual void Update();		//�p����̍X�V
	virtual void Draw();		//�p����̕`��


protected:
	DirectX::XMFLOAT3 m_pos;
	DirectX::XMFLOAT3 m_size;



	Attack* m_pNowAttack = nullptr;	//���s���Ă���U��
	

};