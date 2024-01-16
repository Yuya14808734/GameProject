#pragma once
#include "Scene.h"
#include <vector>
#include "Character_Base.h"
#include "Stage_Base.h"
#include "Camera01_Game.h"
#include "Select01_CharacterList.h"
#include "GameUI00_StartCount.h"
#include "GameUI01_GameEndText.h"
#include "Image3D.h"
#include "StatePattern.h"
#include "Player_Controller.h"


class SceneGame : public CScene
{
public:
	enum class GAMESTATE : int
	{
		GAMESTART = 0,
		GAMEPLAY,
		GAMEEND,
		MAX,
	};

public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	State* SetNextState(GAMESTATE State);		//�X�e�[�g�̐ݒ�
	void ChangeNextState();						//�X�e�[�g�̎擾
private:
	Character* CreateCharacter(int Num);										//�L�����N�^�[�̍쐬(�ԍ���)	
	Character* CreateCharacter(SelectCharacterList::CHARACTER CharacterNum);	//�L�����N�^�[�̍쐬(ENUM��)

private:
	GAMESTATE m_GameState = GAMESTATE::MAX;
	StateContext m_GameSceneStateContext;
	std::vector<Character*> m_Characters;	//�L�����N�^�[�̏��
	Stage* m_pStage;						//�X�e�[�W�̏��
	CameraGame* m_pGameCamera = nullptr;		//�Q�[���̃J����
	Image3D m_BackGround;

	GameStartCountUI m_GameStartCountUI;
	//int m_GameStartFrameCount = 0;
	GameEndText m_GameEndTextUI;

	PlayerController* m_pFirstController = nullptr;
	PlayerController* m_pSecondController = nullptr;


public:
	std::vector<Character*>& GetCharacter()
	{ return m_Characters;}

	Stage* GetStage()
	{ return m_pStage;}

};