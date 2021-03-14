/**
 * @file PoseUI.h
 * @brief ゲームシーン中のポーズ画面でのUIを扱う
 * @details 中身：ポーズ画面用UIクラス
**/
#ifndef POSEUI_H_
#define POSEUI_H_

#include "UIBase.h"
#include "../Score/RankingData.h"

//!UIの種類
enum class HelpUICategory :int
{
	BG,          //!背景
	Continue,    //!文字「つづける」
	End,         //!文字「おわる」
	Help,        //!文字「へるぷ」
	Select,      //!選択中
	HelpBg,      //!ヘルプ画面背景
	CategoryMax,
};

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

		Graphics::TextureData m_ui_tex[(int)HelpUICategory::CategoryMax];  //!テクスチャ情報構造体

		D3DXVECTOR2  m_ui_pos[(int)HelpUICategory::CategoryMax];  //!テクスチャ座標

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
	 * @brief  ポーズ中UI当たり判定関数
	 * @details ポーズ画面中の「つづける」などのUIとの当たり判定を行う
	 */
	void SelectUI();

	/**
	 * @brief  ヘルプ画面切り替え関数
	 * @details ポーズ画面中からヘルプ画面に行った際再びポーズ画面に戻るかどうかを判定する
	 */
	void HelpMode();

	/**
	 * @brief  テクスチャ読み込み関数
	 */
	void LoadTex();

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
	UIExternalInfo m_poseui_externalinfo[static_cast<int>(HelpUICategory::CategoryMax)];
};
#endif