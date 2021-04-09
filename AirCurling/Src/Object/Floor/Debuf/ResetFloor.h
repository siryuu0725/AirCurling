/**
 * @file ResetFloor.h
 * @brief 触れると初期位置に戻されるデバフ床オブジェクト
 * @details　中身：リセットデバフ床クラス
**/

#ifndef RESETFLOOR_H
#define RESETFLOOR_H_
#include "../../ObjectBase.h"

/**
* リセットデバフ床クラス
*/
class ResetFloor :public ObjectBase
{
public:
	/**
 　　* @brief  コンストラクタ
 　　* @param[in] pos_ 座標
 　　* @param[in] scale_ サイズ
 　　* @param[in] angle_ 回転角度
   　* @param[in] width_ 横幅
 　　* @param[in] height_ 縦幅
 　　* @param[in] key_ 描画用キー
 　　*/
	ResetFloor(D3DXVECTOR3 pos_, D3DXVECTOR3 scale_, float radius_, std::string key_);
	~ResetFloor() {}

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
	const void GetResetFloorInfo(ObjectInfo& copy_info_) { copy_info_ = m_resetfloor_info; }

private:
	ObjectInfo m_resetfloor_info; //!リセット床情報
};

#endif