/**
 * @file TitleBG.h
 * @brief タイトルシーンの背景を扱う
 * @details 中身：タイトル背景クラス
**/
#ifndef TITLEUI_BG_H_
#define TITLEUI_BG_H_

#include "../UIBase.h"
#include "TitleUICategory.h"
#include "TitleItem.h"

//!Textureの種類
enum class TitleBGTexCategory :__int8
{
	BG,              //!背景
	HelpBG,	         //!ヘルプ画面用BG
	CategoryMax,     //!UI数
};


/**
* タイトル背景クラス
*/

class TitleBG :public UIBase
{
public:
	//!タイトル背景情報
	struct BGInfo
	{
		BGInfo() :
			m_ui_pos{ D3DXVECTOR2(0.0f,0.0f) }
		{}

		Graphics::TextureData m_ui_tex[(__int8)TitleBGTexCategory::CategoryMax]; //Textureデータ

		D3DXVECTOR2  m_ui_pos[(__int8)TitleBGTexCategory::CategoryMax]; //Texture座標

	};

	/**
 　　* @brief  コンストラクタ
 　　* @param[in] title_item_ タイトル画面選択項目アドレス
 　　*/
	TitleBG(TitleItem* title_item_) :mp_title_item(title_item_) {}
	~TitleBG() {}

	/**
	 * @brief  初期化関数
	 * @details オブジェクト情報初期化
	 */
	virtual void Init()override;

	/**
	 * @brief  描画情報送信関数
	 */
	void Draw();

	/**
	 * @brief  テクスチャ解放関数
	 */
	virtual void ReleaseTex()override;

private:
	BGInfo m_titlebg_info;  //!タイトル背景情報
	TitleItem* mp_title_item; //!タイトル画面選択項目
};
#endif