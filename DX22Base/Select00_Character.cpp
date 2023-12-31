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
	m_isDecided = false;

	//フレームの読み込み
	m_FrameImage.SetTexture("Assets/CharacterImage/SelectFrame.png");
	m_FrameImage.m_size = CVector2(276.0f, 400.0f) * 0.8f;

	//なにもつながっていない時のフォントの読み込み
	m_NoConnectText.SetTexture("Assets/UI/NoConnectText.png");
	m_NoConnectText.m_size = CVector2(400.0f, 221.0f) * 0.5f;

	//なにもつながっていない時の背景の読み込み
	m_NoConnectBackGround.SetTexture("Assets/UI/NoConnectBackGround.png");
	m_NoConnectBackGround.m_size = CVector2(400.0f, 261.0f) * 0.5f;

	//繋がった時に何につながったかの画像
	m_ControllerImage.m_pos = CVector2(-120.0f, -60.0f);
	m_ControllerImage.m_size = CVector2(128.0f, 128.0f);

	//選ばれたときに映す画像
	m_SelectedImage.SetTexture("Assets/CharacterImage/SelectedImage.png");
	m_SelectedImage.m_size = CVector2(150.0f, 150.0f);
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
	case SelectCharacter::SELECTSTATE::ANIMATION:
		AnimationUpdate();
		break;
	case SelectCharacter::SELECTSTATE::DECIDED:
		DecidedUpdate();
		break;
	}
}

void SelectCharacter::Draw()
{
	//=========<選べるキャラクターのリストが設定されていない場合(SceneのInitで設定して下さい)>===========
	if (m_pCharacterImageList == nullptr)
	{
		return;
	}

	if (m_pCharacterIconImageList == nullptr)
	{
		return;
	}

	//=========<コントローラーが接続されていない場合(コントローラーが接続されるまで待つ)>===========
	if (m_pSelectController == nullptr)
	{
		m_NoConnectBackGround.Draw();	//背景の描画
		m_NoConnectText.m_color.w = (sinf((m_AlphaCount / 2.0f) * 3.14f) + 1.0f) / 2.0f;
		m_NoConnectText.Draw();			//テキストの描画
		return;
	}

	//=========<枠の表示>===========
	m_FrameImage.m_pos = (*m_pCharacterImageList)[m_NowSelectCharacter].GetPos();
	m_FrameImage.m_size = (*m_pCharacterImageList)[m_NowSelectCharacter].GetSize();
	m_FrameImage.Draw();

	//=========<接続したコントローラーによって画像を変える>===========
	m_ControllerImage.Draw();

	//=========<キャラクターのアイコンを描画>===========
	(*m_pCharacterIconImageList)[m_NowSelectCharacter].m_BasePos = m_BasePos;
	(*m_pCharacterIconImageList)[m_NowSelectCharacter].Draw();

	//=========<選んでいたらキャラクターのアイコンを隠す文字の描画>===========
	if(m_isDecided)
	{
		m_SelectedImage.Draw();
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

		//=========<コントローラーが接続されていなければ>===========
		if (Controller == nullptr)
		{
			m_ControllerImage.ReleaseTexture();
			return;
		}

		//=========<コントローラーが接続されている>===========
		
		//初期化をする
		m_SelectState = SelectCharacter::SELECTSTATE::SELECT;
		m_isDecided = false;

		//次のコントローラーのタイプ
		switch (Controller->GetControllerType())
		{
		case PlayerController::PLAYCONTROLLERTYPE::GAMEPAD:
			m_ControllerImage.SetTexture("Assets/UI/ControllerImage.png");
			break;
		case PlayerController::PLAYCONTROLLERTYPE::KEYBOARD:
			m_ControllerImage.SetTexture("Assets/UI/KeyboardImage.png");
			break;
		}
	}
}

void SelectCharacter::SetNowCharacter(SelectCharacterList::CHARACTER NowCharacter)
{
	m_NowSelectCharacter = static_cast<int>(NowCharacter);
	m_NowSelectCharacter =	//キャラクターが異常な数字の場合、正常な数字にする
		m_NowSelectCharacter % static_cast<int>(SelectCharacterList::CHARACTER::MAX);
}

bool SelectCharacter::IsDecided()
{
	return m_isDecided;
}

SelectCharacter::SELECTSTATE SelectCharacter::GetState()
{
	return m_SelectState;
}

void SelectCharacter::SetPos(const CVector3& pos)
{
	//各イメージのベース位置を変更
	m_NoConnectBackGround.m_BasePos =
	m_NoConnectText.m_BasePos =
	m_ControllerImage.m_BasePos =
	m_SelectedImage.m_BasePos =
	m_BasePos = pos;
}

const CVector3& SelectCharacter::GetPos() const
{
	return m_BasePos;
}

void SelectCharacter::SetCharacterList(std::array<Image2D, static_cast<int>(SelectCharacterList::CHARACTER::MAX)>* pCharacterImageList)
{
	m_pCharacterImageList = pCharacterImageList;
}

void SelectCharacter::SetCharacterIconList(std::array<Image2D, static_cast<int>(SelectCharacterList::CHARACTER::MAX)>* pCharacterIconImageList)
{
	m_pCharacterIconImageList = pCharacterIconImageList;
}

void SelectCharacter::SelectUpdate()
{
	//右を押したら
	if (m_pSelectController->GetTriggerRightArrow())
	{
		m_NowSelectCharacter++;
		m_NowSelectCharacter =
			m_NowSelectCharacter % static_cast<int>(SelectCharacterList::CHARACTER::MAX);

		m_SelectState = SelectCharacter::SELECTSTATE::ANIMATION;
	}

	//左を押したら
	if (m_pSelectController->GetTriggerLeftArrow())
	{
		m_NowSelectCharacter--;

		m_NowSelectCharacter =
			(m_NowSelectCharacter + static_cast<int>(SelectCharacterList::CHARACTER::MAX))
			% static_cast<int>(SelectCharacterList::CHARACTER::MAX);

		m_SelectState = SelectCharacter::SELECTSTATE::ANIMATION;
	}

	//決定ボタンを押したら
	if (m_pSelectController->IsTriggerReturn())
	{
		m_isDecided = true;
		m_SelectState = SelectCharacter::SELECTSTATE::DECIDED;
	}
}

void SelectCharacter::AnimationUpdate()
{
	m_SelectState = SelectCharacter::SELECTSTATE::SELECT;
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