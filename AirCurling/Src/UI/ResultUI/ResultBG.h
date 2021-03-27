/**
 * @file ResultBG.h
 * @brief リザルトシーンの背景を扱う
 * @details 中身：リザルト背景クラス
**/
#ifndef RESULTUI_BG_H_
#define RESULTUI_BG_H_
#include "../UIBase.h"
#include "ResultUICategory.h"

//!Textureの種類
enum class ResultBGTexCategory :__int8
{
	BG,
	CategoryMax,
};

/**
* リザルト背景クラス
*/
class RusultBG :public UIBase
{
public:
	//!リザルト背景情報
	struct RusultBGInfo
	{
		RusultBGInfo() :
			m_ui_pos{ D3DXVECTOR2(0.0f,0.0f) }
		{}

		Graphics::TextureData m_ui_tex; //Textureデータ
		D3DXVECTOR2  m_ui_pos; //Texture座標
	};

	RusultBG() {}
	~RusultBG() {}

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
	RusultBGInfo m_bg_info; //!リザルト背景情報
};
#endif