/**
 * @file GameUICategory.h
 * @brief ゲームシーンで使用するテクスチャの種類を宣言する
**/
#ifndef GAMEUICATEGORY_H_
#define GAMEUICATEGORY_H_

//!UIの種類
enum class GameUICategory :int
{
	ShotGauge,       //!打つ威力ゲージ
	ShotGaugeFlame,	 //!打つ威力ゲージ枠
	ShotBox,		 //!打つ威力決定バー
	Turn,			 //!文字「ターン」
	TurnNumber,		 //!ターン数
	ViewMode,		 //!文字「Viewモード」
	ShotMode,		 //!文字「shotモード」
	One_Score,		 //!スコア数1の位
	Ten_Score,		 //!スコア数10の位
	Start,			 //!文字「スタート」
	Kacco,			 //!文字「=」
	Finish,          //!文字「フィニッシュ」
	CategoryMax,	 //!UI数
};

#endif