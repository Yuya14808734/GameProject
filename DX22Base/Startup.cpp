#include "Main.h"
#include "WinUtil.h"
#include "Timer.h"
#include <crtdbg.h>
#include "Scene.h"

//--- �萔��`
const char* APP_TITLE = "�W���G���X�g";
const Frame DEFAULT_FPS = 60;

/*
* �G���g���|�C���g
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

	//--- �E�B���h�E�̊Ǘ�
	AppState state = APP_STATE_MESSAGE;
	while (state != APP_STATE_QUIT)
	{
		state = UpdateWindow();
		if (state == APP_STATE_WAIT && UpdateTimer())
		{
			MainLoop();
		}
	}

	// �I����
	MainUninit();
	UninitTimer();
	UninitWindow();
	return 0;
}
