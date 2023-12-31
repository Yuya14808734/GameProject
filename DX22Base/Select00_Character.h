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
	static void AlphaUpdate();

private:
	static float m_AlphaCount;

public:
	SelectCharacter();												//�R���X�g���N�^
	~SelectCharacter();												//�f�X�g���N�^
	void Update();													//�X�V
	void Draw();													//�`��
	void SetController(PlayerController* Controller);				//�R���g���[���[��ݒ�
	void ChangeNowController(PlayerController* Controller);			//�R���g���[���[��ύX
	void SetNowCharacter(SelectCharacterList::CHARACTER NowCharacter);	//�L�����N�^�[��ݒ�
	bool IsDecided();												//�L�����N�^�[�����肵����
	SelectCharacter::SELECTSTATE GetState();
	void SetPos(const CVector3& pos);
	const CVector3& GetPos() const;
	void SetCharacterList(std::array<Image2D, static_cast<int>(SelectCharacterList::CHARACTER::MAX)>* pCharacterImageList);
																	//�I���ł���L�����N�^�[�̉摜�z���ݒ�
	void SetCharacterIconList(std::array<Image2D, static_cast<int>(SelectCharacterList::CHARACTER::MAX)>* pCharacterIconImageList);
																	//�I���ł���L�����N�^�[�̉摜�z���ݒ�

private:
	void SelectUpdate();											//�I��ł���Ƃ��̃A�b�v�f�[�g
	void AnimationUpdate();											//�A�j���[�V�����̃A�b�v�f�[�g
	void DecidedUpdate();											//���肵����̃A�b�v�f�[�g

private:
	SELECTSTATE m_SelectState = SELECTSTATE::MAX;					//�I��ł��鍡�̏��
	CVector3 m_BasePos;												//�`�悷�钆�S�ɂȂ�ʒu
	PlayerController* m_pSelectController = nullptr;				//�R���g���[���[���
	int m_NowSelectCharacter = 0;									//�I��ł���L�����N�^�[�̔ԍ�
	bool m_isDecided = false;										//�L�����N�^�[��I��������
	Image2D m_NoConnectBackGround;									//�����q�����Ă��Ȃ��ꍇ�̔w�i
	Image2D m_NoConnectText;										//�����q�����Ă��Ȃ��ꍇ�̕���
	Image2D m_FrameImage;											//�L�����N�^�[���͂��t���[��
	Image2D m_ControllerImage;										//�R���g���[���[�̉摜
	std::array<Image2D, static_cast<int>(SelectCharacterList::CHARACTER::MAX)>*
		m_pCharacterIconImageList = nullptr;						//�I�ׂ�L�����N�^�[�̃A�C�R��
	std::array<Image2D, static_cast<int>(SelectCharacterList::CHARACTER::MAX)>*
		m_pCharacterImageList = nullptr;							//�I�ׂ�L�����N�^�[�̑S�̐}
};