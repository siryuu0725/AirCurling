﻿/**
 * @file RectBlock.h
 * @brief 立方体(上から見て矩形)のブロックオブジェクト
 * @details　中身：矩形型ブロッククラス
**/
#ifndef RECTBLOCK_H_
#define RECTBLOCK_H_
#include "../ObjectBase.h"

/**
* 矩形型ブロッククラス
*/
class RectBlock :public ObjectBase
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
	RectBlock(D3DXVECTOR3 pos_, D3DXVECTOR3 scale_, D3DXVECTOR3 angle_, float width_, float height_, std::string key_);
	~RectBlock() {}

	/**
	 * @brief  描画情報送信関数
	 */
	virtual void Draw()override;

	/**
	 * @brief   FBXモデル解放関数
	 */
	virtual void ReleaseModel()override;

private:
	//!矩形型ブロック情報(頂点情報)
	ObjectInfo m_rectblock_info;

public:
    /**
 　　* @brief  オブジェクト情報Getter
     * @param[out] copy_info_ 保存用オブジェクト構造体
	 * @details 引数にオブジェクトの情報を渡す
 　　*/
	const void GetRectBlockInfo(ObjectInfo& copy_info_) { copy_info_ = m_rectblock_info; }
};

#endif
