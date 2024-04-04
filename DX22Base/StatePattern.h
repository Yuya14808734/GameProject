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
	State* GetNowState();				//���̃X�e�[�g���擾
	State* GetNextState();				//���ɐݒ肵���X�e�[�g���擾
	void ReleaseNowState();				//���̃X�e�[�g��delete����
	void ReleaseNextState();			//���̃X�e�[�g��delete����
	void ReleaseAllState();				//���Ǝ��̃X�e�[�g��delete����
	void StateInit();					//�X�e�[�g�̏�����
	void StateUninit();					//�X�e�[�g�̏I������
	void StateUpdate();					//�X�e�[�g�̃A�b�v�f�[�g
	void StateDraw();					//�X�e�[�g�̕`��
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


