/**
 * @file GameScore.h
 * @brief ゲーム中の右上に表示するスコアを扱う
 * @details 中身：ゲームスコアUIクラス
**/
#ifndef GAMEUI_GAMESCORE_H_
#define GAMEUI_GAMESCORE_H_

#include "../UIBase.h"
#include "GameUICategory.h"

//!Textureの種類
enum class GameScoreTexCategory :__int8
{
	One_Score,		 //!スコア数1の位
	Ten_Score,		 //!スコア数10の位
	CategoryMax,	 //!UI数
};

/**
* ゲームスコアUIクラス
*/

class GameScoreUI :public UIBase
{
public:
	//!ゲームスコアUIクラス情報
	struct GameScoreUIInfo
	{
		GameScoreUIInfo() :
			m_ui_pos{ D3DXVECTOR2(0.0f,0.0f) },
			m_ui_tu{ 0.0f },
			m_ui_tv{ 0.0f },
			m_now_score(0),
			m_one_score(0),
			m_ten_score(0),
			m_score("")
		{}

		Graphics::TextureData m_ui_tex[(__int8)GameScoreTexCategory::CategoryMax];  //Textureデータ

		D3DXVECTOR2  m_ui_pos[(__int8)GameScoreTexCategory::CategoryMax]; //Texture座標

		float  m_ui_tu[(__int8)GameScoreTexCategory::CategoryMax]; //!テクスチャのTU値
		float  m_ui_tv[(__int8)GameScoreTexCategory::CategoryMax]; //!テクスチャのTV値

		__int8 m_now_score; //!総合スコア 

		__int8 m_one_score;  //!スコア1の位保存用
		__int8 m_ten_score;  //!スコア10の位保存用

		char m_score[20];//!スコア描画用
	};

	GameScoreUI() {}
	~GameScoreUI() {}

	/**
	 * @brief  初期化関数
	 * @details オブジェクト情報初期化
	 */
	virtual void Init()override;

	/**
	 * @brief  更新処理関数
	 * @param[in] is_turnend_ 1ターン終了フラグ
	 * @details スコア加算
	 */
	void AddScore(bool is_turnend_);

	/**
	 * @brief  描画情報送信関数
	 */
	virtual void Draw()override;

	/**
	 * @brief  テクスチャ解放関数
	 */
	virtual void ReleaseTex()override;

private:
	GameScoreUIInfo m_gamescoer_info; //!ゲームスコアUIクラス情報
};
#endif