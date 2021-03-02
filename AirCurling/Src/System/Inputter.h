/**
 * @file Inputter.h
 * @brief キーやマウスの入力関係を扱う
 * @details 中身：入力クラス
**/
#ifndef INPUT_H_
#define INPUT_H_
#include <Windows.h>
#include <dinput.h>
#include "../Utility/Vec.h"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#define MOUSE_ON_VALUE (0x80)		// オン状態の値

/**
* 入力クラス
*/
class Inputter
{
public:
	//!入力状態の種類
	enum InputState
	{
		NotPush,		//!押されていない間
		PushDown,		//!押された瞬間
		Push,			//!押されている間
		PushUp,		//!離した瞬間
	};

	//!マウスボタンの種類
	enum MouseButton
	{
		Left,   //!左 
		Right,	//!右
		Center,	//!ホイール
	};

	//!キーの種類
	enum KeyInfo
	{
		ESCKey,       
		SpaceKey,	   
		AKey,		   
		WKey,		   
		SKey,		   
		DKey,		   
		FKey,		   
		EKey,		   
		QKey,		   
		TKey,		   
		YKey,
		ReturnKey,
		MaxKeyInfo,
	};

private:
	Inputter() {}
	~Inputter() {}

public:
	static Inputter* Instance();

	/**
　　* @brief  入力情報初期化まとめ関数
  　* @detail インターフェース、デバイスなどの初期化を行う
　　*/
	bool InitInput();

	/**
　　* @brief  入力情報解放関数
　　*/
	void EndInput();

	/**
　　* @brief  インターフェース取得関数
　　*/
	bool CreateInputInterface();

	/**
　　* @brief  マウスデバイス設定関数
  　* @detail マウスの操作をできるように設定を行う
　　*/
	bool CreateMouseDevice();

	/**
　　* @brief  キーボードデバイス設定関数
  　* @detail キーボードの操作をできるように設定を行う
　　*/
	bool CreateKeyboardDevice();

	/**
　　* @brief  入力情報の更新関数
  　* @detail キーボードとマウスの入力情報を更新する
　　*/
	void UpdateInput();

	/**
　　* @brief  キーボードの入力情報更新関数
　　*/
	void KeyStateUpdate();

	/**
　　* @brief  キーボードの入力判定関数(押されている間)
  　* @detail キーボードの押されている間trueを返す判定を行う
    * @param (key_)  押されたキーの種類
　　*/
	bool GetKey(KeyInfo key_);

	/**
　　* @brief  キーボードの入力判定関数(押された瞬間)
  　* @detail キーボードの押された瞬間trueを返す判定を行う
	* @param (key_)  押されたキーの種類
　　*/
	bool GetKeyDown(KeyInfo key_);

	/**
　　* @brief  マウスの入力情報更新関数
　　*/
	void UpdateMouse();

	/**
　　* @brief  マウスの入力判定関数
  　* @detail 引数のボタンが押された場合true返す判定を行う
	* @param (button_type_)  押されたボタンの種類
　　*/
	bool OnMouseDown(MouseButton button_type_);

	/**
　　* @brief  マウスの座標取得関数
  　* @detail 現在のマウスの座標をスクリーン座標で返す
　　*/
	Vec2 GetMousePos() { return m_mouse_pos; }

private:
	static Inputter* mp_instance;

	LPDIRECTINPUT8 Ip_interface;
	LPDIRECTINPUTDEVICE8 m_key_device;
	LPDIRECTINPUTDEVICE8 m_mouse_device;		

	DIMOUSESTATE m_prev_mouse_state;			//!マウスの１フレーム前の入力情報
	DIMOUSESTATE m_current_mouse_state;		//!マウスの現在の入力情報
	Vec2 m_mouse_pos;                         //!マウスの座標

	InputState g_InputState[Inputter::KeyInfo::MaxKeyInfo]; //!キーの状態を保持する変数

};


#endif