#include "Main.h"
#include "WinUtil.h"
#include "Timer.h"
#include <crtdbg.h>
#include "Scene.h"

//--- 定数定義
const char* APP_TITLE = "ジュエリスト";
const Frame DEFAULT_FPS = 60;

/*
* エントリポイント
*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_CHECK_ALWAYS_DF | _CRTDBG_LEAK_CHECK_DF);

	if (FAILED(InitWindow(APP_TITLE, GetAppWidth(), GetAppHeight())))
	{
		Error("window initialize faield");
	}
	InitTimer(DEFAULT_FPS);
	MainInit();

	//--- ウィンドウの管理
	AppState state = APP_STATE_MESSAGE;
	while (state != APP_STATE_QUIT)
	{
		state = UpdateWindow();
		if (state == APP_STATE_WAIT && UpdateTimer())
		{
			MainLoop();
		}
	}

	// 終了時
	MainUninit();
	UninitTimer();
	UninitWindow();
	return 0;
}
