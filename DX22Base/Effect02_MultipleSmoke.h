#pragma once

#include "EffectBase.h"
#include "Calculation.h"
#include "Image3D.h"
#include <vector>
#include "Shader.h"

//==========================================================
// 
// ������񂾎��̉_�̃G�t�F�N�g(����)
// 
//==========================================================

class MultipleSmoke : public EffectBase
{
private:
	struct SingleSmokeParameter
	{
		int texNum = 0;
		float time = 0.0f;
		CVector3 pos;
		CVector3 basePos;
		CVector2 size;
		CVector3 velocity;
	};

public:
	MultipleSmoke();
	~MultipleSmoke() override;
	void Update() override;
	void Draw() override;
	void PausedEffect(bool paused = true) override;
	void AddPlayEffect(const CVector3& pos, const CVector3& velocity);
	void SetSingleSmokeEndTime(float time);
	void SetEffectAddEnd(bool end);

private:
	Image3D m_SmokeImages[4];								//�_�̉摜
	std::vector<SingleSmokeParameter> m_SingleSmokeParams;	//�P��̉_�̃p�����[�^
	PixelShader* m_pDissovleShader = nullptr;				//�s�N�Z���V�F�[�_
	bool m_EffectAddEnd = false;							//�G�t�F�N�g������������Ȃ�����ݒ�
	ConstantBuffer m_Buffer_DissolveParameter;				//�萔�o�b�t�@
	float m_EndTime = 0.0f;									//�G�t�F�N�g�폜����
	bool m_isUpdate = false;								//�A�b�v�f�[�g�����邩
	ID3D11ShaderResourceView* m_pDissolveTexture = nullptr;	//�f�B�]���u�̃e�N�X�`��
	float m_DissolveParameter[4];							//�萔�o�b�t�@�ɓn�����e

};