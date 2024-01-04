#pragma once
#include "Player_Controller.h"
#include "Image2D.h"
#include "Select01_CharacterList.h"
#include <array>

class SelectCharacter
{
public:
	enum class SELECTSTATE : int
	{
		SELECT = 0,	//選んでいる
		DECIDED,	//決定している
		MAX
	};

	enum class BOARDCOLOR
	{
		BLACK = 0,
		RED,
		BLUE,
		MAX
	};

private:
	static constexpr float m_StandCharacterLerpTime = 0.5f;
	static constexpr float m_VisibleConnectTextTime = 0.5f;
	static constexpr float m_VisibleDisConnectTextTime = 0.5f;

public:
	static void AlphaUpdate();

private:
	static float m_AlphaCount;

public:
	SelectCharacter();												//コンストラクタ
	~SelectCharacter();												//デストラクタ
	void Update();													//更新
	void BoardDraw();												//描画
	void StandCharacterDraw();										//立っているキャラクターの描画
	void SelectFrameDraw();											//選んでいるキャラクターを書こうフレームの描画
	void SetBoardColor(BOARDCOLOR color);							//ボードのカラーを設定
	void SetController(PlayerController* Controller);				//コントローラーを設定
	void ChangeNowController(PlayerController* Controller);			//コントローラーを変更
	void SetNowCharacter(SelectCharacterList::CHARACTER NowCharacter);	//キャラクターを設定
	bool IsDecided();												//キャラクターを決定したか
	SelectCharacter::SELECTSTATE GetState();
	SelectCharacterList::CHARACTER GetSelectCharacter();
	void SetBoardPos(const CVector3& pos);
	const CVector3& GetBoardPos() const;
	void SetCharacterList(SelectCharacterList* pCharacterList);
	void SetLerpStandCharacterDrawPos(const CVector3& StartPos, const CVector3& EndPos);

private:
	void SelectUpdate();											//選んでいるときのアップデート
	void DecidedUpdate();											//決定した後のアップデート

	void StandCharacterChangeInit();								//キャラクターの立ち絵を表示するための準備
	void StandCharacterChangeUpdate();								//キャラクターの立ち絵を表示するまでのアニメーション
private:

	//=======<キャラクターセレクトの状態変数>==============================================================
	int						m_SelectPlayerNumber = 0;					//自分が何番目に選んでいるか
	SELECTSTATE				m_SelectState = SELECTSTATE::MAX;		//選んでいる今の状態
	int						m_NowSelectCharacter = 0;				//選んでいるキャラクターの番号
	bool					m_isDecided = false;					//キャラクターを選択したか
	//======================================================================================================

	//=======<コントローラーに関する情報>===================================================================
	PlayerController*		m_pSelectController = nullptr;			//コントローラー情報
	//======================================================================================================
	
	//=======<UIの中心になる位置の情報>=====================================================================
	CVector3				m_BasePos;								//ボードやキャラクターのアイコンなどの中心になる位置
	//======================================================================================================

	//=======<後ろのボードに関する情報>=====================================================================
	Image2D					m_CharacterBoardImage;					//キャラクターセレクトの後ろにあるボード
	Image2D					m_ControllerImage;						//コントローラーの画像
	Image2D					m_SelectedImage;						//選ばれたときの画像
	//======================================================================================================
	
	//=======<接続に関する情報>=============================================================================
	Image2D					m_ConnectedText;						//繋がったときの場合の文章画像
	Image2D					m_NoConnectText;						//何も繋がっていない場合の文章画像
	Image2D					m_DisConnectedText;						//接続解除された場合の文章画像
	Image2D					m_ConnectBackGround_Image;				//文章の後ろにある画像
	Image2D					m_ConnectBackGround_Frame;				//文章の後ろにある画像の枠
	float					m_VisibleConnectTextCount = 0.0f;		//繋がりましたを描画する時間
	float					m_VisibleDisconnectTextCount = 0.0f;		//解除されましたを描画する時間
	//======================================================================================================

	//=======<キャラクターをセレクトするときに関する情報>===================================================
	Image2D					m_FrameImage;							//キャラクターを囲うフレーム
	SelectCharacterList*	m_pCharacterList = nullptr;				//キャラクターリストのポインタ
	//======================================================================================================

	//=======<キャラクターの立ち絵を表示するときに使う情報>=================================================
	float					m_StandCharacterImageDrawPos_LerpCount = 0.0f;	//どのくらい移動したか
	CVector3				m_StandCharacterImageDrawPos_LerpStart;		//キャラクターの立ち絵を最初に表示したい位置
	CVector3				m_StandCharacterImageDrawPos_LerpEnd;		//キャラクターの立ち絵を最後に表示したい位置
	CVector3				m_StandCharacterImageDrawPos_LerpNow;		//キャラクターの立ち絵を今表示している位置
	float					m_StandCharacterDrawAlpha = 0.0f;			//キャラクターの立ち絵の透明度
	//======================================================================================================
};