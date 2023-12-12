#pragma once
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include <vector>
#include <string>

class MiniWindow
{
public:
	static void WindowInit();
	static void WindowUninit();
	static void WindowDrawUpdate();

private:
	static std::vector<MiniWindow*> m_MiniWindowVector;

public:
	void Init_MiniWindow();
	void Uninit_MiniWindow();
	void DrawUpdate_MiniWindow();
	bool IsDraw();

protected:
	virtual void Init() {};
	virtual void Uninit() {};
	virtual void DrawUpdate() {};

protected:
	std::string m_WindowName;
	bool m_Draw = true;
	ImVec4 m_BarColor_Selection = ImVec4(1.0f, 0.3f, 0.3f, 1.0f);
	ImVec4 m_BarColor_NonSelect = ImVec4(0.4f,0.1f,0.1f,1.0f);
	ImVec2 m_Pos = ImVec2(0.0f,0.0f);
	ImVec2 m_Size = ImVec2(1.0f,1.0f);
};