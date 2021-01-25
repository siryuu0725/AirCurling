#ifndef RESULTUI_H_
#define RESULTUI_H_

#include "UIBase.h"
#include "../Score/CSV.h"

/**
*@clss  リザルト用UIクラス
*/

class ResultUI
{
public:
	//!UIの種類
	enum class ResultUICategory :int
	{
		BG,
		CategoryMax,
	};
public:
	ResultUI() {}
	~ResultUI() {}

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
	 * @brief  テクスチャ解放関数
	 */
	void ReleaseTex();
private:
	CSV* csv;

	//!スコアランキング情報
	struct  Ranking
	{
		char first[6];   //!1位スコア表示用
		char second[6];	 //!2位スコア表示用
		char third[6];	 //!3位スコア表示用

		std::vector<std::string> score_table;
	};

	//!結果画面UI情報
	struct ResultUIInfo
	{
		Graphics::TEXTURE_DATA ui_tex[(int)ResultUICategory::CategoryMax];

		D3DXVECTOR2  ui_pos[(int)ResultUICategory::CategoryMax];

	};

	ResultUIInfo result_ui_info;

	Ranking m_ranking;
};
#endif