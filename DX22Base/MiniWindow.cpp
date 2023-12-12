#include "MiniWindow.h"
#include "DirectX.h"
#include "WinUtil.h"
#include "Main.h"
#include "Calculation.h"

std::vector<MiniWindow*> MiniWindow::m_MiniWindowVector;

void MiniWindow::WindowInit()
{
	//ImGuiの初期化
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(GetHWND());
	ImGui_ImplDX11_Init(GetDevice(), GetContext());

	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("Assets/Font/BIZ-UDGothicB.ttc", 12.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
}

void MiniWindow::WindowUninit()
{
	m_MiniWindowVector.clear();

	//ImGuiの終了処理
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void MiniWindow::WindowDrawUpdate()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	for (MiniWindow* copy : m_MiniWindowVector)
	{
		if (!copy->IsDraw())
		{
			continue;
		}

		copy->DrawUpdate_MiniWindow();
	}

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void MiniWindow::Init_MiniWindow()
{
	m_MiniWindowVector.push_back(this);
	int i = m_MiniWindowVector.size();
	m_WindowName = "Window" + std::to_string(i);

	Init();
}

void MiniWindow::Uninit_MiniWindow()
{
	Uninit();
	
	std::vector<MiniWindow*>::iterator itr;
	itr = std::find(m_MiniWindowVector.begin(), m_MiniWindowVector.end(), this);

	//あれば解放
	if (itr != m_MiniWindowVector.end())
	{
		m_MiniWindowVector.erase(itr);
	}
}

void MiniWindow::DrawUpdate_MiniWindow()
{
	//ウィンドウのカラー決め
	ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_TitleBgActive, m_BarColor_Selection);
	ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_TitleBg, m_BarColor_NonSelect);

	ImGui::SetNextWindowPos(m_Pos, ImGuiCond_::ImGuiCond_Appearing);
	ImGui::SetNextWindowSize(m_Size, ImGuiCond_::ImGuiCond_Appearing);

	//ウィンドウの作成-----------------------------------
	ImGui::Begin(m_WindowName.c_str());

	DrawUpdate();

	ImGui::End();
	//---------------------------------------------------
	//呼ばないとエラー出る
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
}

bool MiniWindow::IsDraw()
{
	return m_Draw;
}

