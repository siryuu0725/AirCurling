/**
 * @file CircleBlock.h
 * @brief 円柱型(上から見て円形)のブロックオブジェクトを扱う
 * @details　中身：円形ブロッククラス
**/
#ifndef CIRCLE_BLOCK_H_
#define CIRCLE_BLOCK_H_
#include "../ObjectBase.h"

/**
* 円形ブロッククラス
*/
class CircleBlock :public ObjectBase
{
public:
	/**
 　　* @brief  コンストラクタ
 　　* @param (pos_) 座標
 　　* @param (scale_) サイズ
 　　* @param (radius_) 半径
 　　* @param (key_) 描画用キー
 　　*/
	CircleBlock(D3DXVECTOR3 pos_, D3DXVECTOR3 scale_, float radius_, std::string key_);

	~CircleBlock() {}

	/**
	 * @brief  描画情報送信関数
	 */
	void Draw();

	/**
     * @brief   FBXモデル解放関数
     */
	void ReleaseModel();

	/**
 　　* @brief  オブジェクト情報Getter
     * @return ObjectInfoの指定した変数の情報を返す
 　　*/
	const ObjectInfo* GetObjInfo()const { return &m_circleblock_info; }

private:
	ObjectInfo m_circleblock_info;  //!円型ブロック情報
};

#endif
