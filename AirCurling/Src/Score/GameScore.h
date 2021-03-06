﻿/**
 * @file GameScore.h
 * @brief ゲーム内で計算されたスコアを管理する
 * @details 中身：スコアクラス
**/
#ifndef GAMESCORE_H_
#define GAMESCORE_H_

constexpr unsigned __int8 ScoreMinValue = 0;   //!スコアの最小値

/**
* スコア管理クラス
*/
class Score
{
public:
	Score() :m_score(0) {}
	~Score() {}

	/**
　　* @brief  インスタンス化関数
　　* @details 初回のみインスタンス化し、それ以外は実態を呼ぶ
　　*/
	static Score* Instance();

	/**
　　* @brief  スコア加算関数
	* @param[in] score_ 加算するスコア数
　　* @details 初回のみインスタンス化し、それ以外は実態を呼ぶ
　　*/
	void Add(__int16 score_);

	/**
　　* @brief  スコア初期化関数
　　* @details ResultScene終了時にスコアが残らないようにするため
　　*/
	void Reset();

	/**
	*	@brief Instance解放関数(Debug用)
	*	@details 手動でインスタンスを解放する
	*/
	void ReleaseInstance();

	/**
　　* @brief  スコアGetter関数
　　*/
	const __int16 GetScore()const { return m_score; }

private:
	static Score* mp_instance;

	__int16 m_score;  //!スコア保存用
};

#endif