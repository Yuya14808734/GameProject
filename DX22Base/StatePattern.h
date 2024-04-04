#pragma once

class State;
class StateContext;

class StateContext
{
public:
	StateContext();
	~StateContext();

	void SetNextState(State* pState);	//次のステートを設定する
	State* ChangeNextState();			//入れ替える
	State* GetNowState();				//今のステートを取得
	State* GetNextState();				//次に設定したステートを取得
	void ReleaseNowState();				//今のステートをdeleteする
	void ReleaseNextState();			//次のステートをdeleteする
	void ReleaseAllState();				//今と次のステートをdeleteする
	void StateInit();					//ステートの初期化
	void StateUninit();					//ステートの終了処理
	void StateUpdate();					//ステートのアップデート
	void StateDraw();					//ステートの描画
public:
	State* m_pNowState = nullptr;
	State* m_pNextState = nullptr;
};

class State
{
public:
	State() {};
	virtual ~State() {};
	virtual void Init() {};
	virtual void Uninit() {};
	virtual void Update() {};
	virtual void Draw() {};
};


