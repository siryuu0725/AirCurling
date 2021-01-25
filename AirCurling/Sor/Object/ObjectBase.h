#ifndef OBJBASE_H_
#define OBJBASE_H_
#include"../System/FBXController.h"
#include "../Utility/Collision/Shape.h"
#include "../Utility/Calculation.h"
#include "../System/FBX.h"
#include <vector>
#include <string>

/**
*@clss   オブジェクトベースクラス
*/

class ObjectBase
{
protected:

	//!オブジェクト情報
	struct ObjectInfo
	{
		ObjectInfo() :
			pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
			scale(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
			angle(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
			width(0.0f), height(0.0f),
			radius(0.0f),
			rote(0.0f)
		{}

		D3DXVECTOR3 pos;   //!座標
		D3DXVECTOR3 scale; //!サイズ
		D3DXVECTOR3 angle; //!回転角度

		D3DXMATRIX mat_world;		//!ワールド座標

		std::string key;  //!描画用キー

		float width;    //!横幅
		float height;	//!縦幅

		float radius;   //!半径

		float rote;   //!回転角度

	};

public:
	ObjectBase() {}
	~ObjectBase() {}
};

#endif
