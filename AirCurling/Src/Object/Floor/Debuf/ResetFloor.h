#ifndef RESET_FLOOR_H
#define RESET_FLOOR_H_
#include "../../ObjectBase.h"

/**
*@clss   リセットデバフ床クラス
*/

class ResetFloor :public ObjectBase
{
public:
	/**
 　　* @brief  コンストラクタ
 　　* @param (pos_) 座標
 　　* @param (scale_) サイズ
 　　* @param (angle_) 回転角度
   　* @param (width_) 横幅
 　　* @param (height_) 縦幅
 　　* @param (key_) 描画用キー
 　　*/
	ResetFloor(D3DXVECTOR3 pos_, D3DXVECTOR3 scale_, float radius_, std::string key_);
	~ResetFloor() {}

	/**
     * @brief  描画情報送信関数
     */
	void SetUpBuffer();

	/**
	 * @brief   FBXモデル解放関数
	 */
	void ReleaseModel();

	/**
 　　* @brief  オブジェクト情報Getter
	 * @return ObjectInfoの指定した変数の情報を返す
 　　*/
	const ObjectInfo* GetObjInfo()const { return &m_reset_floor_info; }
private:
	ObjectInfo m_reset_floor_info; //!リセット床情報
};

#endif