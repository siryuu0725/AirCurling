/**
 * @file GameName.h
 * @brief タイトルシーンでのゲーム名を扱う
 * @details 中身：ゲーム名クラス
**/
#ifndef TITLEUI_GAMENAME_H_
#define TITLEUI_GAMENAME_H_

#include "../UIBase.h"
#include "TitleUICategory.h"
#include "TitleItem.h"

//!Textureの種類
enum class GameNameTexCategory :__int8
{
	Name,		     //!タイトル名
	CategoryMax,     //!UI数
};

/**
* ゲーム名クラス
*/

class GameName :public UIBase
{
public:
	//!ゲーム名情報
	struct GameNameInfo
	{
		GameNameInfo() :
			m_ui_pos{ D3DXVECTOR2(0.0f,0.0f) }
		{}

		Graphics::TextureData m_ui_tex; //Textureデータ
		D3DXVECTOR2  m_ui_pos; //Texture座標
	};

	/**
 　　* @brief  コンストラクタ
 　　* @param[in] title_item_ タイトル画面選択項目アドレス
 　　*/
	GameName(TitleItem* title_item_) :mp_title_item(title_item_) {}
	~GameName() {}

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
	GameNameInfo m_titlename_info; //!ゲーム名情報
	
	TitleItem* mp_title_item; //!タイトル画面選択項目
};
#endif