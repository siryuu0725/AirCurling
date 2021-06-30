#include <fbxsdk.h>
#include <Windows.h>
#include <thread>
#include "System/SystemController.h"
#include "Scene/SceneController.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


int WINAPI WinMain(HINSTANCE hinstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmpLine,
	INT nCmdShow)
{
#ifdef _DEBUG

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

#endif

	//エンジンの初期化
	if (InitEngine(1920, 1080, "AirCurring") == false)
	{
		return 0;
	}

	//初期化
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
			//更新処理
			SceneController::Instance()->Update();

			//描画
			SceneController::Instance()->Draw();

		}
	}

	//エンジン終了
	EndEngine();

#ifdef _DEBUG
	SceneController::Instance()->ReleaseInstance();
#endif

	return 0;
}