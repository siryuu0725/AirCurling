/**
 * @file PoseUI.h
 * @brief ゲームシーン中のポーズ画面でのUIを扱う
 * @details 中身：ポーズ画面用UIクラス
**/
#ifndef POSEUI_H_
#define POSEUI_H_

#include "../UIBase.h"
#include "../../Score/RankingData.h"
#include "PoseUICategory.h"
#include "PoseBG.h"
#include "PoseItem.h"
constexpr unsigned __int8 PoseUICategoryNum = 2;  //!ポーズ画面で使用するUIオブジェクトの数

/**
* ポーズ画面用UIクラス
*/
class PoseUI :public UIBase
{
public:
	//!ヘルプ画面UI情報
	struct HelpUIInfo
	{
		HelpUIInfo() :
			m_ui_pos{ D3DXVECTOR2(0.0f,0.0f) },
			m_select(false),
			m_continue(false),
			m_end(false),
			m_help(false)
		{}

		Graphics::TextureData m_ui_tex[(int)PoseUICategory::CategoryMax];  //!テクスチャ情報構造体

		D3DXVECTOR2  m_ui_pos[(int)PoseUICategory::CategoryMax];  //!テクスチャ座標

		bool m_select;    //!ポーズ画面各項目選択中フラグ
		bool m_continue;  //!「つづける」選択フラグ
		bool m_end;		  //!「おわる」選択フラグ
		bool m_help;	  //!「へるぷ」選択フラグ
	};

private:
	HelpUIInfo m_poseui_info;

	
public:
	PoseUI() {}
	~PoseUI() {}

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
     * @brief  更新関数
     * @details ポーズ画面中の当たり判定などの処理をまとめる
     */
	void Update();

	/**
	 * @brief  描画情報送信関数
	 */
	void Draw();

	/**
	 * @brief  テクスチャ解放関数
	 */
	void ReleaseTex();

	/**
　　* @brief  UI情報Getter
	* @param[out] copy_info_ 保存用UI情報構造体
	* @details 引数にUIの情報を渡す
　　*/
	void GetHelpUIInfo(HelpUIInfo& copy_info_) { copy_info_ = m_poseui_info; }

private:
	UIExternalInfo m_poseui_externalinfo[static_cast<int>(PoseUICategory::CategoryMax)];
	PoseBG* mp_bg;         //!背景
	PoseItemUI* mp_item;   //!項目
};
#endif