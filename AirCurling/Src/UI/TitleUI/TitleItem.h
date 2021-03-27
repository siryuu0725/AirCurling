/**
 * @file TitleItem.h
 * @brief タイトルシーンでの各選択項目を扱う
 * @details 中身：タイトル画面選択項目クラス
**/
#ifndef TITLEUI_ITEM_H_
#define TITLEUI_ITEM_H_

#include "../UIBase.h"
#include "TitleUICategory.h"


//!Textureの種類
enum class TitleItemTexCategory :__int8
{
	Start,		     //!文字「スタート」
	End,		     //!文字「終わり」
	Help,		     //!文字「ヘルプ」
	NowSelect,	     //!現在選択枠
	CategoryMax,     //!UI数
};

/**
* タイトル画面選択項目クラス
*/

class TitleItem:public UIBase
{
public:
	//!タイトル画面選択項目情報
	struct ItemInfo
	{
		ItemInfo() :
			m_ui_pos{ D3DXVECTOR2(0.0f,0.0f) },
			m_is_start(false),
			m_is_end(false),
			m_is_help(false)
		{}

		Graphics::TextureData m_ui_tex[(__int8)TitleItemTexCategory::CategoryMax]; //Textureデータ

		D3DXVECTOR2  m_ui_pos[(__int8)TitleItemTexCategory::CategoryMax]; //Texture座標

		bool m_is_start; //!「はじめる」を押した時
		bool m_is_end;	 //!「おわる」を押した時
		bool m_is_help;	 //!「ヘルプ」を押した時

	};

	TitleItem() {}
	~TitleItem() {}

	/**
	 * @brief  初期化関数
	 * @details オブジェクト情報初期化
	 */
	virtual void Init()override;

	/**
	 * @brief  更新関数
	 * @details 更新処理まとめ関数
	 */
	virtual void Update();

	/**
	 * @brief  描画情報送信関数
	 */
	virtual void Draw()override;

	/**
	 * @brief  テクスチャ解放関数
	 */
	virtual void ReleaseTex()override;

	/**
	 * @brief  フラグ初期化関数
	 * @details タイトル項目で使用しているフラグを全て初期化する
	 */
	void FlgReset();

	/**
　　* @brief  UI情報Getter
	* @param[out] copy_info_ 保存用UI構造体
	* @details 引数にUIの情報を渡す
　　*/
	void GetTitleItemInfo(ItemInfo& copy_info_) { copy_info_ = m_titleitem_info; }

private:
	ItemInfo m_titleitem_info; //!タイトル画面選択項目情報
};
#endif