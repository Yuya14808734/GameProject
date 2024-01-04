#pragma once
#include "Scene.h"
#include <vector>
#include "Character_Base.h"
#include "Stage_Base.h"
#include "Camera01_Game.h"
#include "Select01_CharacterList.h"
#include "GameUI00_StartCount.h"


class SceneGame : public CScene
{
private:
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
	std::vector<Character*>& GetCharacter();
	Stage* GetStage();

private:
	Character* CreateCharacter(int Num);										//�L�����N�^�[�̍쐬(�ԍ���)	
	Character* CreateCharacter(SelectCharacterList::CHARACTER CharacterNum);	//�L�����N�^�[�̍쐬(ENUM��)

	void UpdateGameStart();														//�Q�[���J�n���̃A�b�v�f�[�g
	void UpdateGamePlay();														//�Q�[�����̃A�b�v�f�[�g
	void UpdateGameEnd();														//�Q�[���I�����̃A�b�v�f�[�g
	void DrawGameStart();														//�Q�[���J�n���̃A�b�v�f�[�g
	void DrawGamePlay();														//�Q�[�����̃A�b�v�f�[�g
	void DrawGameEnd();															//�Q�[���I�����̃A�b�v�f�[�g

	void Collision_Player_Player();												//�����蔻��(�v���C���[�ƃv���C���[)
	void Collision_Player_Stage();												//�����蔻��(�v���C���[�ƃX�e�[�W)
	void Collision_Attack_Player();												//�����蔻��(�v���C���[�U��)
	

private:
	GAMESTATE m_GameState = GAMESTATE::MAX;
	std::vector<Character*> m_Characters;	//�L�����N�^�[�̏��
	Stage* m_pStage;						//�X�e�[�W�̏��
	CameraGame* m_pGameCamera = nullptr;		//�Q�[���̃J����

	GameStartCountUI m_GameStartCountUI;
	int m_GameStartFrameCount = 0;

};