#pragma once

class State;
class StateContext;

class StateContext
{
public:
	StateContext();
	~StateContext();

	void SetNextState(State* pState);	//���̃X�e�[�g��ݒ肷��
	State* ChangeNextState();			//����ւ���
	State* GetNowState();
	State* GetNextState();			//����ւ���
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
