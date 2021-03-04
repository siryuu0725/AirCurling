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
 　　* @param[in] pos_ 座標
 　　* @param[in] scale_ サイズ
 　　* @param[in] radius_ 半径
 　　* @param[in] key_ 描画用キー
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
     * @param[out] copy_info_ 保存用オブジェクト構造体
	 * @details 引数にオブジェクトの情報を渡す
 　　*/
	void GetCircleBlockInfo(ObjectInfo& copy_info_) { copy_info_ = m_circleblock_info; }

private:
	ObjectInfo m_circleblock_info;  //!円型ブロック情報
};

#endif
