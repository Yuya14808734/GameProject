#include "Select00_Character.h"

float SelectCharacter::m_AlphaCount = 0.0f;

void SelectCharacter::AlphaUpdate()
{
	m_AlphaCount += 1.0f / 60.0f;

	while(m_AlphaCount > 100.0f)
	{
		m_AlphaCount -= 100.0f;
	}
}

SelectCharacter::SelectCharacter()
{
	m_isDecided				= false;
	m_NowSelectCharacter	= static_cast<int>(SelectCharacterList::CHARACTER::MAX);
	m_VisibleConnectTextCount		= m_VisibleConnectTextTime;
	m_VisibleDisconnectTextCount	= m_VisibleDisConnectTextTime;

	//�L�����N�^�[���o���{�[�h��UI
	//�{�[�h�̐F��ύX
	m_CharacterUnconnectBoardImage.SetTexture("Assets/UI/SelectBoard_Black.png");
	m_CharacterUnconnectBoardImage.m_size = 
		m_CharacterConnectBoardImage.m_size =
		CVector2(640.0f, 451.0f) * 0.45f;

	//�t���[���̓ǂݍ���
	m_FrameImage.SetTexture("Assets/UI/SelectFrame.png");
	m_FrameImage.m_size = CVector2(276.0f, 400.0f) * 0.8f;

	//�Ȃɂ��Ȃ����Ă��Ȃ����̃t�H���g�̓ǂݍ���
	m_NoConnectText.SetTexture("Assets/UI/NoConnectText.png");
	m_NoConnectText.m_size = CVector2(400.0f, 221.0f) * 0.5f;

	//�q���������ɕ\������摜
	m_ConnectedText.SetTexture("Assets/UI/ConnectedText.png");
	m_ConnectedText.m_size = CVector2(400.0f, 261.0f) * 0.5f;

	//�ڑ������������̉摜
	m_DisConnectedText.SetTexture("Assets/UI/DisConnectText.png");
	m_DisConnectedText.m_size = CVector2(400.0f, 261.0f) * 0.5f;

	//�Ȃɂ��Ȃ����Ă��Ȃ����̔w�i�̓ǂݍ���
	m_ConnectBackGround_Image.SetTexture("Assets/UI/BackGround_Image.png");
	m_ConnectBackGround_Image.m_size = CVector2(400.0f, 261.0f) * 0.45f;
	
	//�q���������̔w�i�̓ǂݍ���
	m_ConnectBackGround_Frame.SetTexture("Assets/UI/BackGround_Frame.png");
	m_ConnectBackGround_Frame.m_size = CVector2(400.0f, 261.0f) * 0.5f;

	//�R���g���[���[�̉摜
	m_ControllerImage.m_pos = CVector2(-70.0f, -50.0f);
	m_ControllerImage.m_size = CVector2(128.0f, 128.0f) * 0.5f;

	//Selected�ƑI�񂾎��ɉf���摜
	m_SelectedImage.SetTexture("Assets/UI/SelectedImage.png");
	m_SelectedImage.m_pos = CVector2(59.0f, 20.0f);
	m_SelectedImage.m_size = CVector2(131.0f, 131.0f);


}

SelectCharacter::~SelectCharacter()
{

}

void SelectCharacter::Update()
{
	//�R���g���[���[��ݒ肵�Ă��Ȃ��ꍇ
	if (m_pSelectController == nullptr)
	{
		return;
	}

	switch (m_SelectState)
	{
	case SelectCharacter::SELECTSTATE::SELECT:
		SelectUpdate();
		break;
	case SelectCharacter::SELECTSTATE::DECIDED:
		DecidedUpdate();
		break;
	}

	StandCharacterChangeUpdate();
}

