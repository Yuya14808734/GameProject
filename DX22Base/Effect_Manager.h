//#pragma once
#ifndef EFFECT_MANAGER_H
#define EFFECT_MANAGER_H

#if _DEBUG
#pragma comment(lib,"Effekseerd.lib")
#pragma comment(lib,"EffekseerRendererDX11d.lib")
#else
#pragma comment(lib,"Effekseer.lib")
#pragma comment(lib,"EffekseerRendererDX11.lib")
#endif

#include <Effekseer.h>
#include <EffekseerRendererDX11.h>

class EffectManager
{
public:
	static void EffectInit();
	static void EffectUninit();
	static Effekseer::ManagerRef& GetManager();
	static void Add_Effect(std::string EffectName, const char16_t* FileName);	//エフェクト情報の追加
	static Effekseer::EffectRef GetEffect(std::string EffectName);
	static void EffectUpdate();
	static void EffectDraw(Effekseer::Handle EffectHandle);
	static void SetIsDrawEffect(bool IsDraw);
private:
	static Effekseer::ManagerRef m_efkManager;
	static EffekseerRendererDX11::RendererRef m_efkRenderer;
	static std::map<std::string, Effekseer::EffectRef> m_Effect;
	static unsigned int m_EffectTimeCount;
	static bool m_IsDrawEffect;
};

#endif // !EFFECT_MANAGER_H
