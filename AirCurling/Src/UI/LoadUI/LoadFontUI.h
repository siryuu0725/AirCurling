/**
 * @file LoadFontUI.h
 * @brief ゲームシーンロード中の画面に出す文字(NowLoad)
 * @details 中身：ロード画面用文字クラス
**/
#ifndef LOADUI_FONT_H_
#define LOADUI_FONT_H_

#include "../UIBase.h"
#include "LoadUICategory.h"

//!Textureの種類
enum class LoadFontTexCategory :int
{
	NowLoad, //!文字「NowLoad」
	CategoryMax,
};

/**
* ロード画面用文字クラス
*/

class LoadFontUI :public UIBase
{
public:
	//!ロード文字情報
	struct LoadFontUIInfo
	{
		LoadFontUIInfo() :
			m_ui_pos{ D3DXVECTOR2(0.0f,0.0f) }
		{}

		Graphics::TextureData m_ui_tex; //Textureデータ
		D3DXVECTOR2  m_ui_pos; //Texture座標 
	};

	LoadFontUI() {}
	~LoadFontUI() {}

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
	LoadFontUIInfo m_loadfont_info;	//!ロード文字情報
};
#endif