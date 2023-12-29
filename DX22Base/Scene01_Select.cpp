#include "Scene01_Select.h"
#include "CameraManager.h"
#include <array>

PlayerController* SceneSelect::m_pFirstPlayerController = nullptr;
PlayerController* SceneSelect::m_pSecondPlayerController = nullptr;

void SceneSelect::Init()
{
	
}

void SceneSelect::Uninit()
{
	
}

void SceneSelect::Update()
{
	//1P��2P�̐U�蕪��
	//�{�^�������������ꂽ����1P,2P�Ƃ��Ă���
	if (m_pFirstPlayerController == nullptr)
	{
		std::array<PlayerController,5>& ControllerArray = PlayerController::GetPlayerControllers();

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
	else if(m_pSecondPlayerController == nullptr)
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

	//�L�����N�^�[�̐ݒ�


	//����{�^���������ꂽ��Q�[���Ɉړ�

}

void SceneSelect::Draw()
{
	
}
