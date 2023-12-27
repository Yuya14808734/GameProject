#pragma once
#include "Scene.h"
#include <vector>
#include "Character_Base.h"
#include "Stage_Base.h"


class SceneGame : public CScene
{
public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	std::vector<Character*>& GetCharacter();
	Stage* GetStage();

private:
	std::vector<Character*> m_Characters;	//キャラクターの情報
	Stage* m_pStage;						//ステージの情報

};