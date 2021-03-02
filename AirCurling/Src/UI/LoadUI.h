/**
 * @file LoadUI.h
 * @brief ゲームシーン中移行中のロード画面を扱う
 * @details 中身：ロード用UIクラス
**/
#ifndef LOADUI_H_
#define LOADUI_H_
#include "../UI/UIBase.h"
#include "../System/Graphics.h"

/**
* ロード用UIクラス
*/

class LoadUI
{
public:
	//!UIの種類
	enum class LoadUICategory :int
	{
		NowLoad, //!文字「NowLoad」
		RoteTex, //!回転テクスチャ
		CategoryMax,
	};
public:
	LoadUI() {}
	~LoadUI() {}

	/**
	 * @brief  初期化関数
	 * @detail オブジェクト情報初期化
	 */
	void Init();

	/**
	 * @brief  テクスチャ読み込み関数
	 */
	void LoadTex();

	/**
	 * @brief  描画情報送信関数
	 */
	void Draw();

	/**
	 * @brief  更新関数
	 * @detail 更新処理まとめ関数
	 */
	void Update();

	/**
	 * @brief  テクスチャ解放関数
	 */
	void ReleaseTex();

	/**
	 * @brief  ロード中テクスチャ回転関数
	 * @detail ゲーム読み込み中のテクスチャ回転処理を行う
	 */
	void LoadTexRote();

private:
	//!ロード画面UI情報
	struct LoadInfo
	{
		LoadInfo():
			left_top_pos(D3DXVECTOR2(0.0f,0.0f)),
			left_down_pos(D3DXVECTOR2(0.0f, 0.0f)),
			right_top_pos(D3DXVECTOR2(0.0f, 0.0f)),
			right_down_pos(D3DXVECTOR2(0.0f, 0.0f)),
			m_center_pos(D3DXVECTOR2(0.0f, 0.0f)),
			m_nowload_pos(D3DXVECTOR2(0.0f, 0.0f)),
			m_rote_angle(0.0f),
			m_rote_timer(0)
		{}

		Graphics::TextureData m_ui_tex[(int)LoadUICategory::CategoryMax];  //!テクスチャ

		/* 回転用に各頂点のposを用意 */
		D3DXVECTOR2 left_top_pos;    //!左上
		D3DXVECTOR2 left_down_pos;	 //!左下
		D3DXVECTOR2 right_top_pos;	 //!右上
		D3DXVECTOR2 right_down_pos;	 //!右下

		D3DXVECTOR2 m_center_pos;   //!回転用軸pos

		D3DXVECTOR2 m_nowload_pos;  //!「NowLoading」文字座標

		float m_rote_angle; //!テクスチャ回転角度

		__int8 m_rote_timer;   //!テクスチャ回転スピード

	};

	LoadInfo m_loadui_info;
};

#endif