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

	//キャラクターを出すボードのUI
	//ボードの色を変更
	m_CharacterUnconnectBoardImage.SetTexture("Assets/UI/SelectBoard_Black.png");
	m_CharacterUnconnectBoardImage.m_size = 
		m_CharacterConnectBoardImage.m_size =
		CVector2(640.0f, 451.0f) * 0.45f;

	//フレームの読み込み
	m_FrameImage.SetTexture("Assets/UI/SelectFrame.png");
	m_FrameImage.m_size = CVector2(276.0f, 400.0f) * 0.8f;

	//なにもつながっていない時のフォントの読み込み
	m_NoConnectText.SetTexture("Assets/UI/NoConnectText.png");
	m_NoConnectText.m_size = CVector2(400.0f, 221.0f) * 0.5f;

	//繋がった時に表示する画像
	m_ConnectedText.SetTexture("Assets/UI/ConnectedText.png");
	m_ConnectedText.m_size = CVector2(400.0f, 261.0f) * 0.5f;

	//接続解除した時の画像
	m_DisConnectedText.SetTexture("Assets/UI/DisConnectText.png");
	m_DisConnectedText.m_size = CVector2(400.0f, 261.0f) * 0.5f;

	//なにもつながっていない時の背景の読み込み
	m_ConnectBackGround_Image.SetTexture("Assets/UI/BackGround_Image.png");
	m_ConnectBackGround_Image.m_size = CVector2(400.0f, 261.0f) * 0.45f;
	
	//繋がった時の背景の読み込み
	m_ConnectBackGround_Frame.SetTexture("Assets/UI/BackGround_Frame.png");
	m_ConnectBackGround_Frame.m_size = CVector2(400.0f, 261.0f) * 0.5f;

	//コントローラーの画像
	m_ControllerImage.m_pos = CVector2(-70.0f, -50.0f);
	m_ControllerImage.m_size = CVector2(128.0f, 128.0f) * 0.5f;

	//Selectedと選んだ時に映す画像
	m_SelectedImage.SetTexture("Assets/UI/SelectedImage.png");
	m_SelectedImage.m_pos = CVector2(59.0f, 20.0f);
	m_SelectedImage.m_size = CVector2(131.0f, 131.0f);


}

SelectCharacter::~SelectCharacter()
{

}

void SelectCharacter::Update()
{
	//コントローラーを設定していない場合
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
	//=========<後ろの背景にあるボードの描画>========================================================
	if (m_pSelectController == nullptr)
	{
		m_CharacterUnconnectBoardImage.Draw();
	}
	else
	{
		m_CharacterConnectBoardImage.Draw();
	}
	//===============================================================================================

	//=========<コントローラーが接続されていない場合(コントローラーが接続されるまで待つ)>===========
	if (m_pSelectController == nullptr)
	{
		//接続が解除された時に表示する
		if (m_VisibleDisconnectTextCount < m_VisibleDisConnectTextTime)
		{
			m_VisibleDisconnectTextCount += 1.0f / 60.0f;
			m_ConnectBackGround_Frame.m_color = DirectX::XMFLOAT4(1.0f, 127.0f / 255.0f, 80.0f / 255.0f, 1.0f);
			m_ConnectBackGround_Frame.Draw();	//背景のフレーム描画
			m_ConnectBackGround_Image.Draw();	//背景の本体描画
			m_DisConnectedText.Draw();			//テキストの描画
		}
		else//接続されていない時に描画
		{
			m_ConnectBackGround_Frame.m_color = DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
			m_ConnectBackGround_Frame.Draw();	//背景のフレーム描画
			m_ConnectBackGround_Image.Draw();	//背景の本体描画
			m_NoConnectText.m_color.w = (sinf((m_AlphaCount / 1.0f) * 3.14f) + 1.0f) / 2.0f;
			m_NoConnectText.Draw();			//テキストの描画
		}
		return;
	}
	//================================================================================================

	//=========<キャラクターのアイコンを描画>=========================================================
	Image2D* pIconImage = &SelectCharacterList::GetCharacterIconImageList()[m_NowSelectCharacter];
	pIconImage->m_BasePos = m_BasePos;
	pIconImage->m_pos = CVector2(59.0f, 20.0f);
	pIconImage->m_size = CVector2(131.0f, 131.0f);
	pIconImage->Draw();
	//===============================================================================================

	//=========<選んでいたらキャラクターのアイコンを隠す文字の描画>==================================
	if(m_isDecided)
	{
		m_SelectedImage.Draw();
	}
	//===============================================================================================

	//=========<接続したコントローラーによって画像を変える>==========================================
	m_ControllerImage.Draw();
	//===============================================================================================

	//=========<繋がった時に文字を描画>==============================================================
	if (m_VisibleConnectTextCount < m_VisibleConnectTextTime)
	{
		m_VisibleConnectTextCount += 1.0f / 60.0f;
		m_ConnectBackGround_Frame.m_color = DirectX::XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f);
		m_ConnectBackGround_Frame.Draw();	//背景のフレーム描画
		m_ConnectBackGround_Image.Draw();	//背景の本体描画
		m_ConnectedText.Draw();
	}
	//===============================================================================================
}

