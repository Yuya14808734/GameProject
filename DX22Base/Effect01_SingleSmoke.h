#pragma once
#include "EffectBase.h"
#include "Calculation.h"
#include "Image3D.h"

//==========================================================
// 
// ������񂾎��̉_�̃G�t�F�N�g(�����)
// 
//==========================================================

class SingleSmoke : public EffectBase
{
public:
	SingleSmoke();
	~SingleSmoke() override;
	void Update() override;
	void Draw() override;
	void PausedEffect(bool paused = true) override;
	void SetPos(const CVector3& pos);
	void SetTime(float EndTime);
	void SetVelocity(const CVector3& velocity);
	void PlayEffect(const CVector3& pos,float endTime,const CVector3& velocity);

private:
	Image3D m_SmokeImage;								//�_�̉摜
	CVector3 m_Velocity;								//�_�𓮂����x�N�g��
	ConstantBuffer m_Buffer_DissolveParameter;			//�萔�o�b�t�@
	float m_Time = 0.0f;								//���̎���
	float m_EndTime = 0.0f;								//�G�t�F�N�g�폜����
	bool m_isUpdate = false;							//�A�b�v�f�[�g�����邩
	ID3D11ShaderResourceView* m_pDissolveTexture;		//�f�B�]���u�̃e�N�X�`��
	float m_DissolveParameter[4];						//�萔�o�b�t�@�ɓn�����e
};