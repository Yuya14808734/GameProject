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
	State* GetNowState();
	State* GetNextState();			//入れ替える
	void StateInit();
	void StateUninit();
	void StateUpdate();
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
};
