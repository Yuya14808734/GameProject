#pragma once
#include "Player_Controller.h"

class SelectCharacter
{
public:
	enum class CHARACTER : int
	{
		UNITYCHAN = 0,
		MAX
	};

	enum class SELECTSTATE : int
	{
		SELECT = 0,	//選んでいる
		ANIMATION,	//UIが動いている
		DECIDED,	//決定している
		MAX
	};

public:
	SelectCharacter();
	~SelectCharacter();
	void Update();
	void Draw();
	void SetController(PlayerController* Controller);			//コントローラーを設定
	void ChangeNowController(PlayerController* Controller);		//コントローラーを変更
	void SetNowCharacter(CHARACTER NowCharacter);				//キャラクターを設定
	bool IsDecided();											//キャラクターを決定したか
	SelectCharacter::SELECTSTATE GetState();

private:
	void SelectUpdate();		//選んでいるときのアップデート
	void AnimationUpdate();		//アニメーションのアップデート
	void DecidedUpdate();		//決定した後のアップデート

private:
	SELECTSTATE m_SelectState = SELECTSTATE::MAX;
	PlayerController* m_pSelectController = nullptr;
	int m_NowSelectCharacter = 0;
	bool m_isDecided = false;
};