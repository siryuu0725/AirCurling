﻿/**
 * @file StopFloor.h
 * @brief 触れるとスピードが減少するデバフ床オブジェクト
 * @details　中身：摩擦上昇デバフ床クラス
**/

#ifndef STOPFLOOR_H
#define STOPFLOOR_H_
#include "../../ObjectBase.h"

/**
* 摩擦上昇デバフ床クラス
*/
class StopFloor :public ObjectBase
{
public:
	/**
 　　* @brief  コンストラクタ
 　　* @param[in] pos_ 座標
 　　* @param[in] scale_ サイズ
   　* @param[in] radius_ 半径
 　　* @param[in] key_ 描画用キー
 　　*/
	StopFloor(D3DXVECTOR3 pos_, D3DXVECTOR3 scale_, D3DXVECTOR3 angle_, float width_, float height_, std::string key_);
	~StopFloor() {}

	/**
     * @brief  描画情報送信関数
     */
	virtual void Draw()override;

	/**
	 * @brief   FBXモデル解放関数
	 */
	virtual void ReleaseModel()override;

	/**
　　* @brief  オブジェクト情報Getter
	* @param[out] copy_info_ 保存用オブジェクト構造体
	* @details 引数にオブジェクトの情報を渡す
　　*/
	const void GetStopFloorInfo(ObjectInfo& copy_info_) { copy_info_ = m_stopfloor_info; }
private:
	ObjectInfo m_stopfloor_info;  //!スピード減衰床情報
};

#endif