/**
 * @file ResultUI.h
 * @brief リザルトシーン画面でのUIを扱う
 * @details 中身：リザルト用UIクラス
**/
#ifndef RESULTUI_H_
#define RESULTUI_H_

#include "../UIBase.h"
#include "ResultUICategory.h"
#include "ResultBG.h"
#include "RankingFontUI.h"
constexpr unsigned __int8 ResultUICategoryNum = 2;  //!リザルトシーンで使用するUIオブジェクトの数

/**
* リザルト用UIクラス
*/
class ResultUI :public UIBase
{
public:
	ResultUI() {}
	~ResultUI() {}

	/**
	 * @brief  初期化関数
	 * @details オブジェクト情報初期化
	 */
	void Init();

	/**
	 * @brief  外部データセット関数
	 * @details 各UIカテゴリーに必要な座標を渡す
	 */
	void SetUIPos();

	/**
	 * @brief  外部データ読み込み関数
	 * @details 読み込んだ外部データを外部データ用の構造体に保存する
	 */
	void LoadResultUIExternalInfo();

	/**
	 * @brief  描画情報送信関数
	 */
	void Draw();

	/**
	 * @brief  テクスチャ解放関数
	 */
	void ReleaseTex();

private:
	RusultBG* mp_bg;                //!背景
	RankingFontUI* mp_ranking_font;	//!ランキング文字

	UIExternalInfo m_resultui_externalinfo[static_cast<int>(ResultUICategory::CategoryMax)];
};
#endif