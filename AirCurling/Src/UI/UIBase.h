#ifndef UIBASE_H_
#define UIBASE_H_
#include "../System/Graphics.h"
#include <d3d9.h>
#include <d3dx9.h>

/**
*@clss  UIベースクラス
*/

class UIBase
{
public:
	UIBase() {}
	~UIBase() {}

protected:
	int m_ui_num;

	struct UIExternalInfo
	{
		float pos_x;  //!X座標
		float pos_y;  //!Y座標
	};
};

#endif