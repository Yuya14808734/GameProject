#include "StatePattern.h"

StateContext::StateContext()
	:m_pNowState(nullptr),
	m_pNextState(nullptr)
{
}

StateContext::~StateContext()
{
}

void StateContext::SetNextState(State* pState)
{
	if (m_pNextState != nullptr) delete m_pNextState;
	m_pNextState = pState;
}

State* StateContext::ChangeNextState()
{
	if (m_pNextState == nullptr) return nullptr;

	if (m_pNowState != nullptr)
	{
		delete m_pNowState;
	}

	m_pNowState = m_pNextState;
	m_pNextState = nullptr;

	m_pNowState->Init();

	return m_pNowState;
}

State* StateContext::GetNowState()
{
	return m_pNowState;
}

State* StateContext::GetNextState()
{
	return m_pNextState;
}

void StateContext::StateInit()
{
	if (m_pNowState == nullptr)
	{
		return;
	}

	m_pNowState->Init();
}

void StateContext::StateUninit()
{
	if (m_pNowState == nullptr)
	{
		return;
	}

	m_pNowState->Uninit();
}

void StateContext::StateUpdate()
{
	if (m_pNowState == nullptr)
	{
		return;
	}

	m_pNowState->Update();
}
