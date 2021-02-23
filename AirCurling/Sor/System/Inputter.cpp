#include "Inputter.h"
#include <Windows.h>
#include <dinput.h>
#include "Window.h"

//ライブラリ側のキー情報配列
int g_KeyInfo[] = {
	DIK_ESCAPE,
	DIK_SPACE,
	DIK_A,
	DIK_W,
	DIK_S,
	DIK_D,
	DIK_F,
	DIK_E,
	DIK_Q,
	DIK_T,
	DIK_Y,
	DIK_RETURN,
};


Inputter* Inputter::p_instance = nullptr;

Inputter* Inputter::Instance()
{
	if (p_instance == nullptr)
	{
		p_instance = new Inputter;
	}

	return p_instance;
}

//!入力情報初期化まとめ関数
bool Inputter::InitInput()
{
	//!インターフェース取得
	if (CreateInputInterface() == false)
	{
		return false;
	}

	//!マウスデバイス設定
	if (CreateMouseDevice() == false)
	{
		EndInput();
		return false;
	}

	//!キーボードデバイス設定
	if (CreateKeyboardDevice() == false) {
		EndInput();
		return false;
	}

	ZeroMemory(&current_mouse_state, sizeof(DIMOUSESTATE));
	ZeroMemory(&prev_mouse_state, sizeof(DIMOUSESTATE));

	return true;
}

//!入力情報解放関数
void Inputter::EndInput()
{
	//!インターフェース
	if (Ip_interface != nullptr)
	{
		Ip_interface->Release();
		Ip_interface = nullptr;
	}

	//!マウス用デバイス
	if (mouse_device != nullptr)
	{
		mouse_device->Release();
		mouse_device = nullptr;
	}

	//!キーボード用デバイス
	if (key_device != nullptr)
	{
		key_device->Release();
		key_device = nullptr;
	}
}

//!インターフェース取得関数
bool Inputter::CreateInputInterface()
{
	// IDirectInput8インターフェイスの取得
	HRESULT hr = DirectInput8Create(GetModuleHandle(nullptr),
		0x0800,
		IID_IDirectInput8,
		(void**)&Ip_interface,
		NULL);
	if (FAILED(hr))
	{
		return false;
	}
	return true;
}

//!マウスデバイス設定関数
bool Inputter::CreateMouseDevice()
{
	// マウス用にデバイスオブジェクトを作成
	if (FAILED(Ip_interface->CreateDevice(GUID_SysMouse, &mouse_device, NULL)))
	{
		// デバイスの作成に失敗
		return false;
	}

	// データフォーマットを設定
	if (FAILED(mouse_device->SetDataFormat(&c_dfDIMouse)))
	{
		// データフォーマットに失敗
		return false;
	}

	// モードを設定（フォアグラウンド＆非排他モード）
	if (FAILED(mouse_device->SetCooperativeLevel(
		FindWindowA(WINDOW_CLASS_NAME, nullptr),
		DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
	{
		// モードの設定に失敗
		return false;
	}

	// デバイスの設定
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;	// 相対値モードで設定（絶対値はDIPROPAXISMODE_ABS）

	if (FAILED(mouse_device->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		// デバイスの設定に失敗
		return false;
	}

	// 入力制御開始
	mouse_device->Acquire();

	return true;
}

//!キーボードデバイス設定関数
bool Inputter::CreateKeyboardDevice()
{
	// マウス用にデバイスオブジェクトを作成
	if (FAILED(Ip_interface->CreateDevice(GUID_SysKeyboard, &key_device, NULL)))
	{
		// デバイスの作成に失敗
		return false;
	}

	// データフォーマットを設定
	if (FAILED(key_device->SetDataFormat(&c_dfDIKeyboard)))
	{
		// データフォーマットに失敗
		return false;
	}

	// モードを設定（フォアグラウンド＆非排他モード）
	if (FAILED(key_device->SetCooperativeLevel(
		FindWindowA(WINDOW_CLASS_NAME, nullptr),
		DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
	{
		// モードの設定に失敗
		return false;
	}

	// デバイスの設定
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;	// 相対値モードで設定（絶対値はDIPROPAXISMODE_ABS）

	if (FAILED(key_device->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		// デバイスの設定に失敗
		return false;
	}

	// 入力制御開始
	key_device->Acquire();

	return true;
}

//!キーボードの入力情報更新関数
void Inputter::KeyStateUpdate()
{
	BYTE Key[256];
	HRESULT hr = key_device->GetDeviceState(256, Key);

	if (FAILED(hr))
	{
		return;
	}

	for (int i = 0; i < MAX_KEY_INFO; i++)
	{
		if (Key[g_KeyInfo[i]] & 0x80)
		{
			if (g_InputState[i] == INPUT_STATE::NOT_PUSH || g_InputState[i] == INPUT_STATE::PUSH_UP)
			{
				g_InputState[i] = INPUT_STATE::PUSH_DOWN;
			}
			else
			{
				g_InputState[i] = INPUT_STATE::PUSH;
			}
		}
		else
		{
			if (g_InputState[i] == INPUT_STATE::PUSH || g_InputState[i] == INPUT_STATE::PUSH_DOWN)
			{
				g_InputState[i] = INPUT_STATE::PUSH_UP;
			}
			else
			{
				g_InputState[i] = INPUT_STATE::NOT_PUSH;
			}
		}
	}
}

//!キーボードの入力判定関数(押されている間)
bool Inputter::GetKey(KEY_INFO key_)
{
	return (g_InputState[key_] == INPUT_STATE::PUSH);
}

//!キーボードの入力判定関数(押された瞬間)
bool Inputter::GetKeyDown(KEY_INFO key_)
{
	return (g_InputState[key_] == INPUT_STATE::PUSH_DOWN);
}

//!入力情報の更新関数
void Inputter::UpdateInput()
{
	UpdateMouse();
	KeyStateUpdate();

	prev_mouse_state = current_mouse_state;
	// マウスの状態を取得します
	HRESULT	hr = mouse_device->GetDeviceState(sizeof(DIMOUSESTATE), &current_mouse_state);
	if (FAILED(hr))
	{
		mouse_device->Acquire();
		hr = mouse_device->GetDeviceState(sizeof(DIMOUSESTATE), &current_mouse_state);
	}
}

//!マウスの入力判定関数
bool Inputter::OnMouseDown(MouseButton button_type_)
{
	if (!(prev_mouse_state.rgbButtons[button_type_] & MOUSE_ON_VALUE) &&
		current_mouse_state.rgbButtons[button_type_] & MOUSE_ON_VALUE)
	{
		return true;
	}

	return false;
}

//!マウスの入力情報更新関数
void Inputter::UpdateMouse()
{
	Vec2 prev = mouse_pos;
	POINT p;
	GetCursorPos(&p);
	//ScreenToClient(FindWindowA(TEXT("Window"), nullptr), &p);
	/*float a=(float)GetSystemMetrics(SM_CXSCREEN);
	float horizon = (float)GetSystemMetrics(SM_CXSCREEN) / 1920.f;
	float vertical = (float)GetSystemMetrics(SM_CYSCREEN) / 1080.f;
	p.x /= horizon;
	p.y /= vertical;*/

	mouse_pos.X = (float)p.x;
	mouse_pos.Y = (float)p.y;
}