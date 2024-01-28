#pragma once
#include "Scene.h"
#include "Image2D.h"
#include "StatePattern.h"
#include "VersusCharacterPanelMove.h"
#include "VersusCharacterImageMove.h"
#include "VersusTextAnime.h"
#include "VersusIconAnime.h"

class SceneLoad : public CScene
{
public:
	enum class LOADSTATE : int
	{
		PANELMOVE = 0,		//パネルを動かす
		CHARACTERDRAW,		//キャラクターを描画
		LOAD,				//ロード
		MAX,
	};

public:
	SceneLoad() {}
	~SceneLoad() override {}

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	State* SetNextState(LOADSTATE LoadState);	//ステートの設定
	void ChangeNextState();						//ステートの取得

private:
	StateContext m_LoadStateContext;
	Image2D m_BackGround;
	std::vector<VersusCharacterPanelMove*> m_CharacterMovePanels;
	std::vector<VersusCharacterImageMove*> m_CharacterImage;
	VersusTextAnime m_VersusTextAnime;
	Image2D m_HideImage;
	VersusIconAnime m_VersusIcon;

};