void SelectCharacter::StandCharacterDraw()
{
	//=========<選べるキャラクターのリストが設定されていない場合(SceneのInitで設定して下さい)>===========
	if (m_pCharacterList == nullptr)
	{
		return;
	}
	//===============================================================================================

	//=========<コントローラーが接続されていない場合(コントローラーが接続されるまで待つ)>===========
	if (m_pSelectController == nullptr)
	{
		return;
	}
	//================================================================================================

	//=========<コントローラーが接続されていない場合(コントローラーが接続されるまで待つ)>===========
	Image2D* StandCharacterImage = &m_pCharacterList->GetCharacterStandImageList()[m_NowSelectCharacter];
	StandCharacterImage->m_pos = m_StandCharacterImageDrawPos_LerpNow;
	StandCharacterImage->m_size = CVector2(474.0f, 697.0f);
	StandCharacterImage->m_color.w = m_StandCharacterDrawAlpha;
	StandCharacterImage->Draw();
	//================================================================================================
}

void SelectCharacter::SelectFrameDraw()
{
	//=========<選べるキャラクターのリストが設定されていない場合(SceneのInitで設定して下さい)>===========
	if (m_pCharacterList == nullptr)
	{
		return;
	}
	//===============================================================================================

	//=========<コントローラーが接続されていない場合(コントローラーが接続されるまで待つ)>===========
	if (m_pSelectController == nullptr)
	{
		return;
	}
	//================================================================================================

	//=========<枠の表示>=============================================================================
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
	//今のフレームでコントローラーが変更された場合
	if (m_pSelectController != Controller)
	{
		//コントローラーの上書き
		m_pSelectController = Controller;

		//=========<コントローラーが接続解除の場合>===========
		if (Controller == nullptr)
		{
			SetBoardColor(SelectCharacter::BOARDCOLOR::BLACK);
			m_ControllerImage.ReleaseTexture();
			m_VisibleDisconnectTextCount = 0.0f;
			m_VisibleConnectTextCount = m_VisibleConnectTextTime;
			return;
		}

		//=========<コントローラーが接続されている>===========
		
		//初期化をする
		m_SelectState = SelectCharacter::SELECTSTATE::SELECT;
		m_isDecided = false;
		m_VisibleDisconnectTextCount = m_VisibleDisConnectTextTime;
		m_VisibleConnectTextCount = 0.0f;
		StandCharacterChangeInit();

		//次のコントローラーのタイプ
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
	//各イメージのベース位置を変更
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
	//右を押したら
	if (m_pSelectController->GetTriggerRightArrow())
	{
		m_NowSelectCharacter++;
		m_NowSelectCharacter =
			m_NowSelectCharacter % static_cast<int>(SelectCharacterList::CHARACTER::MAX);

		StandCharacterChangeInit();
	}

	//左を押したら
	if (m_pSelectController->GetTriggerLeftArrow())
	{
		m_NowSelectCharacter--;

		m_NowSelectCharacter =
			(m_NowSelectCharacter + static_cast<int>(SelectCharacterList::CHARACTER::MAX))
			% static_cast<int>(SelectCharacterList::CHARACTER::MAX);

		StandCharacterChangeInit();
	}

	//決定ボタンを押したら
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
	//補間が終わっていたら
	if (m_StandCharacterImageDrawPos_LerpCount > m_StandCharacterLerpTime)
	{
		m_StandCharacterImageDrawPos_LerpNow = m_StandCharacterImageDrawPos_LerpEnd;
		m_StandCharacterDrawAlpha = 1.0f;
		return;
	}

	//補間時間を更新
	m_StandCharacterImageDrawPos_LerpCount = m_StandCharacterImageDrawPos_LerpCount + (1.0f / 60.0f);

	m_StandCharacterImageDrawPos_LerpNow =
		(m_StandCharacterImageDrawPos_LerpEnd - m_StandCharacterImageDrawPos_LerpStart) *	//最初の位置から最後の位置へのベクトルを求める
		(m_StandCharacterImageDrawPos_LerpCount / m_StandCharacterLerpTime) + m_StandCharacterImageDrawPos_LerpStart;		//上で求めたベクトルを過ぎた時間分、掛ける
																		//それに最初の位置を足す

	m_StandCharacterDrawAlpha = m_StandCharacterImageDrawPos_LerpCount / m_StandCharacterLerpTime;
}

void SelectCharacter::DecidedUpdate()
{
	//決定ボタンを押したら
	if (m_pSelectController->IsPressBack())
	{
		m_isDecided = false;
		m_SelectState = SelectCharacter::SELECTSTATE::SELECT;
	}
}