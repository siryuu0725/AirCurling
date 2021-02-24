#ifndef UIBASE_H_
#define UIBASE_H_
#include "../System/Graphics.h"
#include <d3d9.h>
#include <d3dx9.h>

/**
*@class  UIベースクラス
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
		D3DXVECTOR2 m_pos;  //!座標
	};
};

#endif