/**
 * @file LoadIconUI.h
 * @brief ロード中のアイコンを扱う
 * @details 中身：ロードアイコンクラス
**/
#ifndef LOADUI_ICON_H_
#define LOADUI_ICON_H_

#include "../UIBase.h"
#include "LoadUICategory.h"

//!Textureの種類
enum class LoadIconTexCategory :int
{
	RoteTex, //!回転テクスチャ
	CategoryMax,
};

/**
* ロードアイコンクラス
*/

class LoadIconUI :public UIBase
{
public:
	//!ロードアイコン情報
	struct LoadIconUIInfo
	{
		LoadIconUIInfo() :
			m_ui_pos{ D3DXVECTOR2(0.0f,0.0f) },
			left_top_pos(D3DXVECTOR2(0.0f, 0.0f)),
			left_down_pos(D3DXVECTOR2(0.0f, 0.0f)),
			right_top_pos(D3DXVECTOR2(0.0f, 0.0f)),
			right_down_pos(D3DXVECTOR2(0.0f, 0.0f)),
			m_center_pos(D3DXVECTOR2(0.0f, 0.0f)),
			m_rote_angle(0.0f),
			m_rote_timer(0)
		{}

		Graphics::TextureData m_ui_tex; //Textureデータ
		D3DXVECTOR2  m_ui_pos; //Texture座標

		/* 回転用に各頂点のposを用意 */
		D3DXVECTOR2 left_top_pos;   //!左上
		D3DXVECTOR2 left_down_pos;	//!左下
		D3DXVECTOR2 right_top_pos;	//!右上
		D3DXVECTOR2 right_down_pos;	//!右下

		D3DXVECTOR2 m_center_pos;   //!回転用軸pos

		float m_rote_angle;         //!テクスチャ回転角度

		__int8 m_rote_timer;        //!テクスチャ回転スピード
	};

	LoadIconUI() {}
	~LoadIconUI() {}

	/**
	 * @brief  初期化関数
	 * @details オブジェクト情報初期化
	 */
	virtual void Init()override;

	/**
	 * @brief  更新関数
	 * @details ゲーム読み込み中のテクスチャ回転処理を行う
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

private:
	LoadIconUIInfo m_loadicon_info;  //!ロードアイコン情報
};
#endif