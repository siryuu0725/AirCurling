/**
 * @file Window.h
 * @brief Window作成を行う
**/
#ifndef WINDOW
#define WINDOW

#include<Windows.h>
#include <d3dx9.h>

#define WINDOW_CLASS_NAME "Window"	//!< ウィンドウクラス名



bool MakeWindow(int width_, int height_, const char* title_);
HWND GetWindowHandle();
D3DXVECTOR2 GetWindowSize();


#endif