void SelectCharacter::BoardDraw()
{
	//=========<���̔w�i�ɂ���{�[�h�̕`��>========================================================
	if (m_pSelectController == nullptr)
	{
		m_CharacterUnconnectBoardImage.Draw();
	}
	else
	{
		m_CharacterConnectBoardImage.Draw();
	}
	//===============================================================================================

	//=========<�R���g���[���[���ڑ�����Ă��Ȃ��ꍇ(�R���g���[���[���ڑ������܂ő҂�)>===========
	if (m_pSelectController == nullptr)
	{
		//�ڑ����������ꂽ���ɕ\������
		if (m_VisibleDisconnectTextCount < m_VisibleDisConnectTextTime)
		{
			m_VisibleDisconnectTextCount += 1.0f / 60.0f;
			m_ConnectBackGround_Frame.m_color = DirectX::XMFLOAT4(1.0f, 127.0f / 255.0f, 80.0f / 255.0f, 1.0f);
			m_ConnectBackGround_Frame.Draw();	//�w�i�̃t���[���`��
			m_ConnectBackGround_Image.Draw();	//�w�i�̖{�̕`��
			m_DisConnectedText.Draw();			//�e�L�X�g�̕`��
		}
		else//�ڑ�����Ă��Ȃ����ɕ`��
		{
			m_ConnectBackGround_Frame.m_color = DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
			m_ConnectBackGround_Frame.Draw();	//�w�i�̃t���[���`��
			m_ConnectBackGround_Image.Draw();	//�w�i�̖{�̕`��
			m_NoConnectText.m_color.w = (sinf((m_AlphaCount / 1.0f) * 3.14f) + 1.0f) / 2.0f;
			m_NoConnectText.Draw();			//�e�L�X�g�̕`��
		}
		return;
	}
	//================================================================================================

	//=========<�L�����N�^�[�̃A�C�R����`��>=========================================================
	Image2D* pIconImage = &SelectCharacterList::GetCharacterIconImageList()[m_NowSelectCharacter];
	pIconImage->m_BasePos = m_BasePos;
	pIconImage->m_pos = CVector2(59.0f, 20.0f);
	pIconImage->m_size = CVector2(131.0f, 131.0f);
	pIconImage->Draw();
	//===============================================================================================

	//=========<�I��ł�����L�����N�^�[�̃A�C�R�����B�������̕`��>==================================
	if(m_isDecided)
	{
		m_SelectedImage.Draw();
	}
	//===============================================================================================

	//=========<�ڑ������R���g���[���[�ɂ���ĉ摜��ς���>==========================================
	m_ControllerImage.Draw();
	//===============================================================================================

	//=========<�q���������ɕ�����`��>==============================================================
	if (m_VisibleConnectTextCount < m_VisibleConnectTextTime)
	{
		m_VisibleConnectTextCount += 1.0f / 60.0f;
		m_ConnectBackGround_Frame.m_color = DirectX::XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f);
		m_ConnectBackGround_Frame.Draw();	//�w�i�̃t���[���`��
		m_ConnectBackGround_Image.Draw();	//�w�i�̖{�̕`��
		m_ConnectedText.Draw();
	}
	//===============================================================================================
}

void SelectCharacter::StandCharacterDraw()
{
	//=========<�I�ׂ�L�����N�^�[�̃��X�g���ݒ肳��Ă��Ȃ��ꍇ(Scene��Init�Őݒ肵�ĉ�����)>===========
	if (m_pCharacterList == nullptr)
	{
		return;
	}
	//===============================================================================================

	//=========<�R���g���[���[���ڑ�����Ă��Ȃ��ꍇ(�R���g���[���[���ڑ������܂ő҂�)>===========
	if (m_pSelectController == nullptr)
	{
		return;
	}
	//================================================================================================

	//=========<�R���g���[���[���ڑ�����Ă��Ȃ��ꍇ(�R���g���[���[���ڑ������܂ő҂�)>===========
	Image2D* StandCharacterImage = &m_pCharacterList->GetCharacterStandImageList()[m_NowSelectCharacter];
	StandCharacterImage->m_pos = m_StandCharacterImageDrawPos_LerpNow;
	StandCharacterImage->m_size = CVector2(474.0f, 697.0f);
	StandCharacterImage->m_color.w = m_StandCharacterDrawAlpha;
	StandCharacterImage->Draw();
	//================================================================================================
}

