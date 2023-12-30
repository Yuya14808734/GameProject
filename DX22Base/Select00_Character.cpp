#include "Select00_Character.h"

SelectCharacter::SelectCharacter()
{
	m_isDecided = false;
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

}

void SelectCharacter::SetController(PlayerController* Controller)
{
	m_pSelectController = Controller;
}

void SelectCharacter::ChangeNowController(PlayerController* Controller)
{
	//前のフレームでコントローラーがなく、今のフレームでコントローラーが接続された場合
	if (m_pSelectController == nullptr && Controller != nullptr)
	{
		//初期化をする
		m_SelectState = SelectCharacter::SELECTSTATE::SELECT;
		m_isDecided = false;
	}

	m_pSelectController = Controller;
}

void SelectCharacter::SetNowCharacter(CHARACTER NowCharacter)
{
	m_NowSelectCharacter = static_cast<int>(NowCharacter);
	m_NowSelectCharacter =	//キャラクターが異常な数字の場合、正常な数字にする
		m_NowSelectCharacter % static_cast<int>(SelectCharacter::CHARACTER::MAX);
}

bool SelectCharacter::IsDecided()
{
	return m_isDecided;
}

SelectCharacter::SELECTSTATE SelectCharacter::GetState()
{
	return m_SelectState;
}

void SelectCharacter::SelectUpdate()
{
	//右を押したら
	if (m_pSelectController->GetRightArrow())
	{
		m_NowSelectCharacter++;
		m_NowSelectCharacter =
			m_NowSelectCharacter % static_cast<int>(SelectCharacter::CHARACTER::MAX);

		m_SelectState = SelectCharacter::SELECTSTATE::ANIMATION;
	}

	//左を押したら
	if (m_pSelectController->GetLeftArrow())
	{
		m_NowSelectCharacter--;

		m_NowSelectCharacter =
			(m_NowSelectCharacter + static_cast<int>(SelectCharacter::CHARACTER::MAX))
			% static_cast<int>(SelectCharacter::CHARACTER::MAX);

		m_SelectState = SelectCharacter::SELECTSTATE::ANIMATION;
	}

	//決定ボタンを押したら
	if (m_pSelectController->IsReturn())
	{
		m_isDecided = true;
		m_SelectState = SelectCharacter::SELECTSTATE::DECIDED;
	}
}

void SelectCharacter::AnimationUpdate()
{

}

void SelectCharacter::DecidedUpdate()
{
	//決定ボタンを押したら
	if (m_pSelectController->IsBack())
	{
		m_isDecided = false;
		m_SelectState = SelectCharacter::SELECTSTATE::SELECT;
	}
}
