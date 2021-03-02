/**
 * @file RectBlock.h
 * @brief 立方体(上から見て矩形)のブロックオブジェクト
 * @details　中身：矩形型ブロッククラス
**/
#ifndef RECT_BLOCK_H_
#define RECT_BLOCK_H_
#include "../ObjectBase.h"

/**
* 矩形型ブロッククラス
*/
class RectBlock :public ObjectBase
{
public:

	/**
 　　* @brief  コンストラクタ
 　　* @param (pos_)   座標
 　　* @param (scale_) サイズ
 　　* @param (angle_) 回転角度
   　* @param (width_) 横幅
 　　* @param (height_) 縦幅
 　　* @param (key_) 描画用キー
 　　*/
	RectBlock(D3DXVECTOR3 pos_, D3DXVECTOR3 scale_, D3DXVECTOR3 angle_, float width_, float height_, std::string key_);
	~RectBlock() {}

	/**
	 * @brief  描画情報送信関数
	 */
	void Draw();

	/**
	 * @brief   FBXモデル解放関数
	 */
	void ReleaseModel();

private:
	//!矩形型ブロック情報(頂点情報)
	ObjectInfo m_rectblock_info;

public:
	/**
 　　* @brief  オブジェクト情報Getter
     * @return RectBlockInfoの指定した変数の情報を返す
 　　*/
	const ObjectInfo* GetObjInfo()const { return &m_rectblock_info; }
};

#endif