void SelectCharacter::SelectFrameDraw()
{
	//=========<�I�ׂ�L�����N�^�[�̃��X�g���ݒ肳��Ă��Ȃ��ꍇ(Scene��Init�Őݒ肵�ĉ�����)>===========
	if (m_pCharacterList == nullptr)
	{
		return;
	}
	//===============================================================================================

	//=========<�R���g���[���[���ڑ�����Ă��Ȃ��ꍇ(�R���g���[���[���ڑ������܂ő҂�)>===========
	if (m_pSelectController == nullptr)
	{
		return;
	}
	//================================================================================================

	//=========<�g�̕\��>=============================================================================
	m_FrameImage.m_pos = m_pCharacterList->GetIconPos()[m_NowSelectCharacter];
	m_FrameImage.m_size = m_pCharacterList->GetIconSize();
	m_FrameImage.Draw();
	//===============================================================================================
}

void SelectCharacter::SetBoardColor(BOARDCOLOR color)
{
	switch (color)
	{
	case SelectCharacter::BOARDCOLOR::RED:
		m_CharacterConnectBoardImage.SetTexture("Assets/UI/SelectBoard_Red.png");
		break;
	case SelectCharacter::BOARDCOLOR::BLUE:
		m_CharacterConnectBoardImage.SetTexture("Assets/UI/SelectBoard_Blue.png");
		break;
	}
}

void SelectCharacter::SetController(PlayerController* Controller)
{
	m_pSelectController = Controller;
}

void SelectCharacter::ChangeNowController(PlayerController* Controller)
{
	//���̃t���[���ŃR���g���[���[���ύX���ꂽ�ꍇ
	if (m_pSelectController != Controller)
	{
		//�R���g���[���[�̏㏑��
		m_pSelectController = Controller;

		//=========<�R���g���[���[���ڑ������̏ꍇ>===========
		if (Controller == nullptr)
		{
			SetBoardColor(SelectCharacter::BOARDCOLOR::BLACK);
			m_ControllerImage.ReleaseTexture();
			m_VisibleDisconnectTextCount = 0.0f;
			m_VisibleConnectTextCount = m_VisibleConnectTextTime;
			return;
		}

		//=========<�R���g���[���[���ڑ�����Ă���>===========
		
		//������������
		m_SelectState = SelectCharacter::SELECTSTATE::SELECT;
		m_isDecided = false;
		m_VisibleDisconnectTextCount = m_VisibleDisConnectTextTime;
		m_VisibleConnectTextCount = 0.0f;
		StandCharacterChangeInit();

		//���̃R���g���[���[�̃^�C�v
		switch (Controller->GetControllerType())
		{
		case PlayerController::PLAYCONTROLLERTYPE::GAMEPAD:
			m_ControllerImage.SetTexture("Assets/UI/PadImage.png");
			m_ControllerImage.m_pos = CVector3(-73.0f, -42.0f, 0.0f);
			m_ControllerImage.m_size = CVector2(81.0f, 81.0f);
			break;
		case PlayerController::PLAYCONTROLLERTYPE::KEYBOARD:
			m_ControllerImage.SetTexture("Assets/UI/KeyboardImage.png");
			m_ControllerImage.m_pos = CVector3(-73.0f, -40.0f, 0.0f);
			m_ControllerImage.m_size = CVector2(80.0f, 80.0f);
			break;
		}
	}
}

void SelectCharacter::SetNowCharacter(SelectCharacterList::CHARACTER NowCharacter)
{
	switch (NowCharacter)
	{
	case SelectCharacterList::CHARACTER::NONE:
	case SelectCharacterList::CHARACTER::MAX:
		m_NowSelectCharacter = static_cast<int>(
			SelectCharacterList::CHARACTER::UNITYCHAN);
		break;
	default:
		m_NowSelectCharacter = static_cast<int>(NowCharacter);
		break;
	}
}

bool SelectCharacter::IsDecided()
{
	return m_isDecided;
}

SelectCharacter::SELECTSTATE SelectCharacter::GetState()
{
	return m_SelectState;
}

