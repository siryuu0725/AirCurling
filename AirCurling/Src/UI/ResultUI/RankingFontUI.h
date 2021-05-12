/**
 * @file RankingFontUI.h
 * @brief リザルトシーンのランキング文字を扱う
 * @details 中身：ランキング文字クラス
**/
#ifndef RESULTUI_RANKINGFONT_H_
#define RESULTUI_RANKINGFONT_H_
#include "../UIBase.h"
#include "ResultUICategory.h"
#include "../../Score/RankingData.h"

//!Textureの種類
enum class ResultRankingCategory :__int8
{
	Number_One,
	Number_Two,
	Number_Three,
	CategoryMax,
};

/**
* ランキング文字クラス
*/

class RankingFontUI :public UIBase
{
public:
	//!スコアランキング情報
	struct  RankingFontInfo
	{
		RankingFontInfo() :
			m_firstui_pos(D3DXVECTOR2(0.0f, 0.0f)),
			m_secondui_pos(D3DXVECTOR2(0.0f, 0.0f)),
			m_thirdui_pos(D3DXVECTOR2(0.0f, 0.0f)),
			first(""),
			second(""),
			third(""),
			score_table{ "" }
		{}

		D3DXVECTOR2  m_firstui_pos;
		D3DXVECTOR2  m_secondui_pos;
		D3DXVECTOR2  m_thirdui_pos;

		char first[6];   //!1位スコア表示用
		char second[6];	 //!2位スコア表示用
		char third[6];	 //!3位スコア表示用

		std::vector<std::string> score_table;
	};

	RankingFontUI() {}
	~RankingFontUI() {}

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
	RankingFontInfo m_ranking_info; //!ランキング文字情報
};
#endif