#ifndef STOP_FLOOR_H
#define STOP_FLOOR_H_
#include "../../ObjectBase.h"

/**
*@clss   摩擦上昇デバフ床クラス
*/

class StopFloor :public ObjectBase
{
public:
	/**
 　　* @brief  コンストラクタ
 　　* @param (pos_) 座標
 　　* @param (scale_) サイズ
   　* @param (radius_) 半径
 　　* @param (key_) 描画用キー
 　　*/
	StopFloor(D3DXVECTOR3 pos_, D3DXVECTOR3 scale_, D3DXVECTOR3 angle_, float width_, float height_, std::string key_);
	~StopFloor() {}

	/**
     * @brief  描画情報送信関数
     */
	void SetUpBuffer();

	/**
 　　* @brief  オブジェクト情報Getter
 　　*/
	const ObjectInfo* GetObjInfo()const { return &m_stop_floor_info; }
private:
	ObjectInfo m_stop_floor_info;  //!スピード減衰床情報
};

#endif