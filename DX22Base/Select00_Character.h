#pragma once
#include "Player_Controller.h"
#include "Image2D.h"
#include "Select01_CharacterList.h"
#include <array>

class SelectCharacter
{
public:
	enum class SELECTSTATE : int
	{
		SELECT = 0,	//�I��ł���
		DECIDED,	//���肵�Ă���
		MAX
	};

	enum class BOARDCOLOR
	{
		BLACK = 0,
		RED,
		BLUE,
		MAX
	};

private:
	static constexpr float m_StandCharacterLerpTime = 0.5f;
	static constexpr float m_VisibleConnectTextTime = 0.5f;
	static constexpr float m_VisibleDisConnectTextTime = 0.5f;

public:
	static void AlphaUpdate();

private:
	static float m_AlphaCount;

public:
	SelectCharacter();												//�R���X�g���N�^
	~SelectCharacter();												//�f�X�g���N�^
	void Update();													//�X�V
	void BoardDraw();												//�`��
	void StandCharacterDraw();										//�����Ă���L�����N�^�[�̕`��
	void SelectFrameDraw();											//�I��ł���L�����N�^�[���������t���[���̕`��
	void SetBoardColor(BOARDCOLOR color);							//�{�[�h�̃J���[��ݒ�
	void SetController(PlayerController* Controller);				//�R���g���[���[��ݒ�
	void ChangeNowController(PlayerController* Controller);			//�R���g���[���[��ύX
	void SetNowCharacter(SelectCharacterList::CHARACTER NowCharacter);	//�L�����N�^�[��ݒ�
	bool IsDecided();												//�L�����N�^�[�����肵����
	SelectCharacter::SELECTSTATE GetState();
	SelectCharacterList::CHARACTER GetSelectCharacter();
	void SetBoardPos(const CVector3& pos);
	const CVector3& GetBoardPos() const;
	void SetCharacterList(SelectCharacterList* pCharacterList);
	void SetLerpStandCharacterDrawPos(const CVector3& StartPos, const CVector3& EndPos);

private:
	void SelectUpdate();											//�I��ł���Ƃ��̃A�b�v�f�[�g
	void DecidedUpdate();											//���肵����̃A�b�v�f�[�g

	void StandCharacterChangeInit();								//�L�����N�^�[�̗����G��\�����邽�߂̏���
	void StandCharacterChangeUpdate();								//�L�����N�^�[�̗����G��\������܂ł̃A�j���[�V����
private:

	//=======<�L�����N�^�[�Z���N�g�̏�ԕϐ�>==============================================================
	int						m_SelectPlayerNumber = 0;					//���������ԖڂɑI��ł��邩
	SELECTSTATE				m_SelectState = SELECTSTATE::MAX;		//�I��ł��鍡�̏��
	int						m_NowSelectCharacter = 0;				//�I��ł���L�����N�^�[�̔ԍ�
	bool					m_isDecided = false;					//�L�����N�^�[��I��������
	//======================================================================================================

	//=======<�R���g���[���[�Ɋւ�����>===================================================================
	PlayerController*		m_pSelectController = nullptr;			//�R���g���[���[���
	//======================================================================================================
	
	//=======<UI�̒��S�ɂȂ�ʒu�̏��>=====================================================================
	CVector3				m_BasePos;								//�{�[�h��L�����N�^�[�̃A�C�R���Ȃǂ̒��S�ɂȂ�ʒu
	//======================================================================================================

	//=======<���̃{�[�h�Ɋւ�����>=====================================================================
	Image2D					m_CharacterBoardImage;					//�L�����N�^�[�Z���N�g�̌��ɂ���{�[�h
	Image2D					m_ControllerImage;						//�R���g���[���[�̉摜
	Image2D					m_SelectedImage;						//�I�΂ꂽ�Ƃ��̉摜
	//======================================================================================================
	
	//=======<�ڑ��Ɋւ�����>=============================================================================
	Image2D					m_ConnectedText;						//�q�������Ƃ��̏ꍇ�̕��͉摜
	Image2D					m_NoConnectText;						//�����q�����Ă��Ȃ��ꍇ�̕��͉摜
	Image2D					m_DisConnectedText;						//�ڑ��������ꂽ�ꍇ�̕��͉摜
	Image2D					m_ConnectBackGround_Image;				//���͂̌��ɂ���摜
	Image2D					m_ConnectBackGround_Frame;				//���͂̌��ɂ���摜�̘g
	float					m_VisibleConnectTextCount = 0.0f;		//�q����܂�����`�悷�鎞��
	float					m_VisibleDisconnectTextCount = 0.0f;		//��������܂�����`�悷�鎞��
	//======================================================================================================

	//=======<�L�����N�^�[���Z���N�g����Ƃ��Ɋւ�����>===================================================
	Image2D					m_FrameImage;							//�L�����N�^�[���͂��t���[��
	SelectCharacterList*	m_pCharacterList = nullptr;				//�L�����N�^�[���X�g�̃|�C���^
	//======================================================================================================

	//=======<�L�����N�^�[�̗����G��\������Ƃ��Ɏg�����>=================================================
	float					m_StandCharacterImageDrawPos_LerpCount = 0.0f;	//�ǂ̂��炢�ړ�������
	CVector3				m_StandCharacterImageDrawPos_LerpStart;		//�L�����N�^�[�̗����G���ŏ��ɕ\���������ʒu
	CVector3				m_StandCharacterImageDrawPos_LerpEnd;		//�L�����N�^�[�̗����G���Ō�ɕ\���������ʒu
	CVector3				m_StandCharacterImageDrawPos_LerpNow;		//�L�����N�^�[�̗����G�����\�����Ă���ʒu
	float					m_StandCharacterDrawAlpha = 0.0f;			//�L�����N�^�[�̗����G�̓����x
	//======================================================================================================
};