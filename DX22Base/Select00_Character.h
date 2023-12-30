#pragma once
#include "Player_Controller.h"

class SelectCharacter
{
public:
	enum class CHARACTER : int
	{
		UNITYCHAN = 0,
		MAX
	};

	enum class SELECTSTATE : int
	{
		SELECT = 0,	//�I��ł���
		ANIMATION,	//UI�������Ă���
		DECIDED,	//���肵�Ă���
		MAX
	};

public:
	SelectCharacter();
	~SelectCharacter();
	void Update();
	void Draw();
	void SetController(PlayerController* Controller);			//�R���g���[���[��ݒ�
	void ChangeNowController(PlayerController* Controller);		//�R���g���[���[��ύX
	void SetNowCharacter(CHARACTER NowCharacter);				//�L�����N�^�[��ݒ�
	bool IsDecided();											//�L�����N�^�[�����肵����
	SelectCharacter::SELECTSTATE GetState();

private:
	void SelectUpdate();		//�I��ł���Ƃ��̃A�b�v�f�[�g
	void AnimationUpdate();		//�A�j���[�V�����̃A�b�v�f�[�g
	void DecidedUpdate();		//���肵����̃A�b�v�f�[�g

private:
	SELECTSTATE m_SelectState = SELECTSTATE::MAX;
	PlayerController* m_pSelectController = nullptr;
	int m_NowSelectCharacter = 0;
	bool m_isDecided = false;
};