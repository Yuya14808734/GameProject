//#pragma once
#ifndef EFFECT_MANAGER_H
#define EFFECT_MANAGER_H
#include <Effekseer.h>
#include <EffekseerRendererDX11.h>
#include <map>
#include <string>
#include "CameraBase.h"
#include <DirectXMath.h>

class Effect_Manager
{
public:
	typedef struct 
	{
		Effekseer::EffectRef effect;
		Effekseer::Handle Handle;
		float time;
	}Effect_Info;

public:
	static void Effect_Init();
	static void Effect_Uninit();
	static Effekseer::ManagerRef GetManager();
	static Effekseer::EffectRef GetEffect(std::string EffectName);
	static void Add_Effect(std::string EffectName, const char16_t* FileName);	//�G�t�F�N�g���̒ǉ�
	static void Play_Effect(std::string EffectName,DirectX::XMFLOAT3 Position);	//�G�t�F�N�g���Đ�
	static void Play_Effect(std::string EffectName,DirectX::XMFLOAT3 Position, DirectX::XMFLOAT3 Size);	//�G�t�F�N�g���Đ�
	static void Stop_Effect(std::string EffectName);
	static void Draw_Effect(CameraBase* pCamera);	//�G�t�F�N�g��`��

private:
	static Effekseer::ManagerRef m_efkManager;
	static EffekseerRendererDX11::RendererRef m_efkRenderer;
	static std::map<std::string, Effect_Manager::Effect_Info> m_Effect;
};


#endif // !EFFECT_MANAGER_H
