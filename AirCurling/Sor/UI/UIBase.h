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

	struct UIInfoCopy
	{
		float pos_x;   //!座標
		float pos_y;   //!座標
	};
};

#endif