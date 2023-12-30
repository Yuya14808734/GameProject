#pragma once
#include "Player_Controller.h"
#include "Image2D.h"
#include "Select01_CharacterList.h"

class SelectCharacter
{
public:
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
	void SetController(PlayerController* Controller);				//�R���g���[���[��ݒ�
	void ChangeNowController(PlayerController* Controller);			//�R���g���[���[��ύX
	void SetNowCharacter(SelectCharacterList::CHARACTER NowCharacter);	//�L�����N�^�[��ݒ�
	bool IsDecided();												//�L�����N�^�[�����肵����
	SelectCharacter::SELECTSTATE GetState();
	void SetCharacterList(std::array<Image2D, static_cast<int>(SelectCharacterList::CHARACTER::MAX)>* pCharacterImageList);
																	//�I���ł���L�����N�^�[�̉摜�z���ݒ�

private:
	void SelectUpdate();											//�I��ł���Ƃ��̃A�b�v�f�[�g
	void AnimationUpdate();											//�A�j���[�V�����̃A�b�v�f�[�g
	void DecidedUpdate();											//���肵����̃A�b�v�f�[�g

private:
	SELECTSTATE m_SelectState = SELECTSTATE::MAX;					//�I��ł��鍡�̏��
	PlayerController* m_pSelectController = nullptr;				//�R���g���[���[���
	int m_NowSelectCharacter = 0;									//�I��ł���L�����N�^�[�̔ԍ�
	bool m_isDecided = false;										//�L�����N�^�[��I��������
	Image2D m_FrameImage;											//�L�����N�^�[���͂��t���[��
	std::array<Image2D, static_cast<int>(SelectCharacterList::CHARACTER::MAX)>*
		m_pCharacterImageList = nullptr;
};