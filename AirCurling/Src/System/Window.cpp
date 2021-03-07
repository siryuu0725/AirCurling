#include "Window.h"

HWND hWnd;
HWND GetWindowHandle() { return hWnd; }

D3DXVECTOR2 windowsize;
D3DXVECTOR2 GetWindowSize() { return windowsize; }

LRESULT CALLBACK WindowProc(HWND window_handle_, UINT message_id_, WPARAM wparam_, LPARAM lparam_)
{
	switch (message_id_)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	/*case WM_KEYDOWN:
		if (wparam_ == VK_ESCAPE)
		{
			PostMessage(window_handle_, WM_CLOSE, NULL, NULL);
		}*/
	default:
		return DefWindowProc(window_handle_, message_id_, wparam_, lparam_);
		break;
	}
	return 0;
}

bool MakeWindow(int width_, int height_, const char* title_)
{
	WNDCLASSEX window_class = {
		sizeof(WNDCLASSEXA),			//構造体のサイズ
		CS_HREDRAW | CS_VREDRAW,		//クラスのスタイル
		WindowProc,						//ウィンドウプロシージャ
		0,								//補助メモリ
		0,								//補助メモリ
		GetModuleHandle(nullptr),		//このプログラムのインスタンスハンドル
		LoadIcon(NULL, IDI_APPLICATION),//アイコン画像
		LoadCursor(NULL, IDC_ARROW),	//カーソル画像
		nullptr,						//背景ブラシ(背景色)
		nullptr,						//メニュー名
		WINDOW_CLASS_NAME,				//クラス名									
		nullptr							//小さいアイコン
	};

	//構造体の登録
	if (RegisterClassEx(&window_class) == 0)
	{
		return 0;
	}

	//ウィンドウ作成
	hWnd = CreateWindow(
		WINDOW_CLASS_NAME,
		title_,
		WS_VISIBLE | WS_POPUP,
		//(WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME) | WS_VISIBLE,
		CW_USEDEFAULT,
		0,
		width_,
		height_,
		nullptr,
		nullptr,
		GetModuleHandle(nullptr),
		nullptr);

	if (hWnd == NULL)
	{
		return 0;
	}

	RECT window_rect;
	RECT client_rect;

	GetWindowRect(hWnd, &window_rect);
	GetClientRect(hWnd, &client_rect);

	int frame_size_x = (window_rect.right - window_rect.left) - (client_rect.right - client_rect.left);
	int frame_size_y = (window_rect.bottom - window_rect.top) - (client_rect.bottom - client_rect.top);

	SetWindowPos(hWnd, NULL, CW_USEDEFAULT, CW_USEDEFAULT, frame_size_x + width_, frame_size_y + height_, SWP_NOMOVE);

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	windowsize.x = (float)width_;
	windowsize.y = (float)height_;


	return hWnd;
}