#pragma once
#include "Effect_Manager.h"

class EffectBase
{
public:
	EffectBase();									//������
	virtual ~EffectBase();							//�I������
	virtual void Update();							//�X�V
	virtual void Draw();							//�`��
	virtual void PausedEffect(bool Paused = true);	//�G�t�F�N�g���~�߂�Ƃ��̏���

	void SetDestroy(bool destroy = true);
	bool GetisDestroy();

protected:
	bool m_isDestroy = false;
};