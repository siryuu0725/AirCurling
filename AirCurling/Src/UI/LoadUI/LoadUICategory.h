/**
 * @file LoadUICategory.h
 * @brief ロード画面で使用するテクスチャの種類を宣言する
**/
#ifndef LOADUICATEGORY_H_
#define LOADUICATEGORY_H_

//!UIの種類
enum class LoadUICategory :__int8
{
	RotTex,     //!回転テクスチャ
	NowLoad,    //!文字「NowLoad」
	CategoryMax,
};

#endif