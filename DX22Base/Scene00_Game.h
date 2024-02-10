#pragma once
#include "Scene.h"
#include <vector>
#include "Character_Base.h"
#include "Stage_Base.h"
#include "Camera01_Game.h"
#include "Camera04_Light.h"
#include "Select01_CharacterList.h"
#include "GameUI00_StartCount.h"
#include "GameUI01_GameEndText.h"
#include "GameUI02_StockCount.h"
#include "Image3D.h"
#include "StatePattern.h"
#include "Player_Controller.h"
#include "EffectBase.h"
#include "Light.h"
#include "TextureClass.h"
#include "ConstantBuffer.h"

class SceneGame : public CScene
{
public:
	enum class GAMESTATE : int
	{
		GAMELOAD = 0,
		GAMESTART,
		GAMEPLAY,
		GAMEEND,
		GAMEDISCONNECTCONTROLLER,
		MAX,
	};

public:
	SceneGame() {};
	~SceneGame() override {};

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	State* SetNextState(GAMESTATE State);		//�X�e�[�g�̐ݒ�
	void ChangeNextState();						//�X�e�[�g�̎擾
private:
	Character* CreateCharacter(int Num);										//�L�����N�^�[�̍쐬(�ԍ���)	
	Character* CreateCharacter(SelectCharacterList::CHARACTER CharacterNum);	//�L�����N�^�[�̍쐬(ENUM��)
	void EffectUpdate();
	void EffectDraw();
	void EffectRelease();
public:
	void LightCameraDraw();
	void EffectPause();

private:
	GAMESTATE m_GameState = GAMESTATE::MAX;		//���̃X�e�[�g
	StateContext m_GameSceneStateContext;		//�X�e�[�g�R���e�N�X�g
	std::vector<Character*> m_Characters;		//�L�����N�^�[�̏��
	Stage* m_pStage;							//�X�e�[�W�̏��
	CameraGame* m_pGameCamera = nullptr;		//�Q�[���̃J����
	CameraLight* m_pLightCamera = nullptr;		//���C�g�̃J����
	std::vector<EffectBase*> m_Effects;			//�G�t�F�N�g�̎��
	Image3D m_BackGround;

	GameStartCountUI m_GameStartCountUI;
	GameEndText m_GameEndTextUI;
	StockCountUI m_StockCountUI;

	PlayerController* m_pFirstController = nullptr;
	PlayerController* m_pSecondController = nullptr;

	bool m_isDisConnectController = false;
	
	LightObject m_Light;
	RenderTarget* m_pShadowMapRenderTarget = nullptr;
	DepthStencil* m_pShadowMapDepthStencil = nullptr;
	ConstantBuffer m_LightLVPMatrixBuffer;


public:
	StateContext* GetStateContext()		
	{return &m_GameSceneStateContext;}

	std::vector<Character*>& GetCharacter()
	{ return m_Characters;}

	Stage* GetStage()
	{ return m_pStage;}

	std::vector<EffectBase*>* GetEffectVector() 
	{ return &m_Effects; }

};