SelectCharacterList::CHARACTER SelectCharacter::GetSelectCharacter()
{
	return static_cast<SelectCharacterList::CHARACTER>(m_NowSelectCharacter);
}

void SelectCharacter::SetBoardPos(const CVector3& pos)
{
	//�e�C���[�W�̃x�[�X�ʒu��ύX
	m_CharacterUnconnectBoardImage.m_BasePos = 
	m_CharacterConnectBoardImage.m_BasePos =
	m_ConnectBackGround_Image.m_BasePos =
	m_ConnectBackGround_Frame.m_BasePos =
	m_NoConnectText.m_BasePos =
	m_ConnectedText.m_BasePos =
	m_DisConnectedText.m_BasePos =
	m_ControllerImage.m_BasePos =
	m_SelectedImage.m_BasePos =
	m_BasePos = pos;
}

const CVector3& SelectCharacter::GetBoardPos() const
{
	return m_BasePos;
}

void SelectCharacter::SetCharacterList(SelectCharacterList* pCharacterList)
{
	m_pCharacterList = pCharacterList;
}

void SelectCharacter::SetLerpStandCharacterDrawPos(const CVector3& StartPos, const CVector3& EndPos)
{
	m_StandCharacterImageDrawPos_LerpStart = StartPos;
	m_StandCharacterImageDrawPos_LerpEnd = EndPos;
}

void SelectCharacter::SelectUpdate()
{
	//�E����������
	if (m_pSelectController->GetTriggerRightArrow())
	{
		m_NowSelectCharacter++;
		m_NowSelectCharacter =
			m_NowSelectCharacter % static_cast<int>(SelectCharacterList::CHARACTER::MAX);

		StandCharacterChangeInit();
	}

	//������������
	if (m_pSelectController->GetTriggerLeftArrow())
	{
		m_NowSelectCharacter--;

		m_NowSelectCharacter =
			(m_NowSelectCharacter + static_cast<int>(SelectCharacterList::CHARACTER::MAX))
			% static_cast<int>(SelectCharacterList::CHARACTER::MAX);

		StandCharacterChangeInit();
	}

	//����{�^������������
	if (m_pSelectController->IsTriggerReturn())
	{
		m_pSelectController->UnTriggerNowFrame();
		m_isDecided = true;
		m_SelectState = SelectCharacter::SELECTSTATE::DECIDED;
	}
}

void SelectCharacter::StandCharacterChangeInit()
{
	m_StandCharacterImageDrawPos_LerpCount = 0.0f;
}

void SelectCharacter::StandCharacterChangeUpdate()
{
	//��Ԃ��I����Ă�����
	if (m_StandCharacterImageDrawPos_LerpCount > m_StandCharacterLerpTime)
	{
		m_StandCharacterImageDrawPos_LerpNow = m_StandCharacterImageDrawPos_LerpEnd;
		m_StandCharacterDrawAlpha = 1.0f;
		return;
	}

	//��Ԏ��Ԃ��X�V
	m_StandCharacterImageDrawPos_LerpCount = m_StandCharacterImageDrawPos_LerpCount + (1.0f / 60.0f);

	m_StandCharacterImageDrawPos_LerpNow =
		(m_StandCharacterImageDrawPos_LerpEnd - m_StandCharacterImageDrawPos_LerpStart) *	//�ŏ��̈ʒu����Ō�̈ʒu�ւ̃x�N�g�������߂�
		(m_StandCharacterImageDrawPos_LerpCount / m_StandCharacterLerpTime) + m_StandCharacterImageDrawPos_LerpStart;		//��ŋ��߂��x�N�g�����߂������ԕ��A�|����
																		//����ɍŏ��̈ʒu�𑫂�

	m_StandCharacterDrawAlpha = m_StandCharacterImageDrawPos_LerpCount / m_StandCharacterLerpTime;
}

void SelectCharacter::DecidedUpdate()
{
	//����{�^������������
	if (m_pSelectController->IsPressBack())
	{
		m_isDecided = false;
		m_SelectState = SelectCharacter::SELECTSTATE::SELECT;
	}
}