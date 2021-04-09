/**
 * @file ModeUI.h
 * @brief ゲーム中の左上に表示するモード文字を扱う
 * @details 中身：プレイヤーモードクラス
**/
#ifndef GAMEUI_MODE_H_
#define GAMEUI_MODE_H_

#include "../UIBase.h"
#include "GameUICategory.h"

//!Textureの種類
enum class PlayerModeTexCategory :__int8
{
	ViewMode,		 //!文字「Viewモード」
	ShotMode,		 //!文字「Shotモード」
	CategoryMax,	 //!UI数
};

/**
* プレイヤーモードクラス
*/

class PlayerModeUI :public UIBase
{
public:
	//!プレイヤーモード情報
	struct PlayerModeUIInfo
	{
		PlayerModeUIInfo() :
			m_ui_pos{ D3DXVECTOR2(0.0f,0.0f) },
			m_is_shotmode(false)
		{}

		Graphics::TextureData m_ui_tex[(__int8)PlayerModeTexCategory::CategoryMax]; //Textureデータ

		D3DXVECTOR2  m_ui_pos[(__int8)PlayerModeTexCategory::CategoryMax]; //Texture座標

		bool m_is_shotmode; //!shot(打つ)モード切り替えフラグ

	};

	PlayerModeUI() {}
	~PlayerModeUI() {}

	/**
	 * @brief  初期化関数
	 * @details オブジェクト情報初期化
	 */
	virtual void Init()override;

	/**
	 * @brief  更新関数
	 * @details 更新処理関数
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
　　* @brief  UI情報Getter
	* @param[out] copy_info_ 保存用UI構造体
	* @details 引数にUIの情報を渡す
　　*/
	const void GetPlayerModeUIInfo(PlayerModeUIInfo& copy_info_) { copy_info_ = m_mode_info; }

private:
	PlayerModeUIInfo m_mode_info; //!プレイヤーモード情報
};
#endif