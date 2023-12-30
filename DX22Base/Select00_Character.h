#pragma once
#include "Player_Controller.h"
#include "Image2D.h"
#include "Select01_CharacterList.h"

class SelectCharacter
{
public:
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
	void SetController(PlayerController* Controller);				//コントローラーを設定
	void ChangeNowController(PlayerController* Controller);			//コントローラーを変更
	void SetNowCharacter(SelectCharacterList::CHARACTER NowCharacter);	//キャラクターを設定
	bool IsDecided();												//キャラクターを決定したか
	SelectCharacter::SELECTSTATE GetState();
	void SetCharacterList(std::array<Image2D, static_cast<int>(SelectCharacterList::CHARACTER::MAX)>* pCharacterImageList);
																	//選択できるキャラクターの画像配列を設定

private:
	void SelectUpdate();											//選んでいるときのアップデート
	void AnimationUpdate();											//アニメーションのアップデート
	void DecidedUpdate();											//決定した後のアップデート

private:
	SELECTSTATE m_SelectState = SELECTSTATE::MAX;					//選んでいる今の状態
	PlayerController* m_pSelectController = nullptr;				//コントローラー情報
	int m_NowSelectCharacter = 0;									//選んでいるキャラクターの番号
	bool m_isDecided = false;										//キャラクターを選択したか
	Image2D m_FrameImage;											//キャラクターを囲うフレーム
	std::array<Image2D, static_cast<int>(SelectCharacterList::CHARACTER::MAX)>*
		m_pCharacterImageList = nullptr;
};