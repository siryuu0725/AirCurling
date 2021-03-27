/**
 * @file LoadUI.h
 * @brief ゲームシーン中移行中のロード画面を扱う
 * @details 中身：ロード用UIクラス
**/
#ifndef LOADUI_H_
#define LOADUI_H_
#include "../UIBase.h"
#include "LoadUICategory.h"
#include "LoadIconUI.h"
#include "LoadFontUI.h"
constexpr unsigned __int8 LoadUICategoryNum = 2;  //!ロード画面で使用するUIオブジェクトの数

/**
* ロード用UIクラス
*/
class LoadUI :public UIBase
{
public:
	LoadUI() {}
	~LoadUI() {}

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
	void LoadPoseUIExternalInfo();

	/**
	 * @brief  描画情報送信関数
	 */
	void Draw();

	/**
	 * @brief  更新関数
	 * @details 更新処理まとめ関数
	 */
	void Update();

	/**
	 * @brief  テクスチャ解放関数
	 */
	void ReleaseTex();

private:
	LoadFontUI* mp_load_font;  //!ロード文字
	LoadIconUI* mp_load_icon;  //!ロードアイコン
	UIExternalInfo m_loadui_externalinfo[static_cast<int>(LoadUICategory::CategoryMax)];
};

#endif