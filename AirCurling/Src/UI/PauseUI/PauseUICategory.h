/**
 * @file PauseUICategory.h
 * @brief ポーズ画面で使用するテクスチャの種類を宣言する
**/
#ifndef POSEUICATEGORY_H_
#define POSEUICATEGORY_H_

//!UIの種類
enum class PauseUICategory :__int8
{
	BG,          //!背景
	HelpBG,      //!ヘルプ画面背景
	Continue,    //!文字「つづける」
	End,         //!文字「おわる」
	Help,        //!文字「へるぷ」
	Select,      //!選択中
	CategoryMax,
};

#endif