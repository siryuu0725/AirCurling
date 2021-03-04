/**
 * @file UIBase.h
 * @brief 各UIの共通部分を扱う
 * @details 中身：UIベースクラス
**/
#ifndef UIBASE_H_
#define UIBASE_H_
#include "../System/DirectGraphics.h"
#include <d3d9.h>
#include <d3dx9.h>

/**
* UIベースクラス
*/
class UIBase
{
public:
	UIBase() :m_ui_num(0) {}
	~UIBase() {}

protected:
	int m_ui_num;

	struct UIExternalInfo
	{
		UIExternalInfo() :
			m_pos(D3DXVECTOR2(0.0f, 0.0f))
		{}

		D3DXVECTOR2 m_pos;  //!座標
	};
};

#endif