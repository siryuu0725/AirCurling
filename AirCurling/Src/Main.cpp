#include <fbxsdk.h>
#include <Windows.h>
#include <thread>
#include "System/SystemController.h"
#include "Scene/SceneController.h"



int WINAPI WinMain(HINSTANCE hinstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmpLine,
	INT nCmdShow)
{
	//エンジンの初期化
	if (InitEngine(1920, 1080, "エアホッケ―") == false)
	{
		return 0;
	}

	SceneController::Instance()->Init();


	while (true)
	{
		bool message_ret = false;
		MSG msg;

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else if (msg.message == WM_CLOSE)
			{
				break;
			}
			else {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{

			SceneController::Instance()->Update();

			SceneController::Instance()->Draw();

		}
	}

	//エンジン終了
	EndEngine();
}