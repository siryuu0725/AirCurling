#ifndef OBJBASE_H_
#define OBJBASE_H_
#include"../System/FBXController.h"
#include "../Utility/Collision/Shape.h"
#include "../Utility/Calculation.h"
#include "../System/FBX.h"
#include <vector>
#include <string>

//!外部データ保存用構造体の座標配列のマジックナンバー防止用
enum ARRAY_DATA
{
	X,
	Y,
	Z
};

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
			m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
			m_scale(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
			m_angle(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
			m_width(0.0f), 
			m_height(0.0f),
			m_radius(0.0f),
			m_rote(0.0f)
		{}

		D3DXVECTOR3 m_pos;   //!座標
		D3DXVECTOR3 m_scale; //!サイズ
		D3DXVECTOR3 m_angle; //!回転角度

		D3DXMATRIX m_mat_world;		//!ワールド座標

		std::string m_key;  //!描画用キー

		float m_width;    //!横幅
		float m_height;	//!縦幅

		float m_radius;   //!半径

		float m_rote;   //!回転角度

	};

public:
	ObjectBase() {}
	~ObjectBase() {}
};

#endif
