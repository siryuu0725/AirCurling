/**
 * @file TitleUI.h
 * @brief タイトルシーン画面でのUIを扱う
 * @details 中身：タイトル用UIクラス
**/
#ifndef TITLEUI_H_
#define TITLEUI_H_

#include "../UIBase.h"
#include "TitleUICategory.h"
#include "../../System/Sound/SoundController.h"
#include "TitleBG.h"
#include "TitleItem.h"
#include "GameName.h"
#include "StageItem.h"
constexpr unsigned __int8 TitleUICategoryNum = 4;  //!タイトルシーンで使用するUIオブジェクトの数

/**
* タイトル用UIクラス
*/

class TitleUI :public UIBase
{
public:
	//!タイトル画面UI情報
	struct TitleUIInfo
	{
		TitleUIInfo() :
			startui_flg(false),
			endui_flg(false),
			helpui_flg(false),
			m_is_stage_1(false),
			m_is_stage_2(false)
		{}

		/* 各Sceneへ飛ぶ判定 */
		bool startui_flg;  //!「はじめる」を押した時
		bool endui_flg;	   //!「おわる」を押した時
		bool helpui_flg;   //!「ヘルプ」を押した時

		bool m_is_stage_1;   //!ステージ1を選んだ場合
		bool m_is_stage_2;   //!ステージ2を選んだ場合

	};

private:
	TitleUIInfo m_titleui_info;

public:
	TitleUI() {}
	~TitleUI() {}

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
	void LoadTitleUIExternalInfo();

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

	/**
　　* @brief  UI情報Getter
	* @param[out] copy_info_ 保存用UI情報構造体
	* @details 引数にUIの情報を渡す
　　*/
	void GetTitleUIInfo(TitleUIInfo& copy_info_) { copy_info_ = m_titleui_info; }

private:
	UIExternalInfo m_titleui_externalinfo[static_cast<int>(TitleUICategory::CategoryMax)];

	TitleBG* mp_bg;
	TitleStageItem* mp_stage_item;
	TitleItem* mp_title_item;
	GameName* mp_game_name;
};
#endif