#pragma once
#include "Character_Base.h"
#include "Effect_Manager.h"
#include "CharacterStateWindow.h"
#include "Timer.h"

class Character_00 : public Character
{
private:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

public:
	void SetDefaultCollider() override;
	State* SetNextState(STATE NextState) override;

private:

	int m_FrameCount = 0;					//�A�^�b�N�����Ă���Ƃ��Ɏg���J�E���g
	float m_AnimeTime = 0.0f;				//�A�j���[�V�����̃^�C��
	CharacterStateWindow m_stateWindow;		//�L�����N�^�[�̃f�o�b�O�E�B���h�E
	//unsigned int m_FrameCount = 0;
	int m_HitAttackStopCount = 0;			//�q�b�g�X�g�b�v�̃J�E���g
	bool m_PushButton = false;

};