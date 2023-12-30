#include "Scene01_Select.h"
#include "CameraManager.h"
#include <array>

PlayerController* SceneSelect::m_pFirstPlayerController = nullptr;
PlayerController* SceneSelect::m_pSecondPlayerController = nullptr;

SelectCharacter::CHARACTER SceneSelect::m_FirstPlayerCharacter = SelectCharacter::CHARACTER::MAX;
SelectCharacter::CHARACTER SceneSelect::m_SecondPlayerCharacter = SelectCharacter::CHARACTER::MAX;

PlayerController* SceneSelect::GetFirstPlayerController()
{
	return m_pFirstPlayerController;
}

PlayerController* SceneSelect::GetSecondPlayerController()
{
	return m_pSecondPlayerController;
}

SelectCharacter::CHARACTER SceneSelect::GetFirstPlayerCharacter()
{
	return m_FirstPlayerCharacter;
}

SelectCharacter::CHARACTER SceneSelect::GetSecondPlayerCharacter()
{
	return m_SecondPlayerCharacter;
}

void SceneSelect::Init()
{
	m_SelectFirstCharacter.SetNowCharacter(m_FirstPlayerCharacter);
	m_SelectFirstCharacter.SetController(m_pFirstPlayerController);
	m_SelectSecondCharacter.SetNowCharacter(m_SecondPlayerCharacter);
	m_SelectSecondCharacter.SetController(m_pSecondPlayerController);
}

void SceneSelect::Uninit()
{
	
}

void SceneSelect::Update()
{
	//コントローラーが切れていたら情報を削除する
	ControllerDisconnect();

	//コントローラーをつなげる
	ControllerConnect();

	//コントローラーを解除する
	ControllerRelease();

	//キャラクターの設定

	//コントローラーが変更されているか確認
	m_SelectFirstCharacter.ChangeNowController(m_pFirstPlayerController);
	m_SelectSecondCharacter.ChangeNowController(m_pSecondPlayerController);

	//キャラクターセレクトのアップデート
	m_SelectFirstCharacter.Update();
	m_SelectSecondCharacter.Update();

	//二人がキャラクターを選んでいたら
	if (m_SelectFirstCharacter.IsDecided() && m_SelectSecondCharacter.IsDecided())
	{
		//決定ボタンを押せるようになる
	}
}

void SceneSelect::Draw()
{
	m_SelectFirstCharacter.Draw();
	m_SelectSecondCharacter.Draw();
}

void SceneSelect::ControllerConnect()
{
	//1Pと2Pの振り分け
	//ボタンが何か押された順に1P,2Pとしていく
	if (m_pFirstPlayerController == nullptr)
	{
		std::array<PlayerController, 5>& ControllerArray = PlayerController::GetPlayerControllers();

		for (PlayerController& Controller : ControllerArray)
		{
			if (!Controller.IsConnect())
			{
				continue;
			}

			if (Controller.IsReturn())
			{
				m_pFirstPlayerController = &Controller;
				break;
			}
		}
	}
	else if (m_pSecondPlayerController == nullptr)
	{
		std::array<PlayerController, 5>& ControllerArray = PlayerController::GetPlayerControllers();

		for (PlayerController& Controller : ControllerArray)
		{
			if (!Controller.IsConnect())
			{
				continue;
			}

			if (Controller.IsReturn())
			{
				m_pSecondPlayerController = &Controller;
				break;
			}
		}
	}
}

void SceneSelect::ControllerDisconnect()
{
	//コントローラーの情報が入っていたら
	if (m_pFirstPlayerController != nullptr)
	{
		//今持っているコントローラーが繋がっているか
		if(!m_pFirstPlayerController->IsConnect())
		{
			m_pFirstPlayerController = nullptr;
		}
	}

	//コントローラーの情報が入っていたら
	if (m_pSecondPlayerController != nullptr)
	{
		//今持っているコントローラーが繋がっているか
		if(!m_pSecondPlayerController->IsConnect())
		{
			m_pSecondPlayerController = nullptr;
		}
	}
}

void SceneSelect::ControllerRelease()
{
	//コントローラーの情報が入っていたら
	if (m_pFirstPlayerController != nullptr)
	{
		//キャラクターを選んでいる場合
		if (m_SelectFirstCharacter.GetState() == SelectCharacter::SELECTSTATE::SELECT)
		{
			//Bを押すとコントローラーの登録を外す
			if (!m_pFirstPlayerController->IsBack())
			{
				m_pFirstPlayerController = nullptr;
			}
		}
	}

	//コントローラーの情報が入っていたら
	if (m_pSecondPlayerController != nullptr)
	{
		//キャラクターを選んでいる場合
		if (m_SelectSecondCharacter.GetState() == SelectCharacter::SELECTSTATE::SELECT)
		{
			//Bを押すとコントローラーの登録を外す
			if (!m_pSecondPlayerController->IsBack())
			{
				m_pSecondPlayerController = nullptr;
			}
		}
	}
}
