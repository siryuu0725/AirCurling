/**
 * @file BG.h
 * @brief ポーズ中の背景を扱う
 * @details 中身：ポーズ中背景クラス
**/
#ifndef PAUSEUI_BG_H_
#define PAUSEUI_BG_H_

#include "../UIBase.h"
#include "PauseUICategory.h"
#include "PauseItem.h"

//!Textureの種類
enum class PauseBGTexCategory :__int8
{
	BG,          //!背景
	HelpBg,      //!ヘルプ画面背景
	CategoryMax
};


/**
* ポーズ中背景クラス
*/

class PauseBG :public UIBase
{
public:
	//!ポーズ中背景情報
	struct PauseBGInfo
	{
		PauseBGInfo() :
			m_ui_pos{ D3DXVECTOR2(0.0f,0.0f) }
		{}

		Graphics::TextureData m_ui_tex[(__int8)PauseBGTexCategory::CategoryMax]; //Textureデータ

		D3DXVECTOR2  m_ui_pos[(__int8)PauseBGTexCategory::CategoryMax]; //Texture座標
	};

	PauseBG(PauseItemUI* pose_item_) :mp_pause_item(pose_item_) {}
	~PauseBG() {}

	/**
	 * @brief  初期化関数
	 * @details オブジェクト情報初期化
	 */
	virtual void Init()override;

	/**
	 * @brief  描画情報送信関数
	 */
	virtual void Draw()override;

	/**
	 * @brief  テクスチャ解放関数
	 */
	virtual void ReleaseTex()override;

private:
	PauseBGInfo m_bg_info;  //!ポーズ中背景情報
	PauseItemUI* mp_pause_item; //!//!ポーズ中項目

};
#endif