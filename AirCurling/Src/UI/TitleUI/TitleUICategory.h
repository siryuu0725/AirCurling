/**
 * @file TitleUICategory.h
 * @brief タイトルシーンで使用するテクスチャの種類を宣言する
**/
#ifndef TITLEUICATEGORY_H_
#define TITLEUICATEGORY_H_

//!UIの種類
enum class TitleUICategory :__int8
{
	BG,              //!背景
	HelpBG,	         //!ヘルプ画面用BG
	Name,		     //!タイトル名
	Start,		     //!文字「スタート」
	End,		     //!文字「終わり」
	Help,		     //!文字「ヘルプ」
	NowSelect,	     //!現在選択枠
	SelectStage1,    //!文字「1」
	SelectStage2,    //!文字「2」
	NowSelectStage,  //!現在選択ステージ枠
	SelectStageFont, //!文字「ステージを選択」
	CategoryMax,     //!UI数
};

#endif