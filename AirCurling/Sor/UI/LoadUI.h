#ifndef LOAD_H_
#define LOAD_H_
#include "../UI/UIBase.h"
#include "../System/Graphics.h"

/**
*@clss  ロード用UIクラス
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
	void SetUpBuffer();

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
		Graphics::TEXTURE_DATA m_ui_tex[(int)LoadUICategory::CategoryMax];  //!テクスチャ

		/* 回転用に各頂点のposを用意 */
		D3DXVECTOR2 left_top_pos;    //!左上
		D3DXVECTOR2 left_down_pos;	 //!左下
		D3DXVECTOR2 right_top_pos;	 //!右上
		D3DXVECTOR2 right_down_pos;	 //!右下

		D3DXVECTOR2 m_center_pos;   //!回転用軸pos

		D3DXVECTOR2 m_nowload_pos;  //!「NowLoading」文字座標

		float m_rote_angle; //!テクスチャ回転角度

		int m_rote_timer;   //!テクスチャ回転スピード

	};

	LoadInfo m_load_ui_info;
};

#endif